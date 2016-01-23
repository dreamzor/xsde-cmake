/*
 * regexp.c: generic and extensible Regular Expression engine
 *
 * Basically designed with the purpose of compiling regexps for
 * the variety of validation/shemas mechanisms now available in
 * XML related specifications these include:
 *    - XML-1.0 DTD validation
 *    - XML Schemas structure part 1
 *    - XML Schemas Datatypes part 2 especially Appendix F
 *    - RELAX-NG/TREX i.e. the counter proposal
 *
 * See COPYING for the status of this software.
 */
#include <xsde/c/pre.h>

#include <string.h>
#include <stdlib.h>

#include <xsde/config.h>

#ifdef XSDE_CUSTOM_ALLOCATOR
#  include <xsde/allocator.h>
#endif

#include <xsde/c/regexp/xmlregexp.h>
#include <xsde/c/regexp/xmlunicode.h>
#include <xsde/c/regexp/chvalid.h>

#ifndef INT_MAX
#define INT_MAX 123456789 /* easy to flag and big enough for our needs */
#endif

#define MAX_PUSH 10000000

typedef enum
{
  XML_REGEXP_ERROR_NONE,
  XML_REGEXP_ERROR_MEMORY,
  XML_REGEXP_ERROR_COMPILE
} xmlRegexpError;

#define REGEXP_ERROR(str) xmlRegexpErrCompile(ctxt, str);

#ifdef XSDE_CUSTOM_ALLOCATOR
#define REGEXP_MALLOC(n) xsde_alloc(n)
#define REGEXP_REALLOC(p, n) xsde_realloc(p, n)
#define REGEXP_FREE(p) xsde_free(p)
#else
#define REGEXP_MALLOC(n) malloc(n)
#define REGEXP_REALLOC(p, n) realloc(p, n)
#define REGEXP_FREE(p) free(p)
#endif

#define NEXT ctxt->cur++
#define CUR (*(ctxt->cur))
#define NXT(index) (ctxt->cur[index])

#define CUR_SCHAR(s, l) xmlStringCurrentChar(s, &l)
#define NEXTL(l) ctxt->cur += l;
#define XML_REG_STRING_SEPARATOR '|'

/*
 * Need PREV to check on a '-' within a Character Group. May only be used
 * when it's guaranteed that cur is not at the beginning of ctxt->string!
 */
#define PREV (ctxt->cur[-1])


/************************************************************************
 * 									*
 * 			Datatypes and structures			*
 * 									*
 ************************************************************************/

/*
 * Note: the order of the enums below is significant, do not shuffle
 */
typedef enum {
    XML_REGEXP_EPSILON = 1,
    XML_REGEXP_CHARVAL,
    XML_REGEXP_RANGES,
    XML_REGEXP_SUBREG,  /* used for () sub regexps */
    XML_REGEXP_STRING,
    XML_REGEXP_ANYCHAR, /* . */
    XML_REGEXP_ANYSPACE, /* \s */
    XML_REGEXP_NOTSPACE, /* \S */
    XML_REGEXP_INITNAME, /* \l */
    XML_REGEXP_NOTINITNAME, /* \L */
    XML_REGEXP_NAMECHAR, /* \c */
    XML_REGEXP_NOTNAMECHAR, /* \C */
    XML_REGEXP_DECIMAL, /* \d */
    XML_REGEXP_NOTDECIMAL, /* \D */
    XML_REGEXP_REALCHAR, /* \w */
    XML_REGEXP_NOTREALCHAR, /* \W */
    XML_REGEXP_LETTER = 100,
    XML_REGEXP_LETTER_UPPERCASE,
    XML_REGEXP_LETTER_LOWERCASE,
    XML_REGEXP_LETTER_TITLECASE,
    XML_REGEXP_LETTER_MODIFIER,
    XML_REGEXP_LETTER_OTHERS,
    XML_REGEXP_MARK,
    XML_REGEXP_MARK_NONSPACING,
    XML_REGEXP_MARK_SPACECOMBINING,
    XML_REGEXP_MARK_ENCLOSING,
    XML_REGEXP_NUMBER,
    XML_REGEXP_NUMBER_DECIMAL,
    XML_REGEXP_NUMBER_LETTER,
    XML_REGEXP_NUMBER_OTHERS,
    XML_REGEXP_PUNCT,
    XML_REGEXP_PUNCT_CONNECTOR,
    XML_REGEXP_PUNCT_DASH,
    XML_REGEXP_PUNCT_OPEN,
    XML_REGEXP_PUNCT_CLOSE,
    XML_REGEXP_PUNCT_INITQUOTE,
    XML_REGEXP_PUNCT_FINQUOTE,
    XML_REGEXP_PUNCT_OTHERS,
    XML_REGEXP_SEPAR,
    XML_REGEXP_SEPAR_SPACE,
    XML_REGEXP_SEPAR_LINE,
    XML_REGEXP_SEPAR_PARA,
    XML_REGEXP_SYMBOL,
    XML_REGEXP_SYMBOL_MATH,
    XML_REGEXP_SYMBOL_CURRENCY,
    XML_REGEXP_SYMBOL_MODIFIER,
    XML_REGEXP_SYMBOL_OTHERS,
    XML_REGEXP_OTHER,
    XML_REGEXP_OTHER_CONTROL,
    XML_REGEXP_OTHER_FORMAT,
    XML_REGEXP_OTHER_PRIVATE,
    XML_REGEXP_OTHER_NA,
    XML_REGEXP_BLOCK_NAME
} xmlRegAtomType;

typedef enum {
    XML_REGEXP_QUANT_EPSILON = 1,
    XML_REGEXP_QUANT_ONCE,
    XML_REGEXP_QUANT_OPT,
    XML_REGEXP_QUANT_MULT,
    XML_REGEXP_QUANT_PLUS,
    XML_REGEXP_QUANT_ONCEONLY,
    XML_REGEXP_QUANT_ALL,
    XML_REGEXP_QUANT_RANGE
} xmlRegQuantType;

typedef enum {
    XML_REGEXP_START_STATE = 1,
    XML_REGEXP_FINAL_STATE,
    XML_REGEXP_TRANS_STATE,
    XML_REGEXP_SINK_STATE,
    XML_REGEXP_UNREACH_STATE
} xmlRegStateType;

typedef enum {
    XML_REGEXP_MARK_NORMAL = 0,
    XML_REGEXP_MARK_START,
    XML_REGEXP_MARK_VISITED
} xmlRegMarkedType;

typedef struct _xmlRegRange xmlRegRange;
typedef xmlRegRange *xmlRegRangePtr;

struct _xmlRegRange {
    int neg;		/* 0 normal, 1 not, 2 exclude */
    xmlRegAtomType type;
    int start;
    int end;
    xmlChar *blockName;
};

typedef struct _xmlRegAtom xmlRegAtom;
typedef xmlRegAtom *xmlRegAtomPtr;

typedef struct _xmlAutomataState xmlRegState;
typedef xmlRegState *xmlRegStatePtr;

struct _xmlRegAtom {
    int no;
    xmlRegAtomType type;
    xmlRegQuantType quant;
    int min;
    int max;

    void *valuep;
    void *valuep2;
    int neg;
    int codepoint;
    xmlRegStatePtr start;
    xmlRegStatePtr start0;
    xmlRegStatePtr stop;
    int maxRanges;
    int nbRanges;
    xmlRegRangePtr *ranges;
    void *data;
};

typedef struct _xmlRegCounter xmlRegCounter;
typedef xmlRegCounter *xmlRegCounterPtr;

struct _xmlRegCounter {
    int min;
    int max;
};

typedef struct _xmlRegTrans xmlRegTrans;
typedef xmlRegTrans *xmlRegTransPtr;

struct _xmlRegTrans {
    xmlRegAtomPtr atom;
    int to;
    int counter;
    int count;
    int nd;
};

typedef struct _xmlAutomataState xmlAutomataState;
typedef xmlAutomataState *xmlAutomataStatePtr;

struct _xmlAutomataState {
    xmlRegStateType type;
    xmlRegMarkedType mark;
    xmlRegMarkedType reached;
    int no;
    int maxTrans;
    int nbTrans;
    xmlRegTrans *trans;
    /*  knowing states ponting to us can speed things up */
    int maxTransTo;
    int nbTransTo;
    int *transTo;
};

typedef struct _xmlAutomata xmlRegParserCtxt;
typedef xmlRegParserCtxt *xmlRegParserCtxtPtr;

#define AM_AUTOMATA_RNG 1

typedef struct _xmlAutomata xmlAutomata;
typedef xmlAutomata *xmlAutomataPtr;

struct _xmlAutomata {
    xmlChar *string;
    xmlChar *cur;

    int error;
    const char *error_str;
    int neg;

    xmlRegStatePtr start;
    xmlRegStatePtr end;
    xmlRegStatePtr state;

    xmlRegAtomPtr atom;

    int maxAtoms;
    int nbAtoms;
    xmlRegAtomPtr *atoms;

    int maxStates;
    int nbStates;
    xmlRegStatePtr *states;

    int maxCounters;
    int nbCounters;
    xmlRegCounter *counters;

    int determinist;
    int negs;
    int flags;
};

struct _xmlRegexp {
    xmlChar *string;
    int nbStates;
    xmlRegStatePtr *states;
    int nbAtoms;
    xmlRegAtomPtr *atoms;
    int nbCounters;
    xmlRegCounter *counters;
    int determinist;
    int flags;
    /*
     * That's the compact form for determinists automatas
     */
    int nbstates;
    int *compact;
    void **transdata;
    int nbstrings;
    xmlChar **stringMap;
};

typedef struct _xmlRegExecRollback xmlRegExecRollback;
typedef xmlRegExecRollback *xmlRegExecRollbackPtr;

struct _xmlRegExecRollback {
    xmlRegStatePtr state;/* the current state */
    int index;		/* the index in the input stack */
    int nextbranch;	/* the next transition to explore in that state */
    int *counts;	/* save the automata state if it has some */
};

typedef struct _xmlRegInputToken xmlRegInputToken;
typedef xmlRegInputToken *xmlRegInputTokenPtr;

struct _xmlRegInputToken {
    xmlChar *value;
    void *data;
};

typedef struct _xmlRegExecCtxt xmlRegExecCtxt;
typedef xmlRegExecCtxt *xmlRegExecCtxtPtr;

typedef void (*xmlRegExecCallbacks) (xmlRegExecCtxtPtr exec,
	                             const xmlChar *token,
				     void *transdata,
				     void *inputdata);

struct _xmlRegExecCtxt {
    int status;		/* execution status != 0 indicate an error */
    int determinist;	/* did we find an indeterministic behaviour */
    xmlRegexpPtr comp;	/* the compiled regexp */
    xmlRegExecCallbacks callback;
    void *data;

    xmlRegStatePtr state;/* the current state */
    int transno;	/* the current transition on that state */
    int transcount;	/* the number of chars in char counted transitions */

    /*
     * A stack of rollback states
     */
    int maxRollbacks;
    int nbRollbacks;
    xmlRegExecRollback *rollbacks;

    /*
     * The state of the automata if any
     */
    int *counts;

    /*
     * The input stack
     */
    int inputStackMax;
    int inputStackNr;
    int index;
    int *charStack;
    const xmlChar *inputString; /* when operating on characters */
    xmlRegInputTokenPtr inputStack;/* when operating on strings */

    /*
     * error handling
     */
    int errStateNo;		/* the error state number */
    xmlRegStatePtr errState;    /* the error state */
    xmlChar *errString;		/* the string raising the error */
    int *errCounts;		/* counters at the error state */
    int nbPush;
};

#define REGEXP_ALL_COUNTER	0x123456
#define REGEXP_ALL_LAX_COUNTER	0x123457

static void xmlFAParseRegExp(xmlRegParserCtxtPtr ctxt, int top);
static void xmlRegFreeState(xmlRegStatePtr state);
static void xmlRegFreeAtom(xmlRegAtomPtr atom);
static int xmlRegStrEqualWildcard(const xmlChar *expStr, const xmlChar *valStr);
static int xmlRegCheckCharacter(xmlRegAtomPtr atom, int codepoint);
static int xmlRegCheckCharacterRange(xmlRegAtomType type, int codepoint,
                  int neg, int start, int end, const xmlChar *blockName);

static xmlAutomataPtr xmlNewAutomata(void);
static void xmlFreeAutomata(xmlAutomataPtr am);

static int
xmlStrEqual (const xmlChar* s1, const xmlChar* s2)
{
  return strcmp ((const char*) (s1), (const char*) (s2)) == 0;
}

static xmlChar*
xmlStrdup (const xmlChar* s)
{
  return (xmlChar*) (strdup ((const char*) (s)));
}

static xmlChar*
xmlStrndup (const xmlChar* s, int len)
{
  unsigned int n = (unsigned int)len;

  char* r = (char*) REGEXP_MALLOC (n + 1);

  if (r != NULL)
  {
    memcpy (r, s, n);
    r[n] = '\0';
  }

  return (xmlChar*)r;
}

/**
 * xmlStringCurrentChar:
 * @ctxt:  the XML parser context
 * @cur:  pointer to the beginning of the char
 * @len:  pointer to the length of the char read
 *
 * The current char value, if using UTF-8 this may actually span multiple
 * bytes in the input buffer.
 *
 * Returns the current char value and its length
 */

static int
xmlStringCurrentChar(const xmlChar * cur, int *len)
{
  /*
   * We are supposed to handle UTF8, check it's valid
   * From rfc2044: encoding of the Unicode values on UTF-8:
   *
   * UCS-4 range (hex.)           UTF-8 octet sequence (binary)
   * 0000 0000-0000 007F   0xxxxxxx
   * 0000 0080-0000 07FF   110xxxxx 10xxxxxx
   * 0000 0800-0000 FFFF   1110xxxx 10xxxxxx 10xxxxxx
   *
   * Check for the 0x110000 limit too
   */
  unsigned char c;
  unsigned int val;

  c = *cur;
  if (c & 0x80)
  {
    if ((cur[1] & 0xc0) != 0x80)
      goto encoding_error;
    if ((c & 0xe0) == 0xe0)
    {

      if ((cur[2] & 0xc0) != 0x80)
        goto encoding_error;
      if ((c & 0xf0) == 0xf0)
      {
        if (((c & 0xf8) != 0xf0) || ((cur[3] & 0xc0) != 0x80))
          goto encoding_error;
        /* 4-byte code */
        *len = 4;
        val = (cur[0] & 0x7) << 18;
        val |= (cur[1] & 0x3f) << 12;
        val |= (cur[2] & 0x3f) << 6;
        val |= cur[3] & 0x3f;
      }
      else
      {
        /* 3-byte code */
        *len = 3;
        val = (cur[0] & 0xf) << 12;
        val |= (cur[1] & 0x3f) << 6;
        val |= cur[2] & 0x3f;
      }
    }
    else
    {
      /* 2-byte code */
      *len = 2;
      val = (cur[0] & 0x1f) << 6;
      val |= cur[1] & 0x3f;
    }

    return (val);
  }
  else
  {
    /* 1-byte code */
    *len = 1;
    return ((int) *cur);
  }

  /*
   * Assume it's a fixed length encoding (1) with
   * a compatible encoding for the ASCII set, since
   * XML constructs only use < 128 chars
   */
  *len = 1;
  return ((int) *cur);

encoding_error:

  /*
   * An encoding problem may arise from a truncated input buffer
   * splitting a character in the middle. In that case do not raise
   * an error but return 0 to endicate an end of stream problem
   */
  *len = 0;
  return(0);
}

/************************************************************************
 *									*
 * 		Regexp memory error handler				*
 *									*
 ************************************************************************/
/**
 * xmlRegexpErrMemory:
 * @extra:  extra information
 *
 * Handle an out of memory condition
 */
static void
xmlRegexpErrMemory(xmlRegParserCtxtPtr ctxt, const char *extra)
{
    if (ctxt != NULL) {
        ctxt->error = XML_REGEXP_ERROR_MEMORY;
        ctxt->error_str = extra;
    }
}

/**
 * xmlRegexpErrCompile:
 * @extra:  extra information
 *
 * Handle a compilation failure
 */
static void
xmlRegexpErrCompile(xmlRegParserCtxtPtr ctxt, const char *extra)
{
    if (ctxt != NULL) {
        ctxt->error = XML_REGEXP_ERROR_COMPILE;
        ctxt->error_str = extra;
    }
}

/************************************************************************
 * 									*
 * 			Allocation/Deallocation				*
 * 									*
 ************************************************************************/

static int xmlFAComputesDeterminism(xmlRegParserCtxtPtr ctxt);
/**
 * xmlRegEpxFromParse:
 * @ctxt:  the parser context used to build it
 *
 * Allocate a new regexp and fill it with the result from the parser
 *
 * Returns the new regexp or NULL in case of error
 */
static xmlRegexpPtr
xmlRegEpxFromParse(xmlRegParserCtxtPtr ctxt) {
    xmlRegexpPtr ret;

    ret = (xmlRegexpPtr) REGEXP_MALLOC(sizeof(xmlRegexp));
    if (ret == NULL) {
	xmlRegexpErrMemory(ctxt, "compiling regexp");
	return(NULL);
    }
    memset(ret, 0, sizeof(xmlRegexp));
    ret->string = ctxt->string;
    ret->nbStates = ctxt->nbStates;
    ret->states = ctxt->states;
    ret->nbAtoms = ctxt->nbAtoms;
    ret->atoms = ctxt->atoms;
    ret->nbCounters = ctxt->nbCounters;
    ret->counters = ctxt->counters;
    ret->determinist = ctxt->determinist;
    ret->flags = ctxt->flags;
    if (ret->determinist == -1) {
        xmlRegexpIsDeterminist(ret);
    }

    if ((ret->determinist != 0) &&
	(ret->nbCounters == 0) &&
	(ctxt->negs == 0) &&
	(ret->atoms != NULL) &&
	(ret->atoms[0] != NULL) &&
	(ret->atoms[0]->type == XML_REGEXP_STRING)) {
	int i, j, nbstates = 0, nbatoms = 0;
	int *stateRemap;
	int *stringRemap;
	int *transitions;
	void **transdata;
	xmlChar **stringMap;
        xmlChar *value;

	/*
	 * Switch to a compact representation
	 * 1/ counting the effective number of states left
	 * 2/ counting the unique number of atoms, and check that
	 *    they are all of the string type
	 * 3/ build a table state x atom for the transitions
	 */

	stateRemap = REGEXP_MALLOC(ret->nbStates * sizeof(int));
	if (stateRemap == NULL) {
	    xmlRegexpErrMemory(ctxt, "compiling regexp");
	    REGEXP_FREE(ret);
	    return(NULL);
	}
	for (i = 0;i < ret->nbStates;i++) {
	    if (ret->states[i] != NULL) {
		stateRemap[i] = nbstates;
		nbstates++;
	    } else {
		stateRemap[i] = -1;
	    }
	}
#ifdef DEBUG_COMPACTION
	printf("Final: %d states\n", nbstates);
#endif
	stringMap = REGEXP_MALLOC(ret->nbAtoms * sizeof(char *));
	if (stringMap == NULL) {
	    xmlRegexpErrMemory(ctxt, "compiling regexp");
	    REGEXP_FREE(stateRemap);
	    REGEXP_FREE(ret);
	    return(NULL);
	}
	stringRemap = REGEXP_MALLOC(ret->nbAtoms * sizeof(int));
	if (stringRemap == NULL) {
	    xmlRegexpErrMemory(ctxt, "compiling regexp");
	    REGEXP_FREE(stringMap);
	    REGEXP_FREE(stateRemap);
	    REGEXP_FREE(ret);
	    return(NULL);
	}
	for (i = 0;i < ret->nbAtoms;i++) {
	    if ((ret->atoms[i]->type == XML_REGEXP_STRING) &&
		(ret->atoms[i]->quant == XML_REGEXP_QUANT_ONCE)) {
		value = ret->atoms[i]->valuep;
                for (j = 0;j < nbatoms;j++) {
		    if (xmlStrEqual(stringMap[j], value)) {
			stringRemap[i] = j;
			break;
		    }
		}
		if (j >= nbatoms) {
		    stringRemap[i] = nbatoms;
		    stringMap[nbatoms] = xmlStrdup(value);
		    if (stringMap[nbatoms] == NULL) {
			for (i = 0;i < nbatoms;i++)
			    REGEXP_FREE(stringMap[i]);
			REGEXP_FREE(stringRemap);
			REGEXP_FREE(stringMap);
			REGEXP_FREE(stateRemap);
			REGEXP_FREE(ret);
			return(NULL);
		    }
		    nbatoms++;
		}
	    } else {
		REGEXP_FREE(stateRemap);
		REGEXP_FREE(stringRemap);
		for (i = 0;i < nbatoms;i++)
		    REGEXP_FREE(stringMap[i]);
		REGEXP_FREE(stringMap);
		REGEXP_FREE(ret);
		return(NULL);
	    }
	}
#ifdef DEBUG_COMPACTION
	printf("Final: %d atoms\n", nbatoms);
#endif
	transitions = (int *) REGEXP_MALLOC((nbstates + 1) *
	                                (nbatoms + 1) * sizeof(int));
	if (transitions == NULL) {
	    REGEXP_FREE(stateRemap);
	    REGEXP_FREE(stringRemap);
	    REGEXP_FREE(stringMap);
	    REGEXP_FREE(ret);
	    return(NULL);
	}
	memset(transitions, 0, (nbstates + 1) * (nbatoms + 1) * sizeof(int));

	/*
	 * Allocate the transition table. The first entry for each
	 * state corresponds to the state type.
	 */
	transdata = NULL;

	for (i = 0;i < ret->nbStates;i++) {
	    int stateno, atomno, targetno, prev;
	    xmlRegStatePtr state;
	    xmlRegTransPtr trans;

	    stateno = stateRemap[i];
	    if (stateno == -1)
		continue;
	    state = ret->states[i];

	    transitions[stateno * (nbatoms + 1)] = state->type;

	    for (j = 0;j < state->nbTrans;j++) {
		trans = &(state->trans[j]);
		if ((trans->to == -1) || (trans->atom == NULL))
		    continue;
                atomno = stringRemap[trans->atom->no];
		if ((trans->atom->data != NULL) && (transdata == NULL)) {
		    transdata = (void **) REGEXP_MALLOC(nbstates * nbatoms *
			                            sizeof(void *));
		    if (transdata != NULL)
			memset(transdata, 0,
			       nbstates * nbatoms * sizeof(void *));
		    else {
			xmlRegexpErrMemory(ctxt, "compiling regexp");
			break;
		    }
		}
		targetno = stateRemap[trans->to];
		/*
		 * if the same atom can generate transitions to 2 different
		 * states then it means the automata is not determinist and
		 * the compact form can't be used !
		 */
		prev = transitions[stateno * (nbatoms + 1) + atomno + 1];
		if (prev != 0) {
		    if (prev != targetno + 1) {
			ret->determinist = 0;
#ifdef DEBUG_COMPACTION
			printf("Indet: state %d trans %d, atom %d to %d : %d to %d\n",
			       i, j, trans->atom->no, trans->to, atomno, targetno);
			printf("       previous to is %d\n", prev);
#endif
			if (transdata != NULL)
			    REGEXP_FREE(transdata);
			REGEXP_FREE(transitions);
			REGEXP_FREE(stateRemap);
			REGEXP_FREE(stringRemap);
			for (i = 0;i < nbatoms;i++)
			    REGEXP_FREE(stringMap[i]);
			REGEXP_FREE(stringMap);
			goto not_determ;
		    }
		} else {
#if 0
		    printf("State %d trans %d: atom %d to %d : %d to %d\n",
			   i, j, trans->atom->no, trans->to, atomno, targetno);
#endif
		    transitions[stateno * (nbatoms + 1) + atomno + 1] =
			targetno + 1; /* to avoid 0 */
		    if (transdata != NULL)
			transdata[stateno * nbatoms + atomno] =
			    trans->atom->data;
		}
	    }
	}
	ret->determinist = 1;
#ifdef DEBUG_COMPACTION
	/*
	 * Debug
	 */
	for (i = 0;i < nbstates;i++) {
	    for (j = 0;j < nbatoms + 1;j++) {
                printf("%02d ", transitions[i * (nbatoms + 1) + j]);
	    }
	    printf("\n");
	}
	printf("\n");
#endif
	/*
	 * Cleanup of the old data
	 */
	if (ret->states != NULL) {
	    for (i = 0;i < ret->nbStates;i++)
		xmlRegFreeState(ret->states[i]);
	    REGEXP_FREE(ret->states);
	}
	ret->states = NULL;
	ret->nbStates = 0;
	if (ret->atoms != NULL) {
	    for (i = 0;i < ret->nbAtoms;i++)
		xmlRegFreeAtom(ret->atoms[i]);
	    REGEXP_FREE(ret->atoms);
	}
	ret->atoms = NULL;
	ret->nbAtoms = 0;

	ret->compact = transitions;
	ret->transdata = transdata;
	ret->stringMap = stringMap;
	ret->nbstrings = nbatoms;
	ret->nbstates = nbstates;
	REGEXP_FREE(stateRemap);
	REGEXP_FREE(stringRemap);
    }
not_determ:
    ctxt->string = NULL;
    ctxt->nbStates = 0;
    ctxt->states = NULL;
    ctxt->nbAtoms = 0;
    ctxt->atoms = NULL;
    ctxt->nbCounters = 0;
    ctxt->counters = NULL;
    return(ret);
}

/**
 * xmlRegNewParserCtxt:
 * @string:  the string to parse
 *
 * Allocate a new regexp parser context
 *
 * Returns the new context or NULL in case of error
 */
static xmlRegParserCtxtPtr
xmlRegNewParserCtxt(const xmlChar *string) {
    xmlRegParserCtxtPtr ret;

    ret = (xmlRegParserCtxtPtr) REGEXP_MALLOC(sizeof(xmlRegParserCtxt));
    if (ret == NULL)
	return(NULL);
    memset(ret, 0, sizeof(xmlRegParserCtxt));
    if (string != NULL)
	ret->string = xmlStrdup(string);
    ret->cur = ret->string;
    ret->neg = 0;
    ret->negs = 0;
    ret->error = 0;
    ret->determinist = -1;
    return(ret);
}

/**
 * xmlRegNewRange:
 * @ctxt:  the regexp parser context
 * @neg:  is that negative
 * @type:  the type of range
 * @start:  the start codepoint
 * @end:  the end codepoint
 *
 * Allocate a new regexp range
 *
 * Returns the new range or NULL in case of error
 */
static xmlRegRangePtr
xmlRegNewRange(xmlRegParserCtxtPtr ctxt,
	       int neg, xmlRegAtomType type, int start, int end) {
    xmlRegRangePtr ret;

    ret = (xmlRegRangePtr) REGEXP_MALLOC(sizeof(xmlRegRange));
    if (ret == NULL) {
	xmlRegexpErrMemory(ctxt, "allocating range");
	return(NULL);
    }
    ret->neg = neg;
    ret->type = type;
    ret->start = start;
    ret->end = end;
    return(ret);
}

/**
 * xmlRegFreeRange:
 * @range:  the regexp range
 *
 * Free a regexp range
 */
static void
xmlRegFreeRange(xmlRegRangePtr range) {
    if (range == NULL)
	return;

    if (range->blockName != NULL)
	REGEXP_FREE(range->blockName);
    REGEXP_FREE(range);
}

/**
 * xmlRegCopyRange:
 * @range:  the regexp range
 *
 * Copy a regexp range
 *
 * Returns the new copy or NULL in case of error.
 */
static xmlRegRangePtr
xmlRegCopyRange(xmlRegParserCtxtPtr ctxt, xmlRegRangePtr range) {
    xmlRegRangePtr ret;

    if (range == NULL)
	return(NULL);

    ret = xmlRegNewRange(ctxt, range->neg, range->type, range->start,
                         range->end);
    if (ret == NULL)
        return(NULL);
    if (range->blockName != NULL) {
	ret->blockName = xmlStrdup(range->blockName);
	if (ret->blockName == NULL) {
	    xmlRegexpErrMemory(ctxt, "allocating range");
	    xmlRegFreeRange(ret);
	    return(NULL);
	}
    }
    return(ret);
}

/**
 * xmlRegNewAtom:
 * @ctxt:  the regexp parser context
 * @type:  the type of atom
 *
 * Allocate a new atom
 *
 * Returns the new atom or NULL in case of error
 */
static xmlRegAtomPtr
xmlRegNewAtom(xmlRegParserCtxtPtr ctxt, xmlRegAtomType type) {
    xmlRegAtomPtr ret;

    ret = (xmlRegAtomPtr) REGEXP_MALLOC(sizeof(xmlRegAtom));
    if (ret == NULL) {
	xmlRegexpErrMemory(ctxt, "allocating atom");
	return(NULL);
    }
    memset(ret, 0, sizeof(xmlRegAtom));
    ret->type = type;
    ret->quant = XML_REGEXP_QUANT_ONCE;
    ret->min = 0;
    ret->max = 0;
    return(ret);
}

/**
 * xmlRegFreeAtom:
 * @atom:  the regexp atom
 *
 * Free a regexp atom
 */
static void
xmlRegFreeAtom(xmlRegAtomPtr atom) {
    int i;

    if (atom == NULL)
	return;

    for (i = 0;i < atom->nbRanges;i++)
	xmlRegFreeRange(atom->ranges[i]);
    if (atom->ranges != NULL)
	REGEXP_FREE(atom->ranges);
    if ((atom->type == XML_REGEXP_STRING) && (atom->valuep != NULL))
	REGEXP_FREE(atom->valuep);
    if ((atom->type == XML_REGEXP_STRING) && (atom->valuep2 != NULL))
	REGEXP_FREE(atom->valuep2);
    if ((atom->type == XML_REGEXP_BLOCK_NAME) && (atom->valuep != NULL))
	REGEXP_FREE(atom->valuep);
    REGEXP_FREE(atom);
}

/**
 * xmlRegCopyAtom:
 * @ctxt:  the regexp parser context
 * @atom:  the oiginal atom
 *
 * Allocate a new regexp range
 *
 * Returns the new atom or NULL in case of error
 */
static xmlRegAtomPtr
xmlRegCopyAtom(xmlRegParserCtxtPtr ctxt, xmlRegAtomPtr atom) {
    xmlRegAtomPtr ret;

    ret = (xmlRegAtomPtr) REGEXP_MALLOC(sizeof(xmlRegAtom));
    if (ret == NULL) {
	xmlRegexpErrMemory(ctxt, "copying atom");
	return(NULL);
    }
    memset(ret, 0, sizeof(xmlRegAtom));
    ret->type = atom->type;
    ret->quant = atom->quant;
    ret->min = atom->min;
    ret->max = atom->max;
    if (atom->nbRanges > 0) {
        int i;

        ret->ranges = (xmlRegRangePtr *) REGEXP_MALLOC(sizeof(xmlRegRangePtr) *
	                                           atom->nbRanges);
	if (ret->ranges == NULL) {
	    xmlRegexpErrMemory(ctxt, "copying atom");
	    goto error;
	}
	for (i = 0;i < atom->nbRanges;i++) {
	    ret->ranges[i] = xmlRegCopyRange(ctxt, atom->ranges[i]);
	    if (ret->ranges[i] == NULL)
	        goto error;
	    ret->nbRanges = i + 1;
	}
    }
    return(ret);

error:
    xmlRegFreeAtom(ret);
    return(NULL);
}

static xmlRegStatePtr
xmlRegNewState(xmlRegParserCtxtPtr ctxt) {
    xmlRegStatePtr ret;

    ret = (xmlRegStatePtr) REGEXP_MALLOC(sizeof(xmlRegState));
    if (ret == NULL) {
	xmlRegexpErrMemory(ctxt, "allocating state");
	return(NULL);
    }
    memset(ret, 0, sizeof(xmlRegState));
    ret->type = XML_REGEXP_TRANS_STATE;
    ret->mark = XML_REGEXP_MARK_NORMAL;
    return(ret);
}

/**
 * xmlRegFreeState:
 * @state:  the regexp state
 *
 * Free a regexp state
 */
static void
xmlRegFreeState(xmlRegStatePtr state) {
    if (state == NULL)
	return;

    if (state->trans != NULL)
	REGEXP_FREE(state->trans);
    if (state->transTo != NULL)
	REGEXP_FREE(state->transTo);
    REGEXP_FREE(state);
}

/**
 * xmlRegFreeParserCtxt:
 * @ctxt:  the regexp parser context
 *
 * Free a regexp parser context
 */
static void
xmlRegFreeParserCtxt(xmlRegParserCtxtPtr ctxt) {
    int i;
    if (ctxt == NULL)
	return;

    if (ctxt->string != NULL)
	REGEXP_FREE(ctxt->string);
    if (ctxt->states != NULL) {
	for (i = 0;i < ctxt->nbStates;i++)
	    xmlRegFreeState(ctxt->states[i]);
	REGEXP_FREE(ctxt->states);
    }
    if (ctxt->atoms != NULL) {
	for (i = 0;i < ctxt->nbAtoms;i++)
	    xmlRegFreeAtom(ctxt->atoms[i]);
	REGEXP_FREE(ctxt->atoms);
    }
    if (ctxt->counters != NULL)
	REGEXP_FREE(ctxt->counters);
    REGEXP_FREE(ctxt);
}

/************************************************************************
 * 									*
 *		 Finite Automata structures manipulations		*
 * 									*
 ************************************************************************/

static void
xmlRegAtomAddRange(xmlRegParserCtxtPtr ctxt, xmlRegAtomPtr atom,
	           int neg, xmlRegAtomType type, int start, int end,
		   xmlChar *blockName) {
    xmlRegRangePtr range;

    if (atom == NULL) {
	REGEXP_ERROR("add range: atom is NULL");
	return;
    }
    if (atom->type != XML_REGEXP_RANGES) {
	REGEXP_ERROR("add range: atom is not ranges");
	return;
    }
    if (atom->maxRanges == 0) {
	atom->maxRanges = 4;
	atom->ranges = (xmlRegRangePtr *) REGEXP_MALLOC(atom->maxRanges *
		                             sizeof(xmlRegRangePtr));
	if (atom->ranges == NULL) {
	    xmlRegexpErrMemory(ctxt, "adding ranges");
	    atom->maxRanges = 0;
	    return;
	}
    } else if (atom->nbRanges >= atom->maxRanges) {
	xmlRegRangePtr *tmp;
	atom->maxRanges *= 2;
	tmp = (xmlRegRangePtr *) REGEXP_REALLOC(atom->ranges, atom->maxRanges *
                                         sizeof(xmlRegRangePtr));
	if (tmp == NULL) {
	    xmlRegexpErrMemory(ctxt, "adding ranges");
	    atom->maxRanges /= 2;
	    return;
	}
	atom->ranges = tmp;
    }
    range = xmlRegNewRange(ctxt, neg, type, start, end);
    if (range == NULL)
	return;
    range->blockName = blockName;
    atom->ranges[atom->nbRanges++] = range;

}

static int
xmlRegGetCounter(xmlRegParserCtxtPtr ctxt) {
    if (ctxt->maxCounters == 0) {
	ctxt->maxCounters = 4;
	ctxt->counters = (xmlRegCounter *) REGEXP_MALLOC(ctxt->maxCounters *
		                             sizeof(xmlRegCounter));
	if (ctxt->counters == NULL) {
	    xmlRegexpErrMemory(ctxt, "allocating counter");
	    ctxt->maxCounters = 0;
	    return(-1);
	}
    } else if (ctxt->nbCounters >= ctxt->maxCounters) {
	xmlRegCounter *tmp;
	ctxt->maxCounters *= 2;
	tmp = (xmlRegCounter *) REGEXP_REALLOC(ctxt->counters, ctxt->maxCounters *
		                           sizeof(xmlRegCounter));
	if (tmp == NULL) {
	    xmlRegexpErrMemory(ctxt, "allocating counter");
	    ctxt->maxCounters /= 2;
	    return(-1);
	}
	ctxt->counters = tmp;
    }
    ctxt->counters[ctxt->nbCounters].min = -1;
    ctxt->counters[ctxt->nbCounters].max = -1;
    return(ctxt->nbCounters++);
}

static int
xmlRegAtomPush(xmlRegParserCtxtPtr ctxt, xmlRegAtomPtr atom) {
    if (atom == NULL) {
	REGEXP_ERROR("atom push: atom is NULL");
	return(-1);
    }
    if (ctxt->maxAtoms == 0) {
	ctxt->maxAtoms = 4;
	ctxt->atoms = (xmlRegAtomPtr *) REGEXP_MALLOC(ctxt->maxAtoms *
		                             sizeof(xmlRegAtomPtr));
	if (ctxt->atoms == NULL) {
	    xmlRegexpErrMemory(ctxt, "pushing atom");
	    ctxt->maxAtoms = 0;
	    return(-1);
	}
    } else if (ctxt->nbAtoms >= ctxt->maxAtoms) {
	xmlRegAtomPtr *tmp;
	ctxt->maxAtoms *= 2;
	tmp = (xmlRegAtomPtr *) REGEXP_REALLOC(ctxt->atoms, ctxt->maxAtoms *
		                             sizeof(xmlRegAtomPtr));
	if (tmp == NULL) {
	    xmlRegexpErrMemory(ctxt, "allocating counter");
	    ctxt->maxAtoms /= 2;
	    return(-1);
	}
	ctxt->atoms = tmp;
    }
    atom->no = ctxt->nbAtoms;
    ctxt->atoms[ctxt->nbAtoms++] = atom;
    return(0);
}

static void
xmlRegStateAddTransTo(xmlRegParserCtxtPtr ctxt, xmlRegStatePtr target,
                      int from) {
    if (target->maxTransTo == 0) {
	target->maxTransTo = 8;
	target->transTo = (int *) REGEXP_MALLOC(target->maxTransTo *
		                             sizeof(int));
	if (target->transTo == NULL) {
	    xmlRegexpErrMemory(ctxt, "adding transition");
	    target->maxTransTo = 0;
	    return;
	}
    } else if (target->nbTransTo >= target->maxTransTo) {
	int *tmp;
	target->maxTransTo *= 2;
	tmp = (int *) REGEXP_REALLOC(target->transTo, target->maxTransTo *
		                             sizeof(int));
	if (tmp == NULL) {
	    xmlRegexpErrMemory(ctxt, "adding transition");
	    target->maxTransTo /= 2;
	    return;
	}
	target->transTo = tmp;
    }
    target->transTo[target->nbTransTo] = from;
    target->nbTransTo++;
}

static void
xmlRegStateAddTrans(xmlRegParserCtxtPtr ctxt, xmlRegStatePtr state,
	            xmlRegAtomPtr atom, xmlRegStatePtr target,
		    int counter, int count) {

    int nrtrans;

    if (state == NULL) {
	REGEXP_ERROR("add state: state is NULL");
	return;
    }
    if (target == NULL) {
	REGEXP_ERROR("add state: target is NULL");
	return;
    }
    /*
     * Other routines follow the philosophy 'When in doubt, add a transition'
     * so we check here whether such a transition is already present and, if
     * so, silently ignore this request.
     */

    for (nrtrans = state->nbTrans - 1; nrtrans >= 0; nrtrans--) {
	xmlRegTransPtr trans = &(state->trans[nrtrans]);
	if ((trans->atom == atom) &&
	    (trans->to == target->no) &&
	    (trans->counter == counter) &&
	    (trans->count == count)) {
#ifdef DEBUG_REGEXP_GRAPH
	    printf("Ignoring duplicate transition from %d to %d\n",
		    state->no, target->no);
#endif
	    return;
	}
    }

    if (state->maxTrans == 0) {
	state->maxTrans = 8;
	state->trans = (xmlRegTrans *) REGEXP_MALLOC(state->maxTrans *
		                             sizeof(xmlRegTrans));
	if (state->trans == NULL) {
	    xmlRegexpErrMemory(ctxt, "adding transition");
	    state->maxTrans = 0;
	    return;
	}
    } else if (state->nbTrans >= state->maxTrans) {
	xmlRegTrans *tmp;
	state->maxTrans *= 2;
	tmp = (xmlRegTrans *) REGEXP_REALLOC(state->trans, state->maxTrans *
		                             sizeof(xmlRegTrans));
	if (tmp == NULL) {
	    xmlRegexpErrMemory(ctxt, "adding transition");
	    state->maxTrans /= 2;
	    return;
	}
	state->trans = tmp;
    }
#ifdef DEBUG_REGEXP_GRAPH
    printf("Add trans from %d to %d ", state->no, target->no);
    if (count == REGEXP_ALL_COUNTER)
	printf("all transition\n");
    else if (count >= 0)
	printf("count based %d\n", count);
    else if (counter >= 0)
	printf("counted %d\n", counter);
    else if (atom == NULL)
	printf("epsilon transition\n");
    else if (atom != NULL)
        xmlRegPrintAtom(stdout, atom);
#endif

    state->trans[state->nbTrans].atom = atom;
    state->trans[state->nbTrans].to = target->no;
    state->trans[state->nbTrans].counter = counter;
    state->trans[state->nbTrans].count = count;
    state->trans[state->nbTrans].nd = 0;
    state->nbTrans++;
    xmlRegStateAddTransTo(ctxt, target, state->no);
}

static int
xmlRegStatePush(xmlRegParserCtxtPtr ctxt, xmlRegStatePtr state) {
    if (state == NULL) return(-1);
    if (ctxt->maxStates == 0) {
	ctxt->maxStates = 4;
	ctxt->states = (xmlRegStatePtr *) REGEXP_MALLOC(ctxt->maxStates *
		                             sizeof(xmlRegStatePtr));
	if (ctxt->states == NULL) {
	    xmlRegexpErrMemory(ctxt, "adding state");
	    ctxt->maxStates = 0;
	    return(-1);
	}
    } else if (ctxt->nbStates >= ctxt->maxStates) {
	xmlRegStatePtr *tmp;
	ctxt->maxStates *= 2;
	tmp = (xmlRegStatePtr *) REGEXP_REALLOC(ctxt->states, ctxt->maxStates *
		                             sizeof(xmlRegStatePtr));
	if (tmp == NULL) {
	    xmlRegexpErrMemory(ctxt, "adding state");
	    ctxt->maxStates /= 2;
	    return(-1);
	}
	ctxt->states = tmp;
    }
    state->no = ctxt->nbStates;
    ctxt->states[ctxt->nbStates++] = state;
    return(0);
}

/**
 * xmlFAGenerateEpsilonTransition:
 * @ctxt:  a regexp parser context
 * @from:  the from state
 * @to:  the target state or NULL for building a new one
 *
 */
static void
xmlFAGenerateEpsilonTransition(xmlRegParserCtxtPtr ctxt,
			       xmlRegStatePtr from, xmlRegStatePtr to) {
    if (to == NULL) {
	to = xmlRegNewState(ctxt);
	xmlRegStatePush(ctxt, to);
	ctxt->state = to;
    }
    xmlRegStateAddTrans(ctxt, from, NULL, to, -1, -1);
}

/**
 * xmlFAGenerateCountedEpsilonTransition:
 * @ctxt:  a regexp parser context
 * @from:  the from state
 * @to:  the target state or NULL for building a new one
 * counter:  the counter for that transition
 *
 */
static void
xmlFAGenerateCountedEpsilonTransition(xmlRegParserCtxtPtr ctxt,
	    xmlRegStatePtr from, xmlRegStatePtr to, int counter) {
    if (to == NULL) {
	to = xmlRegNewState(ctxt);
	xmlRegStatePush(ctxt, to);
	ctxt->state = to;
    }
    xmlRegStateAddTrans(ctxt, from, NULL, to, counter, -1);
}

/**
 * xmlFAGenerateCountedTransition:
 * @ctxt:  a regexp parser context
 * @from:  the from state
 * @to:  the target state or NULL for building a new one
 * counter:  the counter for that transition
 *
 */
static void
xmlFAGenerateCountedTransition(xmlRegParserCtxtPtr ctxt,
	    xmlRegStatePtr from, xmlRegStatePtr to, int counter) {
    if (to == NULL) {
	to = xmlRegNewState(ctxt);
	xmlRegStatePush(ctxt, to);
	ctxt->state = to;
    }
    xmlRegStateAddTrans(ctxt, from, NULL, to, -1, counter);
}

/**
 * xmlFAGenerateTransitions:
 * @ctxt:  a regexp parser context
 * @from:  the from state
 * @to:  the target state or NULL for building a new one
 * @atom:  the atom generating the transition
 *
 * Returns 0 if success and -1 in case of error.
 */
static int
xmlFAGenerateTransitions(xmlRegParserCtxtPtr ctxt, xmlRegStatePtr from,
	                 xmlRegStatePtr to, xmlRegAtomPtr atom) {
    xmlRegStatePtr end;

    if (atom == NULL) {
	REGEXP_ERROR("genrate transition: atom == NULL");
	return(-1);
    }
    if (atom->type == XML_REGEXP_SUBREG) {
	/*
	 * this is a subexpression handling one should not need to
	 * create a new node except for XML_REGEXP_QUANT_RANGE.
	 */
	if (xmlRegAtomPush(ctxt, atom) < 0) {
	    return(-1);
	}
	if ((to != NULL) && (atom->stop != to) &&
	    (atom->quant != XML_REGEXP_QUANT_RANGE)) {
	    /*
	     * Generate an epsilon transition to link to the target
	     */
	    xmlFAGenerateEpsilonTransition(ctxt, atom->stop, to);
#ifdef DV
	} else if ((to == NULL) && (atom->quant != XML_REGEXP_QUANT_RANGE) &&
		   (atom->quant != XML_REGEXP_QUANT_ONCE)) {
	    to = xmlRegNewState(ctxt);
	    xmlRegStatePush(ctxt, to);
	    ctxt->state = to;
	    xmlFAGenerateEpsilonTransition(ctxt, atom->stop, to);
#endif
	}
	switch (atom->quant) {
	    case XML_REGEXP_QUANT_OPT:
		atom->quant = XML_REGEXP_QUANT_ONCE;
		/*
		 * transition done to the state after end of atom.
		 *      1. set transition from atom start to new state
		 *      2. set transition from atom end to this state.
		 */
                if (to == NULL) {
                    xmlFAGenerateEpsilonTransition(ctxt, atom->start, 0);
                    xmlFAGenerateEpsilonTransition(ctxt, atom->stop,
                                                   ctxt->state);
                } else {
                    xmlFAGenerateEpsilonTransition(ctxt, atom->start, to);
                }
		break;
	    case XML_REGEXP_QUANT_MULT:
		atom->quant = XML_REGEXP_QUANT_ONCE;
		xmlFAGenerateEpsilonTransition(ctxt, atom->start, atom->stop);
		xmlFAGenerateEpsilonTransition(ctxt, atom->stop, atom->start);
		break;
	    case XML_REGEXP_QUANT_PLUS:
		atom->quant = XML_REGEXP_QUANT_ONCE;
		xmlFAGenerateEpsilonTransition(ctxt, atom->stop, atom->start);
		break;
	    case XML_REGEXP_QUANT_RANGE: {
		int counter;
		xmlRegStatePtr inter, newstate;

		/*
		 * create the final state now if needed
		 */
		if (to != NULL) {
		    newstate = to;
		} else {
		    newstate = xmlRegNewState(ctxt);
		    xmlRegStatePush(ctxt, newstate);
		}

		/*
		 * The principle here is to use counted transition
		 * to avoid explosion in the number of states in the
		 * graph. This is clearly more complex but should not
		 * be exploitable at runtime.
		 */
		if ((atom->min == 0) && (atom->start0 == NULL)) {
		    xmlRegAtomPtr copy;
		    /*
		     * duplicate a transition based on atom to count next
		     * occurences after 1. We cannot loop to atom->start
		     * directly because we need an epsilon transition to
		     * newstate.
		     */
		     /* ???? For some reason it seems we never reach that
		        case, I suppose this got optimized out before when
			building the automata */
		    copy = xmlRegCopyAtom(ctxt, atom);
		    if (copy == NULL)
		        return(-1);
		    copy->quant = XML_REGEXP_QUANT_ONCE;
		    copy->min = 0;
		    copy->max = 0;

		    if (xmlFAGenerateTransitions(ctxt, atom->start, NULL, copy)
		        < 0)
			return(-1);
		    inter = ctxt->state;
		    counter = xmlRegGetCounter(ctxt);
		    ctxt->counters[counter].min = atom->min - 1;
		    ctxt->counters[counter].max = atom->max - 1;
		    /* count the number of times we see it again */
		    xmlFAGenerateCountedEpsilonTransition(ctxt, inter,
						   atom->stop, counter);
		    /* allow a way out based on the count */
		    xmlFAGenerateCountedTransition(ctxt, inter,
			                           newstate, counter);
		    /* and also allow a direct exit for 0 */
		    xmlFAGenerateEpsilonTransition(ctxt, atom->start,
		                                   newstate);
		} else {
		    /*
		     * either we need the atom at least once or there
		     * is an atom->start0 allowing to easilly plug the
		     * epsilon transition.
		     */
		    counter = xmlRegGetCounter(ctxt);
		    ctxt->counters[counter].min = atom->min - 1;
		    ctxt->counters[counter].max = atom->max - 1;
		    /* count the number of times we see it again */
		    xmlFAGenerateCountedEpsilonTransition(ctxt, atom->stop,
						   atom->start, counter);
		    /* allow a way out based on the count */
		    xmlFAGenerateCountedTransition(ctxt, atom->stop,
			                           newstate, counter);
		    /* and if needed allow a direct exit for 0 */
		    if (atom->min == 0)
			xmlFAGenerateEpsilonTransition(ctxt, atom->start0,
						       newstate);

		}
		atom->min = 0;
		atom->max = 0;
		atom->quant = XML_REGEXP_QUANT_ONCE;
		ctxt->state = newstate;
	    }
	    default:
		break;
	}
	return(0);
    }
    if ((atom->min == 0) && (atom->max == 0) &&
               (atom->quant == XML_REGEXP_QUANT_RANGE)) {
        /*
	 * we can discard the atom and generate an epsilon transition instead
	 */
	if (to == NULL) {
	    to = xmlRegNewState(ctxt);
	    if (to != NULL)
		xmlRegStatePush(ctxt, to);
	    else {
		return(-1);
	    }
	}
	xmlFAGenerateEpsilonTransition(ctxt, from, to);
	ctxt->state = to;
	xmlRegFreeAtom(atom);
	return(0);
    }
    if (to == NULL) {
	to = xmlRegNewState(ctxt);
	if (to != NULL)
	    xmlRegStatePush(ctxt, to);
	else {
	    return(-1);
	}
    }
    end = to;
    if ((atom->quant == XML_REGEXP_QUANT_MULT) ||
        (atom->quant == XML_REGEXP_QUANT_PLUS)) {
	/*
	 * Do not pollute the target state by adding transitions from
	 * it as it is likely to be the shared target of multiple branches.
	 * So isolate with an epsilon transition.
	 */
        xmlRegStatePtr tmp;

	tmp = xmlRegNewState(ctxt);
	if (tmp != NULL)
	    xmlRegStatePush(ctxt, tmp);
	else {
	    return(-1);
	}
	xmlFAGenerateEpsilonTransition(ctxt, tmp, to);
	to = tmp;
    }
    if (xmlRegAtomPush(ctxt, atom) < 0) {
	return(-1);
    }
    xmlRegStateAddTrans(ctxt, from, atom, to, -1, -1);
    ctxt->state = end;
    switch (atom->quant) {
	case XML_REGEXP_QUANT_OPT:
	    atom->quant = XML_REGEXP_QUANT_ONCE;
	    xmlFAGenerateEpsilonTransition(ctxt, from, to);
	    break;
	case XML_REGEXP_QUANT_MULT:
	    atom->quant = XML_REGEXP_QUANT_ONCE;
	    xmlFAGenerateEpsilonTransition(ctxt, from, to);
	    xmlRegStateAddTrans(ctxt, to, atom, to, -1, -1);
	    break;
	case XML_REGEXP_QUANT_PLUS:
	    atom->quant = XML_REGEXP_QUANT_ONCE;
	    xmlRegStateAddTrans(ctxt, to, atom, to, -1, -1);
	    break;
	case XML_REGEXP_QUANT_RANGE:
#if DV_test
	    if (atom->min == 0) {
		xmlFAGenerateEpsilonTransition(ctxt, from, to);
	    }
#endif
	    break;
	default:
	    break;
    }
    return(0);
}

/**
 * xmlFAReduceEpsilonTransitions:
 * @ctxt:  a regexp parser context
 * @fromnr:  the from state
 * @tonr:  the to state
 * @counter:  should that transition be associated to a counted
 *
 */
static void
xmlFAReduceEpsilonTransitions(xmlRegParserCtxtPtr ctxt, int fromnr,
	                      int tonr, int counter) {
    int transnr;
    xmlRegStatePtr from;
    xmlRegStatePtr to;

#ifdef DEBUG_REGEXP_GRAPH
    printf("xmlFAReduceEpsilonTransitions(%d, %d)\n", fromnr, tonr);
#endif
    from = ctxt->states[fromnr];
    if (from == NULL)
	return;
    to = ctxt->states[tonr];
    if (to == NULL)
	return;
    if ((to->mark == XML_REGEXP_MARK_START) ||
	(to->mark == XML_REGEXP_MARK_VISITED))
	return;

    to->mark = XML_REGEXP_MARK_VISITED;
    if (to->type == XML_REGEXP_FINAL_STATE) {
#ifdef DEBUG_REGEXP_GRAPH
	printf("State %d is final, so %d becomes final\n", tonr, fromnr);
#endif
	from->type = XML_REGEXP_FINAL_STATE;
    }
    for (transnr = 0;transnr < to->nbTrans;transnr++) {
        if (to->trans[transnr].to < 0)
	    continue;
	if (to->trans[transnr].atom == NULL) {
	    /*
	     * Don't remove counted transitions
	     * Don't loop either
	     */
	    if (to->trans[transnr].to != fromnr) {
		if (to->trans[transnr].count >= 0) {
		    int newto = to->trans[transnr].to;

		    xmlRegStateAddTrans(ctxt, from, NULL,
					ctxt->states[newto],
					-1, to->trans[transnr].count);
		} else {
#ifdef DEBUG_REGEXP_GRAPH
		    printf("Found epsilon trans %d from %d to %d\n",
			   transnr, tonr, to->trans[transnr].to);
#endif
		    if (to->trans[transnr].counter >= 0) {
			xmlFAReduceEpsilonTransitions(ctxt, fromnr,
					      to->trans[transnr].to,
					      to->trans[transnr].counter);
		    } else {
			xmlFAReduceEpsilonTransitions(ctxt, fromnr,
					      to->trans[transnr].to,
					      counter);
		    }
		}
	    }
	} else {
	    int newto = to->trans[transnr].to;

	    if (to->trans[transnr].counter >= 0) {
		xmlRegStateAddTrans(ctxt, from, to->trans[transnr].atom,
				    ctxt->states[newto],
				    to->trans[transnr].counter, -1);
	    } else {
		xmlRegStateAddTrans(ctxt, from, to->trans[transnr].atom,
				    ctxt->states[newto], counter, -1);
	    }
	}
    }
    to->mark = XML_REGEXP_MARK_NORMAL;
}

/**
 * xmlFAEliminateSimpleEpsilonTransitions:
 * @ctxt:  a regexp parser context
 *
 * Eliminating general epsilon transitions can get costly in the general
 * algorithm due to the large amount of generated new transitions and
 * associated comparisons. However for simple epsilon transition used just
 * to separate building blocks when generating the automata this can be
 * reduced to state elimination:
 *    - if there exists an epsilon from X to Y
 *    - if there is no other transition from X
 * then X and Y are semantically equivalent and X can be eliminated
 * If X is the start state then make Y the start state, else replace the
 * target of all transitions to X by transitions to Y.
 */
static void
xmlFAEliminateSimpleEpsilonTransitions(xmlRegParserCtxtPtr ctxt) {
    int statenr, i, j, newto;
    xmlRegStatePtr state, tmp;

    for (statenr = 0;statenr < ctxt->nbStates;statenr++) {
	state = ctxt->states[statenr];
	if (state == NULL)
	    continue;
	if (state->nbTrans != 1)
	    continue;
	if (state->type == XML_REGEXP_UNREACH_STATE)
	    continue;
	/* is the only transition out a basic transition */
	if ((state->trans[0].atom == NULL) &&
	    (state->trans[0].to >= 0) &&
	    (state->trans[0].to != statenr) &&
	    (state->trans[0].counter < 0) &&
	    (state->trans[0].count < 0)) {
	    newto = state->trans[0].to;

            if (state->type == XML_REGEXP_START_STATE) {
#ifdef DEBUG_REGEXP_GRAPH
		printf("Found simple epsilon trans from start %d to %d\n",
		       statenr, newto);
#endif
            } else {
#ifdef DEBUG_REGEXP_GRAPH
		printf("Found simple epsilon trans from %d to %d\n",
		       statenr, newto);
#endif
	        for (i = 0;i < state->nbTransTo;i++) {
		    tmp = ctxt->states[state->transTo[i]];
		    for (j = 0;j < tmp->nbTrans;j++) {
			if (tmp->trans[j].to == statenr) {
#ifdef DEBUG_REGEXP_GRAPH
			    printf("Changed transition %d on %d to go to %d\n",
				   j, tmp->no, newto);
#endif
			    tmp->trans[j].to = -1;
			    xmlRegStateAddTrans(ctxt, tmp, tmp->trans[j].atom,
			    			ctxt->states[newto],
					        tmp->trans[j].counter,
						tmp->trans[j].count);
			}
		    }
		}
		if (state->type == XML_REGEXP_FINAL_STATE)
		    ctxt->states[newto]->type = XML_REGEXP_FINAL_STATE;
		/* eliminate the transition completely */
		state->nbTrans = 0;

                state->type = XML_REGEXP_UNREACH_STATE;

	    }

	}
    }
}
/**
 * xmlFAEliminateEpsilonTransitions:
 * @ctxt:  a regexp parser context
 *
 */
static void
xmlFAEliminateEpsilonTransitions(xmlRegParserCtxtPtr ctxt) {
    int statenr, transnr;
    xmlRegStatePtr state;
    int has_epsilon;

    if (ctxt->states == NULL) return;

    /*
     * Eliminate simple epsilon transition and the associated unreachable
     * states.
     */
    xmlFAEliminateSimpleEpsilonTransitions(ctxt);
    for (statenr = 0;statenr < ctxt->nbStates;statenr++) {
	state = ctxt->states[statenr];
	if ((state != NULL) && (state->type == XML_REGEXP_UNREACH_STATE)) {
#ifdef DEBUG_REGEXP_GRAPH
	    printf("Removed unreachable state %d\n", statenr);
#endif
	    xmlRegFreeState(state);
	    ctxt->states[statenr] = NULL;
	}
    }

    has_epsilon = 0;

    /*
     * Build the completed transitions bypassing the epsilons
     * Use a marking algorithm to avoid loops
     * Mark sink states too.
     * Process from the latests states backward to the start when
     * there is long cascading epsilon chains this minimize the
     * recursions and transition compares when adding the new ones
     */
    for (statenr = ctxt->nbStates - 1;statenr >= 0;statenr--) {
	state = ctxt->states[statenr];
	if (state == NULL)
	    continue;
	if ((state->nbTrans == 0) &&
	    (state->type != XML_REGEXP_FINAL_STATE)) {
	    state->type = XML_REGEXP_SINK_STATE;
	}
	for (transnr = 0;transnr < state->nbTrans;transnr++) {
	    if ((state->trans[transnr].atom == NULL) &&
		(state->trans[transnr].to >= 0)) {
		if (state->trans[transnr].to == statenr) {
		    state->trans[transnr].to = -1;
#ifdef DEBUG_REGEXP_GRAPH
		    printf("Removed loopback epsilon trans %d on %d\n",
			   transnr, statenr);
#endif
		} else if (state->trans[transnr].count < 0) {
		    int newto = state->trans[transnr].to;

#ifdef DEBUG_REGEXP_GRAPH
		    printf("Found epsilon trans %d from %d to %d\n",
			   transnr, statenr, newto);
#endif
		    has_epsilon = 1;
		    state->trans[transnr].to = -2;
		    state->mark = XML_REGEXP_MARK_START;
		    xmlFAReduceEpsilonTransitions(ctxt, statenr,
				      newto, state->trans[transnr].counter);
		    state->mark = XML_REGEXP_MARK_NORMAL;
#ifdef DEBUG_REGEXP_GRAPH
		} else {
		    printf("Found counted transition %d on %d\n",
			   transnr, statenr);
#endif
	        }
	    }
	}
    }
    /*
     * Eliminate the epsilon transitions
     */
    if (has_epsilon) {
	for (statenr = 0;statenr < ctxt->nbStates;statenr++) {
	    state = ctxt->states[statenr];
	    if (state == NULL)
		continue;
	    for (transnr = 0;transnr < state->nbTrans;transnr++) {
		xmlRegTransPtr trans = &(state->trans[transnr]);
		if ((trans->atom == NULL) &&
		    (trans->count < 0) &&
		    (trans->to >= 0)) {
		    trans->to = -1;
		}
	    }
	}
    }

    /*
     * Use this pass to detect unreachable states too
     */
    for (statenr = 0;statenr < ctxt->nbStates;statenr++) {
	state = ctxt->states[statenr];
	if (state != NULL)
	    state->reached = XML_REGEXP_MARK_NORMAL;
    }
    state = ctxt->states[0];
    if (state != NULL)
	state->reached = XML_REGEXP_MARK_START;
    while (state != NULL) {
	xmlRegStatePtr target = NULL;
	state->reached = XML_REGEXP_MARK_VISITED;
	/*
	 * Mark all states reachable from the current reachable state
	 */
	for (transnr = 0;transnr < state->nbTrans;transnr++) {
	    if ((state->trans[transnr].to >= 0) &&
		((state->trans[transnr].atom != NULL) ||
		 (state->trans[transnr].count >= 0))) {
		int newto = state->trans[transnr].to;

		if (ctxt->states[newto] == NULL)
		    continue;
		if (ctxt->states[newto]->reached == XML_REGEXP_MARK_NORMAL) {
		    ctxt->states[newto]->reached = XML_REGEXP_MARK_START;
		    target = ctxt->states[newto];
		}
	    }
	}

	/*
	 * find the next accessible state not explored
	 */
	if (target == NULL) {
	    for (statenr = 1;statenr < ctxt->nbStates;statenr++) {
		state = ctxt->states[statenr];
		if ((state != NULL) && (state->reached ==
			XML_REGEXP_MARK_START)) {
		    target = state;
		    break;
		}
	    }
	}
	state = target;
    }
    for (statenr = 0;statenr < ctxt->nbStates;statenr++) {
	state = ctxt->states[statenr];
	if ((state != NULL) && (state->reached == XML_REGEXP_MARK_NORMAL)) {
#ifdef DEBUG_REGEXP_GRAPH
	    printf("Removed unreachable state %d\n", statenr);
#endif
	    xmlRegFreeState(state);
	    ctxt->states[statenr] = NULL;
	}
    }

}

static int
xmlFACompareRanges(xmlRegRangePtr range1, xmlRegRangePtr range2) {
    int ret = 0;

    if ((range1->type == XML_REGEXP_RANGES) ||
        (range2->type == XML_REGEXP_RANGES) ||
        (range2->type == XML_REGEXP_SUBREG) ||
        (range1->type == XML_REGEXP_SUBREG) ||
        (range1->type == XML_REGEXP_STRING) ||
        (range2->type == XML_REGEXP_STRING))
	return(-1);

    /* put them in order */
    if (range1->type > range2->type) {
        xmlRegRangePtr tmp;

	tmp = range1;
	range1 = range2;
	range2 = tmp;
    }
    if ((range1->type == XML_REGEXP_ANYCHAR) ||
        (range2->type == XML_REGEXP_ANYCHAR)) {
	ret = 1;
    } else if ((range1->type == XML_REGEXP_EPSILON) ||
               (range2->type == XML_REGEXP_EPSILON)) {
	return(0);
    } else if (range1->type == range2->type) {
        if (range1->type != XML_REGEXP_CHARVAL)
            ret = 1;
        else if ((range1->end < range2->start) ||
	         (range2->end < range1->start))
	    ret = 0;
	else
	    ret = 1;
    } else if (range1->type == XML_REGEXP_CHARVAL) {
        int codepoint;
	int neg = 0;

	/*
	 * just check all codepoints in the range for acceptance,
	 * this is usually way cheaper since done only once at
	 * compilation than testing over and over at runtime or
	 * pushing too many states when evaluating.
	 */
	if (((range1->neg == 0) && (range2->neg != 0)) ||
	    ((range1->neg != 0) && (range2->neg == 0)))
	    neg = 1;

	for (codepoint = range1->start;codepoint <= range1->end ;codepoint++) {
	    ret = xmlRegCheckCharacterRange(range2->type, codepoint,
					    0, range2->start, range2->end,
					    range2->blockName);
	    if (ret < 0)
	        return(-1);
	    if (((neg == 1) && (ret == 0)) ||
	        ((neg == 0) && (ret == 1)))
		return(1);
	}
	return(0);
    } else if ((range1->type == XML_REGEXP_BLOCK_NAME) ||
               (range2->type == XML_REGEXP_BLOCK_NAME)) {
	if (range1->type == range2->type) {
	    ret = xmlStrEqual(range1->blockName, range2->blockName);
	} else {
	    /*
	     * comparing a block range with anything else is way
	     * too costly, and maintining the table is like too much
	     * memory too, so let's force the automata to save state
	     * here.
	     */
	    return(1);
	}
    } else if ((range1->type < XML_REGEXP_LETTER) ||
               (range2->type < XML_REGEXP_LETTER)) {
	if ((range1->type == XML_REGEXP_ANYSPACE) &&
	    (range2->type == XML_REGEXP_NOTSPACE))
	    ret = 0;
	else if ((range1->type == XML_REGEXP_INITNAME) &&
	         (range2->type == XML_REGEXP_NOTINITNAME))
	    ret = 0;
	else if ((range1->type == XML_REGEXP_NAMECHAR) &&
	         (range2->type == XML_REGEXP_NOTNAMECHAR))
	    ret = 0;
	else if ((range1->type == XML_REGEXP_DECIMAL) &&
	         (range2->type == XML_REGEXP_NOTDECIMAL))
	    ret = 0;
	else if ((range1->type == XML_REGEXP_REALCHAR) &&
	         (range2->type == XML_REGEXP_NOTREALCHAR))
	    ret = 0;
	else {
	    /* same thing to limit complexity */
	    return(1);
	}
    } else {
        ret = 0;
        /* range1->type < range2->type here */
        switch (range1->type) {
	    case XML_REGEXP_LETTER:
	         /* all disjoint except in the subgroups */
	         if ((range2->type == XML_REGEXP_LETTER_UPPERCASE) ||
		     (range2->type == XML_REGEXP_LETTER_LOWERCASE) ||
		     (range2->type == XML_REGEXP_LETTER_TITLECASE) ||
		     (range2->type == XML_REGEXP_LETTER_MODIFIER) ||
		     (range2->type == XML_REGEXP_LETTER_OTHERS))
		     ret = 1;
		 break;
	    case XML_REGEXP_MARK:
	         if ((range2->type == XML_REGEXP_MARK_NONSPACING) ||
		     (range2->type == XML_REGEXP_MARK_SPACECOMBINING) ||
		     (range2->type == XML_REGEXP_MARK_ENCLOSING))
		     ret = 1;
		 break;
	    case XML_REGEXP_NUMBER:
	         if ((range2->type == XML_REGEXP_NUMBER_DECIMAL) ||
		     (range2->type == XML_REGEXP_NUMBER_LETTER) ||
		     (range2->type == XML_REGEXP_NUMBER_OTHERS))
		     ret = 1;
		 break;
	    case XML_REGEXP_PUNCT:
	         if ((range2->type == XML_REGEXP_PUNCT_CONNECTOR) ||
		     (range2->type == XML_REGEXP_PUNCT_DASH) ||
		     (range2->type == XML_REGEXP_PUNCT_OPEN) ||
		     (range2->type == XML_REGEXP_PUNCT_CLOSE) ||
		     (range2->type == XML_REGEXP_PUNCT_INITQUOTE) ||
		     (range2->type == XML_REGEXP_PUNCT_FINQUOTE) ||
		     (range2->type == XML_REGEXP_PUNCT_OTHERS))
		     ret = 1;
		 break;
	    case XML_REGEXP_SEPAR:
	         if ((range2->type == XML_REGEXP_SEPAR_SPACE) ||
		     (range2->type == XML_REGEXP_SEPAR_LINE) ||
		     (range2->type == XML_REGEXP_SEPAR_PARA))
		     ret = 1;
		 break;
	    case XML_REGEXP_SYMBOL:
	         if ((range2->type == XML_REGEXP_SYMBOL_MATH) ||
		     (range2->type == XML_REGEXP_SYMBOL_CURRENCY) ||
		     (range2->type == XML_REGEXP_SYMBOL_MODIFIER) ||
		     (range2->type == XML_REGEXP_SYMBOL_OTHERS))
		     ret = 1;
		 break;
	    case XML_REGEXP_OTHER:
	         if ((range2->type == XML_REGEXP_OTHER_CONTROL) ||
		     (range2->type == XML_REGEXP_OTHER_FORMAT) ||
		     (range2->type == XML_REGEXP_OTHER_PRIVATE))
		     ret = 1;
		 break;
            default:
	         if ((range2->type >= XML_REGEXP_LETTER) &&
		     (range2->type < XML_REGEXP_BLOCK_NAME))
		     ret = 0;
		 else {
		     /* safety net ! */
		     return(1);
		 }
	}
    }
    if (((range1->neg == 0) && (range2->neg != 0)) ||
        ((range1->neg != 0) && (range2->neg == 0)))
	ret = !ret;
    return(ret);
}

/**
 * xmlFACompareAtomTypes:
 * @type1:  an atom type
 * @type2:  an atom type
 *
 * Compares two atoms type to check whether they intersect in some ways,
 * this is used by xmlFACompareAtoms only
 *
 * Returns 1 if they may intersect and 0 otherwise
 */
static int
xmlFACompareAtomTypes(xmlRegAtomType type1, xmlRegAtomType type2) {
    if ((type1 == XML_REGEXP_EPSILON) ||
        (type1 == XML_REGEXP_CHARVAL) ||
	(type1 == XML_REGEXP_RANGES) ||
	(type1 == XML_REGEXP_SUBREG) ||
	(type1 == XML_REGEXP_STRING) ||
	(type1 == XML_REGEXP_ANYCHAR))
	return(1);
    if ((type2 == XML_REGEXP_EPSILON) ||
        (type2 == XML_REGEXP_CHARVAL) ||
	(type2 == XML_REGEXP_RANGES) ||
	(type2 == XML_REGEXP_SUBREG) ||
	(type2 == XML_REGEXP_STRING) ||
	(type2 == XML_REGEXP_ANYCHAR))
	return(1);

    if (type1 == type2) return(1);

    /* simplify subsequent compares by making sure type1 < type2 */
    if (type1 > type2) {
        xmlRegAtomType tmp = type1;
	type1 = type2;
	type2 = tmp;
    }
    switch (type1) {
        case XML_REGEXP_ANYSPACE: /* \s */
	    /* can't be a letter, number, mark, pontuation, symbol */
	    if ((type2 == XML_REGEXP_NOTSPACE) ||
		((type2 >= XML_REGEXP_LETTER) &&
		 (type2 <= XML_REGEXP_LETTER_OTHERS)) ||
	        ((type2 >= XML_REGEXP_NUMBER) &&
		 (type2 <= XML_REGEXP_NUMBER_OTHERS)) ||
	        ((type2 >= XML_REGEXP_MARK) &&
		 (type2 <= XML_REGEXP_MARK_ENCLOSING)) ||
	        ((type2 >= XML_REGEXP_PUNCT) &&
		 (type2 <= XML_REGEXP_PUNCT_OTHERS)) ||
	        ((type2 >= XML_REGEXP_SYMBOL) &&
		 (type2 <= XML_REGEXP_SYMBOL_OTHERS))
	        ) return(0);
	    break;
        case XML_REGEXP_NOTSPACE: /* \S */
	    break;
        case XML_REGEXP_INITNAME: /* \l */
	    /* can't be a number, mark, separator, pontuation, symbol or other */
	    if ((type2 == XML_REGEXP_NOTINITNAME) ||
	        ((type2 >= XML_REGEXP_NUMBER) &&
		 (type2 <= XML_REGEXP_NUMBER_OTHERS)) ||
	        ((type2 >= XML_REGEXP_MARK) &&
		 (type2 <= XML_REGEXP_MARK_ENCLOSING)) ||
	        ((type2 >= XML_REGEXP_SEPAR) &&
		 (type2 <= XML_REGEXP_SEPAR_PARA)) ||
	        ((type2 >= XML_REGEXP_PUNCT) &&
		 (type2 <= XML_REGEXP_PUNCT_OTHERS)) ||
	        ((type2 >= XML_REGEXP_SYMBOL) &&
		 (type2 <= XML_REGEXP_SYMBOL_OTHERS)) ||
	        ((type2 >= XML_REGEXP_OTHER) &&
		 (type2 <= XML_REGEXP_OTHER_NA))
		) return(0);
	    break;
        case XML_REGEXP_NOTINITNAME: /* \L */
	    break;
        case XML_REGEXP_NAMECHAR: /* \c */
	    /* can't be a mark, separator, pontuation, symbol or other */
	    if ((type2 == XML_REGEXP_NOTNAMECHAR) ||
	        ((type2 >= XML_REGEXP_MARK) &&
		 (type2 <= XML_REGEXP_MARK_ENCLOSING)) ||
	        ((type2 >= XML_REGEXP_PUNCT) &&
		 (type2 <= XML_REGEXP_PUNCT_OTHERS)) ||
	        ((type2 >= XML_REGEXP_SEPAR) &&
		 (type2 <= XML_REGEXP_SEPAR_PARA)) ||
	        ((type2 >= XML_REGEXP_SYMBOL) &&
		 (type2 <= XML_REGEXP_SYMBOL_OTHERS)) ||
	        ((type2 >= XML_REGEXP_OTHER) &&
		 (type2 <= XML_REGEXP_OTHER_NA))
		) return(0);
	    break;
        case XML_REGEXP_NOTNAMECHAR: /* \C */
	    break;
        case XML_REGEXP_DECIMAL: /* \d */
	    /* can't be a letter, mark, separator, pontuation, symbol or other */
	    if ((type2 == XML_REGEXP_NOTDECIMAL) ||
	        (type2 == XML_REGEXP_REALCHAR) ||
		((type2 >= XML_REGEXP_LETTER) &&
		 (type2 <= XML_REGEXP_LETTER_OTHERS)) ||
	        ((type2 >= XML_REGEXP_MARK) &&
		 (type2 <= XML_REGEXP_MARK_ENCLOSING)) ||
	        ((type2 >= XML_REGEXP_PUNCT) &&
		 (type2 <= XML_REGEXP_PUNCT_OTHERS)) ||
	        ((type2 >= XML_REGEXP_SEPAR) &&
		 (type2 <= XML_REGEXP_SEPAR_PARA)) ||
	        ((type2 >= XML_REGEXP_SYMBOL) &&
		 (type2 <= XML_REGEXP_SYMBOL_OTHERS)) ||
	        ((type2 >= XML_REGEXP_OTHER) &&
		 (type2 <= XML_REGEXP_OTHER_NA))
		)return(0);
	    break;
        case XML_REGEXP_NOTDECIMAL: /* \D */
	    break;
        case XML_REGEXP_REALCHAR: /* \w */
	    /* can't be a mark, separator, pontuation, symbol or other */
	    if ((type2 == XML_REGEXP_NOTDECIMAL) ||
	        ((type2 >= XML_REGEXP_MARK) &&
		 (type2 <= XML_REGEXP_MARK_ENCLOSING)) ||
	        ((type2 >= XML_REGEXP_PUNCT) &&
		 (type2 <= XML_REGEXP_PUNCT_OTHERS)) ||
	        ((type2 >= XML_REGEXP_SEPAR) &&
		 (type2 <= XML_REGEXP_SEPAR_PARA)) ||
	        ((type2 >= XML_REGEXP_SYMBOL) &&
		 (type2 <= XML_REGEXP_SYMBOL_OTHERS)) ||
	        ((type2 >= XML_REGEXP_OTHER) &&
		 (type2 <= XML_REGEXP_OTHER_NA))
		)return(0);
	    break;
        case XML_REGEXP_NOTREALCHAR: /* \W */
	    break;
	/*
	 * at that point we know both type 1 and type2 are from
	 * character categories are ordered and are different,
	 * it becomes simple because this is a partition
	 */
        case XML_REGEXP_LETTER:
	    if (type2 <= XML_REGEXP_LETTER_OTHERS)
	        return(1);
	    return(0);
        case XML_REGEXP_LETTER_UPPERCASE:
        case XML_REGEXP_LETTER_LOWERCASE:
        case XML_REGEXP_LETTER_TITLECASE:
        case XML_REGEXP_LETTER_MODIFIER:
        case XML_REGEXP_LETTER_OTHERS:
	    return(0);
        case XML_REGEXP_MARK:
	    if (type2 <= XML_REGEXP_MARK_ENCLOSING)
	        return(1);
	    return(0);
        case XML_REGEXP_MARK_NONSPACING:
        case XML_REGEXP_MARK_SPACECOMBINING:
        case XML_REGEXP_MARK_ENCLOSING:
	    return(0);
        case XML_REGEXP_NUMBER:
	    if (type2 <= XML_REGEXP_NUMBER_OTHERS)
	        return(1);
	    return(0);
        case XML_REGEXP_NUMBER_DECIMAL:
        case XML_REGEXP_NUMBER_LETTER:
        case XML_REGEXP_NUMBER_OTHERS:
	    return(0);
        case XML_REGEXP_PUNCT:
	    if (type2 <= XML_REGEXP_PUNCT_OTHERS)
	        return(1);
	    return(0);
        case XML_REGEXP_PUNCT_CONNECTOR:
        case XML_REGEXP_PUNCT_DASH:
        case XML_REGEXP_PUNCT_OPEN:
        case XML_REGEXP_PUNCT_CLOSE:
        case XML_REGEXP_PUNCT_INITQUOTE:
        case XML_REGEXP_PUNCT_FINQUOTE:
        case XML_REGEXP_PUNCT_OTHERS:
	    return(0);
        case XML_REGEXP_SEPAR:
	    if (type2 <= XML_REGEXP_SEPAR_PARA)
	        return(1);
	    return(0);
        case XML_REGEXP_SEPAR_SPACE:
        case XML_REGEXP_SEPAR_LINE:
        case XML_REGEXP_SEPAR_PARA:
	    return(0);
        case XML_REGEXP_SYMBOL:
	    if (type2 <= XML_REGEXP_SYMBOL_OTHERS)
	        return(1);
	    return(0);
        case XML_REGEXP_SYMBOL_MATH:
        case XML_REGEXP_SYMBOL_CURRENCY:
        case XML_REGEXP_SYMBOL_MODIFIER:
        case XML_REGEXP_SYMBOL_OTHERS:
	    return(0);
        case XML_REGEXP_OTHER:
	    if (type2 <= XML_REGEXP_OTHER_NA)
	        return(1);
	    return(0);
        case XML_REGEXP_OTHER_CONTROL:
        case XML_REGEXP_OTHER_FORMAT:
        case XML_REGEXP_OTHER_PRIVATE:
        case XML_REGEXP_OTHER_NA:
	    return(0);
	default:
	    break;
    }
    return(1);
}

/**
 * xmlFAEqualAtoms:
 * @atom1:  an atom
 * @atom2:  an atom
 * @deep: if not set only compare string pointers
 *
 * Compares two atoms to check whether they are the same exactly
 * this is used to remove equivalent transitions
 *
 * Returns 1 if same and 0 otherwise
 */
static int
xmlFAEqualAtoms(xmlRegAtomPtr atom1, xmlRegAtomPtr atom2, int deep) {
    int ret = 0;

    if (atom1 == atom2)
	return(1);
    if ((atom1 == NULL) || (atom2 == NULL))
	return(0);

    if (atom1->type != atom2->type)
        return(0);
    switch (atom1->type) {
        case XML_REGEXP_EPSILON:
	    ret = 0;
	    break;
        case XML_REGEXP_STRING:
            if (!deep)
                ret = (atom1->valuep == atom2->valuep);
            else
                ret = xmlStrEqual((xmlChar *)atom1->valuep,
                                  (xmlChar *)atom2->valuep);
	    break;
        case XML_REGEXP_CHARVAL:
	    ret = (atom1->codepoint == atom2->codepoint);
	    break;
	case XML_REGEXP_RANGES:
	    /* too hard to do in the general case */
	    ret = 0;
	default:
	    break;
    }
    return(ret);
}

/**
 * xmlFACompareAtoms:
 * @atom1:  an atom
 * @atom2:  an atom
 * @deep: if not set only compare string pointers
 *
 * Compares two atoms to check whether they intersect in some ways,
 * this is used by xmlFAComputesDeterminism and xmlFARecurseDeterminism only
 *
 * Returns 1 if yes and 0 otherwise
 */
static int
xmlFACompareAtoms(xmlRegAtomPtr atom1, xmlRegAtomPtr atom2, int deep) {
    int ret = 1;

    if (atom1 == atom2)
	return(1);
    if ((atom1 == NULL) || (atom2 == NULL))
	return(0);

    if ((atom1->type == XML_REGEXP_ANYCHAR) ||
        (atom2->type == XML_REGEXP_ANYCHAR))
	return(1);

    if (atom1->type > atom2->type) {
	xmlRegAtomPtr tmp;
	tmp = atom1;
	atom1 = atom2;
	atom2 = tmp;
    }
    if (atom1->type != atom2->type) {
        ret = xmlFACompareAtomTypes(atom1->type, atom2->type);
	/* if they can't intersect at the type level break now */
	if (ret == 0)
	    return(0);
    }
    switch (atom1->type) {
        case XML_REGEXP_STRING:
            if (!deep)
                ret = (atom1->valuep != atom2->valuep);
            else
                ret = xmlRegStrEqualWildcard((xmlChar *)atom1->valuep,
                                             (xmlChar *)atom2->valuep);
	    break;
        case XML_REGEXP_EPSILON:
	    goto not_determinist;
        case XML_REGEXP_CHARVAL:
	    if (atom2->type == XML_REGEXP_CHARVAL) {
		ret = (atom1->codepoint == atom2->codepoint);
	    } else {
	        ret = xmlRegCheckCharacter(atom2, atom1->codepoint);
		if (ret < 0)
		    ret = 1;
	    }
	    break;
        case XML_REGEXP_RANGES:
	    if (atom2->type == XML_REGEXP_RANGES) {
	        int i, j, res;
		xmlRegRangePtr r1, r2;

		/*
		 * need to check that none of the ranges eventually matches
		 */
		for (i = 0;i < atom1->nbRanges;i++) {
		    for (j = 0;j < atom2->nbRanges;j++) {
			r1 = atom1->ranges[i];
			r2 = atom2->ranges[j];
			res = xmlFACompareRanges(r1, r2);
			if (res == 1) {
			    ret = 1;
			    goto done;
			}
		    }
		}
		ret = 0;
	    }
	    break;
	default:
	    goto not_determinist;
    }
done:
    if (atom1->neg != atom2->neg) {
        ret = !ret;
    }
    if (ret == 0)
        return(0);
not_determinist:
    return(1);
}

/**
 * xmlFARecurseDeterminism:
 * @ctxt:  a regexp parser context
 *
 * Check whether the associated regexp is determinist,
 * should be called after xmlFAEliminateEpsilonTransitions()
 *
 */
static int
xmlFARecurseDeterminism(xmlRegParserCtxtPtr ctxt, xmlRegStatePtr state,
	                 int to, xmlRegAtomPtr atom) {
    int ret = 1;
    int res;
    int transnr, nbTrans;
    xmlRegTransPtr t1;
    int deep = 1;

    if (state == NULL)
	return(ret);

    if (ctxt->flags & AM_AUTOMATA_RNG)
        deep = 0;

    /*
     * don't recurse on transitions potentially added in the course of
     * the elimination.
     */
    nbTrans = state->nbTrans;
    for (transnr = 0;transnr < nbTrans;transnr++) {
	t1 = &(state->trans[transnr]);
	/*
	 * check transitions conflicting with the one looked at
	 */
	if (t1->atom == NULL) {
	    if (t1->to < 0)
		continue;
	    res = xmlFARecurseDeterminism(ctxt, ctxt->states[t1->to],
		                           to, atom);
	    if (res == 0) {
	        ret = 0;
		/* t1->nd = 1; */
	    }
	    continue;
	}
	if (t1->to != to)
	    continue;
	if (xmlFACompareAtoms(t1->atom, atom, deep)) {
	    ret = 0;
	    /* mark the transition as non-deterministic */
	    t1->nd = 1;
	}
    }
    return(ret);
}

/**
 * xmlFAComputesDeterminism:
 * @ctxt:  a regexp parser context
 *
 * Check whether the associated regexp is determinist,
 * should be called after xmlFAEliminateEpsilonTransitions()
 *
 */
static int
xmlFAComputesDeterminism(xmlRegParserCtxtPtr ctxt) {
    int statenr, transnr;
    xmlRegStatePtr state;
    xmlRegTransPtr t1, t2, last;
    int i;
    int ret = 1;
    int deep = 1;

#ifdef DEBUG_REGEXP_GRAPH
    printf("xmlFAComputesDeterminism\n");
    xmlRegPrintCtxt(stdout, ctxt);
#endif
    if (ctxt->determinist != -1)
	return(ctxt->determinist);

    if (ctxt->flags & AM_AUTOMATA_RNG)
        deep = 0;

    /*
     * First cleanup the automata removing cancelled transitions
     */
    for (statenr = 0;statenr < ctxt->nbStates;statenr++) {
	state = ctxt->states[statenr];
	if (state == NULL)
	    continue;
	if (state->nbTrans < 2)
	    continue;
	for (transnr = 0;transnr < state->nbTrans;transnr++) {
	    t1 = &(state->trans[transnr]);
	    /*
	     * Determinism checks in case of counted or all transitions
	     * will have to be handled separately
	     */
	    if (t1->atom == NULL) {
		/* t1->nd = 1; */
		continue;
	    }
	    if (t1->to == -1) /* eliminated */
		continue;
	    for (i = 0;i < transnr;i++) {
		t2 = &(state->trans[i]);
		if (t2->to == -1) /* eliminated */
		    continue;
		if (t2->atom != NULL) {
		    if (t1->to == t2->to) {
                        /*
                         * Here we use deep because we want to keep the
                         * transitions which indicate a conflict
                         */
			if (xmlFAEqualAtoms(t1->atom, t2->atom, deep) &&
                            (t1->counter == t2->counter) &&
                            (t1->count == t2->count))
			    t2->to = -1; /* eliminated */
		    }
		}
	    }
	}
    }

    /*
     * Check for all states that there aren't 2 transitions
     * with the same atom and a different target.
     */
    for (statenr = 0;statenr < ctxt->nbStates;statenr++) {
	state = ctxt->states[statenr];
	if (state == NULL)
	    continue;
	if (state->nbTrans < 2)
	    continue;
	last = NULL;
	for (transnr = 0;transnr < state->nbTrans;transnr++) {
	    t1 = &(state->trans[transnr]);
	    /*
	     * Determinism checks in case of counted or all transitions
	     * will have to be handled separately
	     */
	    if (t1->atom == NULL) {
		continue;
	    }
	    if (t1->to == -1) /* eliminated */
		continue;
	    for (i = 0;i < transnr;i++) {
		t2 = &(state->trans[i]);
		if (t2->to == -1) /* eliminated */
		    continue;
		if (t2->atom != NULL) {
                    /*
                     * But here we don't use deep because we want to
                     * find transitions which indicate a conflict
                     */
		    if (xmlFACompareAtoms(t1->atom, t2->atom, 1)) {
			ret = 0;
			/* mark the transitions as non-deterministic ones */
			t1->nd = 1;
			t2->nd = 1;
			last = t1;
		    }
		} else if (t1->to != -1) {
		    /*
		     * do the closure in case of remaining specific
		     * epsilon transitions like choices or all
		     */
		    ret = xmlFARecurseDeterminism(ctxt, ctxt->states[t1->to],
						   t2->to, t2->atom);
		    /* don't shortcut the computation so all non deterministic
		       transition get marked down
		    if (ret == 0)
			return(0);
		     */
		    if (ret == 0) {
			t1->nd = 1;
			/* t2->nd = 1; */
			last = t1;
		    }
		}
	    }
	    /* don't shortcut the computation so all non deterministic
	       transition get marked down
	    if (ret == 0)
		break; */
	}

	/*
	 * mark specifically the last non-deterministic transition
	 * from a state since there is no need to set-up rollback
	 * from it
	 */
	if (last != NULL) {
	    last->nd = 2;
	}

	/* don't shortcut the computation so all non deterministic
	   transition get marked down
	if (ret == 0)
	    break; */
    }

    ctxt->determinist = ret;
    return(ret);
}

/************************************************************************
 * 									*
 *	Routines to check input against transition atoms		*
 * 									*
 ************************************************************************/

static int
xmlRegCheckCharacterRange(xmlRegAtomType type, int codepoint, int neg,
	                  int start, int end, const xmlChar *blockName) {
    int ret = 0;

    switch (type) {
        case XML_REGEXP_STRING:
        case XML_REGEXP_SUBREG:
        case XML_REGEXP_RANGES:
        case XML_REGEXP_EPSILON:
	    return(-1);
        case XML_REGEXP_ANYCHAR:
	    ret = ((codepoint != '\n') && (codepoint != '\r'));
	    break;
        case XML_REGEXP_CHARVAL:
	    ret = ((codepoint >= start) && (codepoint <= end));
	    break;
        case XML_REGEXP_NOTSPACE:
	    neg = !neg;
        case XML_REGEXP_ANYSPACE:
	    ret = ((codepoint == '\n') || (codepoint == '\r') ||
		   (codepoint == '\t') || (codepoint == ' '));
	    break;
        case XML_REGEXP_NOTINITNAME:
	    neg = !neg;
        case XML_REGEXP_INITNAME:
	    ret = (xmlIsLetter(codepoint) ||
		   (codepoint == '_') || (codepoint == ':'));
	    break;
        case XML_REGEXP_NOTNAMECHAR:
	    neg = !neg;
        case XML_REGEXP_NAMECHAR:
	    ret = (xmlIsLetter(codepoint) || xmlIsDigit(codepoint) ||
		   (codepoint == '.') || (codepoint == '-') ||
		   (codepoint == '_') || (codepoint == ':') ||
		   xmlIsCombining(codepoint) || xmlIsExtender(codepoint));
	    break;
        case XML_REGEXP_NOTDECIMAL:
	    neg = !neg;
        case XML_REGEXP_DECIMAL:
	    ret = xmlUCSIsCatNd(codepoint);
	    break;
        case XML_REGEXP_REALCHAR:
	    neg = !neg;
        case XML_REGEXP_NOTREALCHAR:
	    ret = xmlUCSIsCatP(codepoint);
	    if (ret == 0)
		ret = xmlUCSIsCatZ(codepoint);
	    if (ret == 0)
		ret = xmlUCSIsCatC(codepoint);
	    break;
        case XML_REGEXP_LETTER:
	    ret = xmlUCSIsCatL(codepoint);
	    break;
        case XML_REGEXP_LETTER_UPPERCASE:
	    ret = xmlUCSIsCatLu(codepoint);
	    break;
        case XML_REGEXP_LETTER_LOWERCASE:
	    ret = xmlUCSIsCatLl(codepoint);
	    break;
        case XML_REGEXP_LETTER_TITLECASE:
	    ret = xmlUCSIsCatLt(codepoint);
	    break;
        case XML_REGEXP_LETTER_MODIFIER:
	    ret = xmlUCSIsCatLm(codepoint);
	    break;
        case XML_REGEXP_LETTER_OTHERS:
	    ret = xmlUCSIsCatLo(codepoint);
	    break;
        case XML_REGEXP_MARK:
	    ret = xmlUCSIsCatM(codepoint);
	    break;
        case XML_REGEXP_MARK_NONSPACING:
	    ret = xmlUCSIsCatMn(codepoint);
	    break;
        case XML_REGEXP_MARK_SPACECOMBINING:
	    ret = xmlUCSIsCatMc(codepoint);
	    break;
        case XML_REGEXP_MARK_ENCLOSING:
	    ret = xmlUCSIsCatMe(codepoint);
	    break;
        case XML_REGEXP_NUMBER:
	    ret = xmlUCSIsCatN(codepoint);
	    break;
        case XML_REGEXP_NUMBER_DECIMAL:
	    ret = xmlUCSIsCatNd(codepoint);
	    break;
        case XML_REGEXP_NUMBER_LETTER:
	    ret = xmlUCSIsCatNl(codepoint);
	    break;
        case XML_REGEXP_NUMBER_OTHERS:
	    ret = xmlUCSIsCatNo(codepoint);
	    break;
        case XML_REGEXP_PUNCT:
	    ret = xmlUCSIsCatP(codepoint);
	    break;
        case XML_REGEXP_PUNCT_CONNECTOR:
	    ret = xmlUCSIsCatPc(codepoint);
	    break;
        case XML_REGEXP_PUNCT_DASH:
	    ret = xmlUCSIsCatPd(codepoint);
	    break;
        case XML_REGEXP_PUNCT_OPEN:
	    ret = xmlUCSIsCatPs(codepoint);
	    break;
        case XML_REGEXP_PUNCT_CLOSE:
	    ret = xmlUCSIsCatPe(codepoint);
	    break;
        case XML_REGEXP_PUNCT_INITQUOTE:
	    ret = xmlUCSIsCatPi(codepoint);
	    break;
        case XML_REGEXP_PUNCT_FINQUOTE:
	    ret = xmlUCSIsCatPf(codepoint);
	    break;
        case XML_REGEXP_PUNCT_OTHERS:
	    ret = xmlUCSIsCatPo(codepoint);
	    break;
        case XML_REGEXP_SEPAR:
	    ret = xmlUCSIsCatZ(codepoint);
	    break;
        case XML_REGEXP_SEPAR_SPACE:
	    ret = xmlUCSIsCatZs(codepoint);
	    break;
        case XML_REGEXP_SEPAR_LINE:
	    ret = xmlUCSIsCatZl(codepoint);
	    break;
        case XML_REGEXP_SEPAR_PARA:
	    ret = xmlUCSIsCatZp(codepoint);
	    break;
        case XML_REGEXP_SYMBOL:
	    ret = xmlUCSIsCatS(codepoint);
	    break;
        case XML_REGEXP_SYMBOL_MATH:
	    ret = xmlUCSIsCatSm(codepoint);
	    break;
        case XML_REGEXP_SYMBOL_CURRENCY:
	    ret = xmlUCSIsCatSc(codepoint);
	    break;
        case XML_REGEXP_SYMBOL_MODIFIER:
	    ret = xmlUCSIsCatSk(codepoint);
	    break;
        case XML_REGEXP_SYMBOL_OTHERS:
	    ret = xmlUCSIsCatSo(codepoint);
	    break;
        case XML_REGEXP_OTHER:
	    ret = xmlUCSIsCatC(codepoint);
	    break;
        case XML_REGEXP_OTHER_CONTROL:
	    ret = xmlUCSIsCatCc(codepoint);
	    break;
        case XML_REGEXP_OTHER_FORMAT:
	    ret = xmlUCSIsCatCf(codepoint);
	    break;
        case XML_REGEXP_OTHER_PRIVATE:
	    ret = xmlUCSIsCatCo(codepoint);
	    break;
        case XML_REGEXP_OTHER_NA:
	    /* ret = xmlUCSIsCatCn(codepoint); */
	    /* Seems it doesn't exist anymore in recent Unicode releases */
	    ret = 0;
	    break;
        case XML_REGEXP_BLOCK_NAME:
	    ret = xmlUCSIsBlock(codepoint, (const char *) blockName);
	    break;
    }
    if (neg)
	return(!ret);
    return(ret);
}

static int
xmlRegCheckCharacter(xmlRegAtomPtr atom, int codepoint) {
    int i, ret = 0;
    xmlRegRangePtr range;

    if ((atom == NULL) || (!xmlIsChar(codepoint)))
	return(-1);

    switch (atom->type) {
        case XML_REGEXP_SUBREG:
        case XML_REGEXP_EPSILON:
	    return(-1);
        case XML_REGEXP_CHARVAL:
            return(codepoint == atom->codepoint);
        case XML_REGEXP_RANGES: {
	    int accept = 0;

	    for (i = 0;i < atom->nbRanges;i++) {
		range = atom->ranges[i];
		if (range->neg == 2) {
		    ret = xmlRegCheckCharacterRange(range->type, codepoint,
						0, range->start, range->end,
						range->blockName);
		    if (ret != 0)
			return(0); /* excluded char */
		} else if (range->neg) {
		    ret = xmlRegCheckCharacterRange(range->type, codepoint,
						0, range->start, range->end,
						range->blockName);
		    if (ret == 0)
		        accept = 1;
		    else
		        return(0);
		} else {
		    ret = xmlRegCheckCharacterRange(range->type, codepoint,
						0, range->start, range->end,
						range->blockName);
		    if (ret != 0)
			accept = 1; /* might still be excluded */
		}
	    }
	    return(accept);
	}
        case XML_REGEXP_STRING:
          /*TODO XML_REGEXP_STRING */
	    return(-1);
        case XML_REGEXP_ANYCHAR:
        case XML_REGEXP_ANYSPACE:
        case XML_REGEXP_NOTSPACE:
        case XML_REGEXP_INITNAME:
        case XML_REGEXP_NOTINITNAME:
        case XML_REGEXP_NAMECHAR:
        case XML_REGEXP_NOTNAMECHAR:
        case XML_REGEXP_DECIMAL:
        case XML_REGEXP_NOTDECIMAL:
        case XML_REGEXP_REALCHAR:
        case XML_REGEXP_NOTREALCHAR:
        case XML_REGEXP_LETTER:
        case XML_REGEXP_LETTER_UPPERCASE:
        case XML_REGEXP_LETTER_LOWERCASE:
        case XML_REGEXP_LETTER_TITLECASE:
        case XML_REGEXP_LETTER_MODIFIER:
        case XML_REGEXP_LETTER_OTHERS:
        case XML_REGEXP_MARK:
        case XML_REGEXP_MARK_NONSPACING:
        case XML_REGEXP_MARK_SPACECOMBINING:
        case XML_REGEXP_MARK_ENCLOSING:
        case XML_REGEXP_NUMBER:
        case XML_REGEXP_NUMBER_DECIMAL:
        case XML_REGEXP_NUMBER_LETTER:
        case XML_REGEXP_NUMBER_OTHERS:
        case XML_REGEXP_PUNCT:
        case XML_REGEXP_PUNCT_CONNECTOR:
        case XML_REGEXP_PUNCT_DASH:
        case XML_REGEXP_PUNCT_OPEN:
        case XML_REGEXP_PUNCT_CLOSE:
        case XML_REGEXP_PUNCT_INITQUOTE:
        case XML_REGEXP_PUNCT_FINQUOTE:
        case XML_REGEXP_PUNCT_OTHERS:
        case XML_REGEXP_SEPAR:
        case XML_REGEXP_SEPAR_SPACE:
        case XML_REGEXP_SEPAR_LINE:
        case XML_REGEXP_SEPAR_PARA:
        case XML_REGEXP_SYMBOL:
        case XML_REGEXP_SYMBOL_MATH:
        case XML_REGEXP_SYMBOL_CURRENCY:
        case XML_REGEXP_SYMBOL_MODIFIER:
        case XML_REGEXP_SYMBOL_OTHERS:
        case XML_REGEXP_OTHER:
        case XML_REGEXP_OTHER_CONTROL:
        case XML_REGEXP_OTHER_FORMAT:
        case XML_REGEXP_OTHER_PRIVATE:
        case XML_REGEXP_OTHER_NA:
	case XML_REGEXP_BLOCK_NAME:
	    ret = xmlRegCheckCharacterRange(atom->type, codepoint, 0, 0, 0,
		                            (const xmlChar *)atom->valuep);
	    if (atom->neg)
		ret = !ret;
	    break;
    }
    return(ret);
}

/************************************************************************
 * 									*
 *	Saving and restoring state of an execution context		*
 * 									*
 ************************************************************************/

#ifdef DEBUG_REGEXP_EXEC
static void
xmlFARegDebugExec(xmlRegExecCtxtPtr exec) {
    printf("state: %d:%d:idx %d", exec->state->no, exec->transno, exec->index);
    if (exec->inputStack != NULL) {
	int i;
	printf(": ");
	for (i = 0;(i < 3) && (i < exec->inputStackNr);i++)
	    printf("%s ", (const char *)
	           exec->inputStack[exec->inputStackNr - (i + 1)].value);
    } else {
	printf(": %s", &(exec->inputString[exec->index]));
    }
    printf("\n");
}
#endif

static void
xmlFARegExecSave(xmlRegExecCtxtPtr exec) {
#ifdef DEBUG_REGEXP_EXEC
    printf("saving ");
    exec->transno++;
    xmlFARegDebugExec(exec);
    exec->transno--;
#endif
#ifdef MAX_PUSH
    if (exec->nbPush > MAX_PUSH) {
        return;
    }
    exec->nbPush++;
#endif

    if (exec->maxRollbacks == 0) {
	exec->maxRollbacks = 4;
	exec->rollbacks = (xmlRegExecRollback *) REGEXP_MALLOC(exec->maxRollbacks *
		                             sizeof(xmlRegExecRollback));
	if (exec->rollbacks == NULL) {
	    xmlRegexpErrMemory(NULL, "saving regexp");
	    exec->maxRollbacks = 0;
	    return;
	}
	memset(exec->rollbacks, 0,
	       exec->maxRollbacks * sizeof(xmlRegExecRollback));
    } else if (exec->nbRollbacks >= exec->maxRollbacks) {
	xmlRegExecRollback *tmp;
	int len = exec->maxRollbacks;

	exec->maxRollbacks *= 2;
	tmp = (xmlRegExecRollback *) REGEXP_REALLOC(exec->rollbacks,
			exec->maxRollbacks * sizeof(xmlRegExecRollback));
	if (tmp == NULL) {
	    xmlRegexpErrMemory(NULL, "saving regexp");
	    exec->maxRollbacks /= 2;
	    return;
	}
	exec->rollbacks = tmp;
	tmp = &exec->rollbacks[len];
	memset(tmp, 0, (exec->maxRollbacks - len) * sizeof(xmlRegExecRollback));
    }
    exec->rollbacks[exec->nbRollbacks].state = exec->state;
    exec->rollbacks[exec->nbRollbacks].index = exec->index;
    exec->rollbacks[exec->nbRollbacks].nextbranch = exec->transno + 1;
    if (exec->comp->nbCounters > 0) {
	if (exec->rollbacks[exec->nbRollbacks].counts == NULL) {
	    exec->rollbacks[exec->nbRollbacks].counts = (int *)
		REGEXP_MALLOC(exec->comp->nbCounters * sizeof(int));
	    if (exec->rollbacks[exec->nbRollbacks].counts == NULL) {
		xmlRegexpErrMemory(NULL, "saving regexp");
		exec->status = -5;
		return;
	    }
	}
	memcpy(exec->rollbacks[exec->nbRollbacks].counts, exec->counts,
	       exec->comp->nbCounters * sizeof(int));
    }
    exec->nbRollbacks++;
}

static void
xmlFARegExecRollBack(xmlRegExecCtxtPtr exec) {
    if (exec->nbRollbacks <= 0) {
	exec->status = -1;
#ifdef DEBUG_REGEXP_EXEC
	printf("rollback failed on empty stack\n");
#endif
	return;
    }
    exec->nbRollbacks--;
    exec->state = exec->rollbacks[exec->nbRollbacks].state;
    exec->index = exec->rollbacks[exec->nbRollbacks].index;
    exec->transno = exec->rollbacks[exec->nbRollbacks].nextbranch;
    if (exec->comp->nbCounters > 0) {
	if (exec->rollbacks[exec->nbRollbacks].counts == NULL) {
#ifdef DEBUG_REGEXP_EXEC
	    fprintf(stderr, "exec save: allocation failed");
#endif
	    exec->status = -6;
	    return;
	}
	memcpy(exec->counts, exec->rollbacks[exec->nbRollbacks].counts,
	       exec->comp->nbCounters * sizeof(int));
    }

#ifdef DEBUG_REGEXP_EXEC
    printf("restored ");
    xmlFARegDebugExec(exec);
#endif
}

/************************************************************************
 * 									*
 *	Verifier, running an input against a compiled regexp		*
 * 									*
 ************************************************************************/

static int
xmlFARegExec(xmlRegexpPtr comp, const xmlChar *content) {
    xmlRegExecCtxt execval;
    xmlRegExecCtxtPtr exec = &execval;
    int ret, codepoint = 0, len, deter;

    exec->inputString = content;
    exec->index = 0;
    exec->nbPush = 0;
    exec->determinist = 1;
    exec->maxRollbacks = 0;
    exec->nbRollbacks = 0;
    exec->rollbacks = NULL;
    exec->status = 0;
    exec->comp = comp;
    exec->state = comp->states[0];
    exec->transno = 0;
    exec->transcount = 0;
    exec->inputStack = NULL;
    exec->inputStackMax = 0;
    if (comp->nbCounters > 0) {
	exec->counts = (int *) REGEXP_MALLOC(comp->nbCounters * sizeof(int));
	if (exec->counts == NULL) {
	    xmlRegexpErrMemory(NULL, "running regexp");
	    return(-1);
	}
        memset(exec->counts, 0, comp->nbCounters * sizeof(int));
    } else
	exec->counts = NULL;
    while ((exec->status == 0) &&
	   ((exec->inputString[exec->index] != 0) ||
	    ((exec->state != NULL) &&
	     (exec->state->type != XML_REGEXP_FINAL_STATE)))) {
	xmlRegTransPtr trans;
	xmlRegAtomPtr atom;

	/*
	 * If end of input on non-terminal state, rollback, however we may
	 * still have epsilon like transition for counted transitions
	 * on counters, in that case don't break too early.  Additionally,
	 * if we are working on a range like "AB{0,2}", where B is not present,
	 * we don't want to break.
	 */
	len = 1;
	if ((exec->inputString[exec->index] == 0) && (exec->counts == NULL)) {
	    /*
	     * if there is a transition, we must check if
	     *  atom allows minOccurs of 0
	     */
	    if (exec->transno < exec->state->nbTrans) {
	        trans = &exec->state->trans[exec->transno];
		if (trans->to >=0) {
		    atom = trans->atom;
		    if (!((atom->min == 0) && (atom->max > 0)))
		        goto rollback;
		}
	    } else
	        goto rollback;
	}

	exec->transcount = 0;
	for (;exec->transno < exec->state->nbTrans;exec->transno++) {
	    trans = &exec->state->trans[exec->transno];
	    if (trans->to < 0)
		continue;
	    atom = trans->atom;
	    ret = 0;
	    deter = 1;
	    if (trans->count >= 0) {
		int count;
		xmlRegCounterPtr counter;

		if (exec->counts == NULL) {
		    exec->status = -1;
		    goto error;
		}
		/*
		 * A counted transition.
		 */

		count = exec->counts[trans->count];
		counter = &exec->comp->counters[trans->count];
#ifdef DEBUG_REGEXP_EXEC
		printf("testing count %d: val %d, min %d, max %d\n",
		       trans->count, count, counter->min,  counter->max);
#endif
		ret = ((count >= counter->min) && (count <= counter->max));
		if ((ret) && (counter->min != counter->max))
		    deter = 0;
	    } else if (atom == NULL) {
#ifdef DEBUG_REGEXP_EXEC
		fprintf(stderr, "epsilon transition left at runtime\n");
#endif
		exec->status = -2;
		break;
	    } else if (exec->inputString[exec->index] != 0) {
                codepoint = CUR_SCHAR(&(exec->inputString[exec->index]), len);
		ret = xmlRegCheckCharacter(atom, codepoint);
		if ((ret == 1) && (atom->min >= 0) && (atom->max > 0)) {
		    xmlRegStatePtr to = comp->states[trans->to];

		    /*
		     * this is a multiple input sequence
		     * If there is a counter associated increment it now.
		     * before potentially saving and rollback
		     * do not increment if the counter is already over the
		     * maximum limit in which case get to next transition
		     */
		    if (trans->counter >= 0) {
			xmlRegCounterPtr counter;

			if ((exec->counts == NULL) ||
			    (exec->comp == NULL) ||
			    (exec->comp->counters == NULL)) {
			    exec->status = -1;
			    goto error;
			}
			counter = &exec->comp->counters[trans->counter];
			if (exec->counts[trans->counter] >= counter->max)
			    continue; /* for loop on transitions */

#ifdef DEBUG_REGEXP_EXEC
			printf("Increasing count %d\n", trans->counter);
#endif
			exec->counts[trans->counter]++;
		    }
		    if (exec->state->nbTrans > exec->transno + 1) {
			xmlFARegExecSave(exec);
		    }
		    exec->transcount = 1;
		    do {
			/*
			 * Try to progress as much as possible on the input
			 */
			if (exec->transcount == atom->max) {
			    break;
			}
			exec->index += len;
			/*
			 * End of input: stop here
			 */
			if (exec->inputString[exec->index] == 0) {
			    exec->index -= len;
			    break;
			}
			if (exec->transcount >= atom->min) {
			    int transno = exec->transno;
			    xmlRegStatePtr state = exec->state;

			    /*
			     * The transition is acceptable save it
			     */
			    exec->transno = -1; /* trick */
			    exec->state = to;
			    xmlFARegExecSave(exec);
			    exec->transno = transno;
			    exec->state = state;
			}
			codepoint = CUR_SCHAR(&(exec->inputString[exec->index]),
				              len);
			ret = xmlRegCheckCharacter(atom, codepoint);
			exec->transcount++;
		    } while (ret == 1);
		    if (exec->transcount < atom->min)
			ret = 0;

		    /*
		     * If the last check failed but one transition was found
		     * possible, rollback
		     */
		    if (ret < 0)
			ret = 0;
		    if (ret == 0) {
			goto rollback;
		    }
		    if (trans->counter >= 0) {
			if (exec->counts == NULL) {
			    exec->status = -1;
			    goto error;
			}
#ifdef DEBUG_REGEXP_EXEC
			printf("Decreasing count %d\n", trans->counter);
#endif
			exec->counts[trans->counter]--;
		    }
		} else if ((ret == 0) && (atom->min == 0) && (atom->max > 0)) {
		    /*
		     * we don't match on the codepoint, but minOccurs of 0
		     * says that's ok.  Setting len to 0 inhibits stepping
		     * over the codepoint.
		     */
		    exec->transcount = 1;
		    len = 0;
		    ret = 1;
		}
	    } else if ((atom->min == 0) && (atom->max > 0)) {
	        /* another spot to match when minOccurs is 0 */
		exec->transcount = 1;
		len = 0;
		ret = 1;
	    }
	    if (ret == 1) {
		if ((trans->nd == 1) ||
		    ((trans->count >= 0) && (deter == 0) &&
		     (exec->state->nbTrans > exec->transno + 1))) {
#ifdef DEBUG_REGEXP_EXEC
		    if (trans->nd == 1)
		        printf("Saving on nd transition atom %d for %c at %d\n",
			       trans->atom->no, codepoint, exec->index);
		    else
		        printf("Saving on counted transition count %d for %c at %d\n",
			       trans->count, codepoint, exec->index);
#endif
		    xmlFARegExecSave(exec);
		}
		if (trans->counter >= 0) {
		    xmlRegCounterPtr counter;

                    /* make sure we don't go over the counter maximum value */
		    if ((exec->counts == NULL) ||
			(exec->comp == NULL) ||
			(exec->comp->counters == NULL)) {
			exec->status = -1;
			goto error;
		    }
		    counter = &exec->comp->counters[trans->counter];
		    if (exec->counts[trans->counter] >= counter->max)
			continue; /* for loop on transitions */
#ifdef DEBUG_REGEXP_EXEC
		    printf("Increasing count %d\n", trans->counter);
#endif
		    exec->counts[trans->counter]++;
		}
		if ((trans->count >= 0) &&
		    (trans->count < REGEXP_ALL_COUNTER)) {
		    if (exec->counts == NULL) {
		        exec->status = -1;
			goto error;
		    }
#ifdef DEBUG_REGEXP_EXEC
		    printf("resetting count %d on transition\n",
		           trans->count);
#endif
		    exec->counts[trans->count] = 0;
		}
#ifdef DEBUG_REGEXP_EXEC
		printf("entering state %d\n", trans->to);
#endif
		exec->state = comp->states[trans->to];
		exec->transno = 0;
		if (trans->atom != NULL) {
		    exec->index += len;
		}
		goto progress;
	    } else if (ret < 0) {
		exec->status = -4;
		break;
	    }
	}
	if ((exec->transno != 0) || (exec->state->nbTrans == 0)) {
rollback:
	    /*
	     * Failed to find a way out
	     */
	    exec->determinist = 0;
#ifdef DEBUG_REGEXP_EXEC
	    printf("rollback from state %d on %d:%c\n", exec->state->no,
	           codepoint,codepoint);
#endif
	    xmlFARegExecRollBack(exec);
	}
progress:
	continue;
    }
error:
    if (exec->rollbacks != NULL) {
	if (exec->counts != NULL) {
	    int i;

	    for (i = 0;i < exec->maxRollbacks;i++)
		if (exec->rollbacks[i].counts != NULL)
		    REGEXP_FREE(exec->rollbacks[i].counts);
	}
	REGEXP_FREE(exec->rollbacks);
    }
    if (exec->counts != NULL)
	REGEXP_FREE(exec->counts);
    if (exec->status == 0)
	return(1);
    if (exec->status == -1) {
	if (exec->nbPush > MAX_PUSH)
	    return(-1);
	return(0);
    }
    return(exec->status);
}

/************************************************************************
 * 									*
 *	Progressive interface to the verifier one atom at a time	*
 * 									*
 ************************************************************************/

/**
 * xmlRegStrEqualWildcard:
 * @expStr:  the string to be evaluated
 * @valStr:  the validation string
 *
 * Checks if both strings are equal or have the same content. "*"
 * can be used as a wildcard in @valStr; "|" is used as a seperator of
 * substrings in both @expStr and @valStr.
 *
 * Returns 1 if the comparison is satisfied and the number of substrings
 * is equal, 0 otherwise.
 */

static int
xmlRegStrEqualWildcard(const xmlChar *expStr, const xmlChar *valStr) {
    if (expStr == valStr) return(1);
    if (expStr == NULL) return(0);
    if (valStr == NULL) return(0);
    do {
	/*
	* Eval if we have a wildcard for the current item.
	*/
        if (*expStr != *valStr) {
	    /* if one of them starts with a wildcard make valStr be it */
	    if (*valStr == '*') {
	        const xmlChar *tmp;

		tmp = valStr;
		valStr = expStr;
		expStr = tmp;
	    }
	    if ((*valStr != 0) && (*expStr != 0) && (*expStr++ == '*')) {
		do {
		    if (*valStr == XML_REG_STRING_SEPARATOR)
			break;
		    valStr++;
		} while (*valStr != 0);
		continue;
	    } else
		return(0);
	}
	expStr++;
	valStr++;
    } while (*valStr != 0);
    if (*expStr != 0)
	return (0);
    else
	return (1);
}

/************************************************************************
 * 									*
 *	Parser for the Schemas Datatype Regular Expressions		*
 *	http://www.w3.org/TR/2001/REC-xmlschema-2-20010502/#regexs	*
 * 									*
 ************************************************************************/

/**
 * xmlFAIsChar:
 * @ctxt:  a regexp parser context
 *
 * [10]   Char   ::=   [^.\?*+()|#x5B#x5D]
 */
static int
xmlFAIsChar(xmlRegParserCtxtPtr ctxt) {
    int cur;
    int len;

    cur = CUR_SCHAR(ctxt->cur, len);
    if ((cur == '.') || (cur == '\\') || (cur == '?') ||
	(cur == '*') || (cur == '+') || (cur == '(') ||
	(cur == ')') || (cur == '|') || (cur == 0x5B) ||
	(cur == 0x5D) || (cur == 0))
	return(-1);
    return(cur);
}

/**
 * xmlFAParseCharProp:
 * @ctxt:  a regexp parser context
 *
 * [27]   charProp   ::=   IsCategory | IsBlock
 * [28]   IsCategory ::= Letters | Marks | Numbers | Punctuation |
 *                       Separators | Symbols | Others
 * [29]   Letters   ::=   'L' [ultmo]?
 * [30]   Marks   ::=   'M' [nce]?
 * [31]   Numbers   ::=   'N' [dlo]?
 * [32]   Punctuation   ::=   'P' [cdseifo]?
 * [33]   Separators   ::=   'Z' [slp]?
 * [34]   Symbols   ::=   'S' [mcko]?
 * [35]   Others   ::=   'C' [cfon]?
 * [36]   IsBlock   ::=   'Is' [a-zA-Z0-9#x2D]+
 */
static void
xmlFAParseCharProp(xmlRegParserCtxtPtr ctxt) {
    int cur;
    xmlRegAtomType type = (xmlRegAtomType) 0;
    xmlChar *blockName = NULL;

    cur = CUR;
    if (cur == 'L') {
	NEXT;
	cur = CUR;
	if (cur == 'u') {
	    NEXT;
	    type = XML_REGEXP_LETTER_UPPERCASE;
	} else if (cur == 'l') {
	    NEXT;
	    type = XML_REGEXP_LETTER_LOWERCASE;
	} else if (cur == 't') {
	    NEXT;
	    type = XML_REGEXP_LETTER_TITLECASE;
	} else if (cur == 'm') {
	    NEXT;
	    type = XML_REGEXP_LETTER_MODIFIER;
	} else if (cur == 'o') {
	    NEXT;
	    type = XML_REGEXP_LETTER_OTHERS;
	} else {
	    type = XML_REGEXP_LETTER;
	}
    } else if (cur == 'M') {
	NEXT;
	cur = CUR;
	if (cur == 'n') {
	    NEXT;
	    /* nonspacing */
	    type = XML_REGEXP_MARK_NONSPACING;
	} else if (cur == 'c') {
	    NEXT;
	    /* spacing combining */
	    type = XML_REGEXP_MARK_SPACECOMBINING;
	} else if (cur == 'e') {
	    NEXT;
	    /* enclosing */
	    type = XML_REGEXP_MARK_ENCLOSING;
	} else {
	    /* all marks */
	    type = XML_REGEXP_MARK;
	}
    } else if (cur == 'N') {
	NEXT;
	cur = CUR;
	if (cur == 'd') {
	    NEXT;
	    /* digital */
	    type = XML_REGEXP_NUMBER_DECIMAL;
	} else if (cur == 'l') {
	    NEXT;
	    /* letter */
	    type = XML_REGEXP_NUMBER_LETTER;
	} else if (cur == 'o') {
	    NEXT;
	    /* other */
	    type = XML_REGEXP_NUMBER_OTHERS;
	} else {
	    /* all numbers */
	    type = XML_REGEXP_NUMBER;
	}
    } else if (cur == 'P') {
	NEXT;
	cur = CUR;
	if (cur == 'c') {
	    NEXT;
	    /* connector */
	    type = XML_REGEXP_PUNCT_CONNECTOR;
	} else if (cur == 'd') {
	    NEXT;
	    /* dash */
	    type = XML_REGEXP_PUNCT_DASH;
	} else if (cur == 's') {
	    NEXT;
	    /* open */
	    type = XML_REGEXP_PUNCT_OPEN;
	} else if (cur == 'e') {
	    NEXT;
	    /* close */
	    type = XML_REGEXP_PUNCT_CLOSE;
	} else if (cur == 'i') {
	    NEXT;
	    /* initial quote */
	    type = XML_REGEXP_PUNCT_INITQUOTE;
	} else if (cur == 'f') {
	    NEXT;
	    /* final quote */
	    type = XML_REGEXP_PUNCT_FINQUOTE;
	} else if (cur == 'o') {
	    NEXT;
	    /* other */
	    type = XML_REGEXP_PUNCT_OTHERS;
	} else {
	    /* all punctuation */
	    type = XML_REGEXP_PUNCT;
	}
    } else if (cur == 'Z') {
	NEXT;
	cur = CUR;
	if (cur == 's') {
	    NEXT;
	    /* space */
	    type = XML_REGEXP_SEPAR_SPACE;
	} else if (cur == 'l') {
	    NEXT;
	    /* line */
	    type = XML_REGEXP_SEPAR_LINE;
	} else if (cur == 'p') {
	    NEXT;
	    /* paragraph */
	    type = XML_REGEXP_SEPAR_PARA;
	} else {
	    /* all separators */
	    type = XML_REGEXP_SEPAR;
	}
    } else if (cur == 'S') {
	NEXT;
	cur = CUR;
	if (cur == 'm') {
	    NEXT;
	    type = XML_REGEXP_SYMBOL_MATH;
	    /* math */
	} else if (cur == 'c') {
	    NEXT;
	    type = XML_REGEXP_SYMBOL_CURRENCY;
	    /* currency */
	} else if (cur == 'k') {
	    NEXT;
	    type = XML_REGEXP_SYMBOL_MODIFIER;
	    /* modifiers */
	} else if (cur == 'o') {
	    NEXT;
	    type = XML_REGEXP_SYMBOL_OTHERS;
	    /* other */
	} else {
	    /* all symbols */
	    type = XML_REGEXP_SYMBOL;
	}
    } else if (cur == 'C') {
	NEXT;
	cur = CUR;
	if (cur == 'c') {
	    NEXT;
	    /* control */
	    type = XML_REGEXP_OTHER_CONTROL;
	} else if (cur == 'f') {
	    NEXT;
	    /* format */
	    type = XML_REGEXP_OTHER_FORMAT;
	} else if (cur == 'o') {
	    NEXT;
	    /* private use */
	    type = XML_REGEXP_OTHER_PRIVATE;
	} else if (cur == 'n') {
	    NEXT;
	    /* not assigned */
	    type = XML_REGEXP_OTHER_NA;
	} else {
	    /* all others */
	    type = XML_REGEXP_OTHER;
	}
    } else if (cur == 'I') {
	const xmlChar *start;
	NEXT;
	cur = CUR;
	if (cur != 's') {
	    REGEXP_ERROR("IsXXXX expected");
	    return;
	}
	NEXT;
	start = ctxt->cur;
	cur = CUR;
	if (((cur >= 'a') && (cur <= 'z')) ||
	    ((cur >= 'A') && (cur <= 'Z')) ||
	    ((cur >= '0') && (cur <= '9')) ||
	    (cur == 0x2D)) {
	    NEXT;
	    cur = CUR;
	    while (((cur >= 'a') && (cur <= 'z')) ||
		((cur >= 'A') && (cur <= 'Z')) ||
		((cur >= '0') && (cur <= '9')) ||
		(cur == 0x2D)) {
		NEXT;
		cur = CUR;
	    }
	}
	type = XML_REGEXP_BLOCK_NAME;
	blockName = xmlStrndup(start, ctxt->cur - start);
    } else {
	REGEXP_ERROR("Unknown char property");
	return;
    }
    if (ctxt->atom == NULL) {
	ctxt->atom = xmlRegNewAtom(ctxt, type);
	if (ctxt->atom != NULL)
	    ctxt->atom->valuep = blockName;
    } else if (ctxt->atom->type == XML_REGEXP_RANGES) {
        xmlRegAtomAddRange(ctxt, ctxt->atom, ctxt->neg,
		           type, 0, 0, blockName);
    }
}

/**
 * xmlFAParseCharClassEsc:
 * @ctxt:  a regexp parser context
 *
 * [23] charClassEsc ::= ( SingleCharEsc | MultiCharEsc | catEsc | complEsc )
 * [24] SingleCharEsc ::= '\' [nrt\|.?*+(){}#x2D#x5B#x5D#x5E]
 * [25] catEsc   ::=   '\p{' charProp '}'
 * [26] complEsc ::=   '\P{' charProp '}'
 * [37] MultiCharEsc ::= '.' | ('\' [sSiIcCdDwW])
 */
static void
xmlFAParseCharClassEsc(xmlRegParserCtxtPtr ctxt) {
    int cur;

    if (CUR == '.') {
	if (ctxt->atom == NULL) {
	    ctxt->atom = xmlRegNewAtom(ctxt, XML_REGEXP_ANYCHAR);
	} else if (ctxt->atom->type == XML_REGEXP_RANGES) {
	    xmlRegAtomAddRange(ctxt, ctxt->atom, ctxt->neg,
			       XML_REGEXP_ANYCHAR, 0, 0, NULL);
	}
	NEXT;
	return;
    }
    if (CUR != '\\') {
	REGEXP_ERROR("Escaped sequence: expecting \\");
	return;
    }
    NEXT;
    cur = CUR;
    if (cur == 'p') {
	NEXT;
	if (CUR != '{') {
	    REGEXP_ERROR("Expecting '{'");
	    return;
	}
	NEXT;
	xmlFAParseCharProp(ctxt);
	if (CUR != '}') {
	    REGEXP_ERROR("Expecting '}'");
	    return;
	}
	NEXT;
    } else if (cur == 'P') {
	NEXT;
	if (CUR != '{') {
	    REGEXP_ERROR("Expecting '{'");
	    return;
	}
	NEXT;
	xmlFAParseCharProp(ctxt);
	ctxt->atom->neg = 1;
	if (CUR != '}') {
	    REGEXP_ERROR("Expecting '}'");
	    return;
	}
	NEXT;
    } else if ((cur == 'n') || (cur == 'r') || (cur == 't') || (cur == '\\') ||
	(cur == '|') || (cur == '.') || (cur == '?') || (cur == '*') ||
	(cur == '+') || (cur == '(') || (cur == ')') || (cur == '{') ||
	(cur == '}') || (cur == 0x2D) || (cur == 0x5B) || (cur == 0x5D) ||
	(cur == 0x5E)) {
	if (ctxt->atom == NULL) {
	    ctxt->atom = xmlRegNewAtom(ctxt, XML_REGEXP_CHARVAL);
	    if (ctxt->atom != NULL) {
	        switch (cur) {
		    case 'n':
		        ctxt->atom->codepoint = '\n';
			break;
		    case 'r':
		        ctxt->atom->codepoint = '\r';
			break;
		    case 't':
		        ctxt->atom->codepoint = '\t';
			break;
		    default:
			ctxt->atom->codepoint = cur;
		}
	    }
	} else if (ctxt->atom->type == XML_REGEXP_RANGES) {
            switch (cur) {
                case 'n':
                    cur = '\n';
                    break;
                case 'r':
                    cur = '\r';
                    break;
                case 't':
                    cur = '\t';
                    break;
            }
	    xmlRegAtomAddRange(ctxt, ctxt->atom, ctxt->neg,
			       XML_REGEXP_CHARVAL, cur, cur, NULL);
	}
	NEXT;
    } else if ((cur == 's') || (cur == 'S') || (cur == 'i') || (cur == 'I') ||
	(cur == 'c') || (cur == 'C') || (cur == 'd') || (cur == 'D') ||
	(cur == 'w') || (cur == 'W')) {
	xmlRegAtomType type = XML_REGEXP_ANYSPACE;

	switch (cur) {
	    case 's':
		type = XML_REGEXP_ANYSPACE;
		break;
	    case 'S':
		type = XML_REGEXP_NOTSPACE;
		break;
	    case 'i':
		type = XML_REGEXP_INITNAME;
		break;
	    case 'I':
		type = XML_REGEXP_NOTINITNAME;
		break;
	    case 'c':
		type = XML_REGEXP_NAMECHAR;
		break;
	    case 'C':
		type = XML_REGEXP_NOTNAMECHAR;
		break;
	    case 'd':
		type = XML_REGEXP_DECIMAL;
		break;
	    case 'D':
		type = XML_REGEXP_NOTDECIMAL;
		break;
	    case 'w':
		type = XML_REGEXP_REALCHAR;
		break;
	    case 'W':
		type = XML_REGEXP_NOTREALCHAR;
		break;
	}
	NEXT;
	if (ctxt->atom == NULL) {
	    ctxt->atom = xmlRegNewAtom(ctxt, type);
	} else if (ctxt->atom->type == XML_REGEXP_RANGES) {
	    xmlRegAtomAddRange(ctxt, ctxt->atom, ctxt->neg,
			       type, 0, 0, NULL);
	}
    } else {
	REGEXP_ERROR("Wrong escape sequence, misuse of character '\\'");
    }
}

/**
 * xmlFAParseCharRange:
 * @ctxt:  a regexp parser context
 *
 * [17]   charRange   ::=     seRange | XmlCharRef | XmlCharIncDash
 * [18]   seRange   ::=   charOrEsc '-' charOrEsc
 * [20]   charOrEsc   ::=   XmlChar | SingleCharEsc
 * [21]   XmlChar   ::=   [^\#x2D#x5B#x5D]
 * [22]   XmlCharIncDash   ::=   [^\#x5B#x5D]
 */
static void
xmlFAParseCharRange(xmlRegParserCtxtPtr ctxt) {
    int cur, len;
    int start = -1;
    int end = -1;

    if (CUR == '\0') {
        REGEXP_ERROR("Expecting ']'");
	return;
    }

    cur = CUR;
    if (cur == '\\') {
	NEXT;
	cur = CUR;
	switch (cur) {
	    case 'n': start = 0xA; break;
	    case 'r': start = 0xD; break;
	    case 't': start = 0x9; break;
	    case '\\': case '|': case '.': case '-': case '^': case '?':
	    case '*': case '+': case '{': case '}': case '(': case ')':
	    case '[': case ']':
		start = cur; break;
	    default:
		REGEXP_ERROR("Invalid escape value");
		return;
	}
	end = start;
        len = 1;
    } else if ((cur != 0x5B) && (cur != 0x5D)) {
        end = start = CUR_SCHAR(ctxt->cur, len);
    } else {
	REGEXP_ERROR("Expecting a char range");
	return;
    }
    /*
     * Since we are "inside" a range, we can assume ctxt->cur is past
     * the start of ctxt->string, and PREV should be safe
     */
    if ((start == '-') && (NXT(1) != ']') && (PREV != '[') && (PREV != '^')) {
	NEXTL(len);
	return;
    }
    NEXTL(len);
    cur = CUR;
    if ((cur != '-') || (NXT(1) == ']')) {
        xmlRegAtomAddRange(ctxt, ctxt->atom, ctxt->neg,
		              XML_REGEXP_CHARVAL, start, end, NULL);
	return;
    }
    NEXT;
    cur = CUR;
    if (cur == '\\') {
	NEXT;
	cur = CUR;
	switch (cur) {
	    case 'n': end = 0xA; break;
	    case 'r': end = 0xD; break;
	    case 't': end = 0x9; break;
	    case '\\': case '|': case '.': case '-': case '^': case '?':
	    case '*': case '+': case '{': case '}': case '(': case ')':
	    case '[': case ']':
		end = cur; break;
	    default:
		REGEXP_ERROR("Invalid escape value");
		return;
	}
        len = 1;
    } else if ((cur != 0x5B) && (cur != 0x5D)) {
        end = CUR_SCHAR(ctxt->cur, len);
    } else {
	REGEXP_ERROR("Expecting the end of a char range");
	return;
    }
    NEXTL(len);
    /* TODO check that the values are acceptable character ranges for XML */
    if (end < start) {
	REGEXP_ERROR("End of range is before start of range");
    } else {
        xmlRegAtomAddRange(ctxt, ctxt->atom, ctxt->neg,
		           XML_REGEXP_CHARVAL, start, end, NULL);
    }
    return;
}

/**
 * xmlFAParsePosCharGroup:
 * @ctxt:  a regexp parser context
 *
 * [14]   posCharGroup ::= ( charRange | charClassEsc  )+
 */
static void
xmlFAParsePosCharGroup(xmlRegParserCtxtPtr ctxt) {
    do {
	if (CUR == '\\') {
	    xmlFAParseCharClassEsc(ctxt);
	} else {
	    xmlFAParseCharRange(ctxt);
	}
    } while ((CUR != ']') && (CUR != '^') && (CUR != '-') &&
             (CUR != 0) && (ctxt->error == 0));
}

/**
 * xmlFAParseCharGroup:
 * @ctxt:  a regexp parser context
 *
 * [13]   charGroup    ::= posCharGroup | negCharGroup | charClassSub
 * [15]   negCharGroup ::= '^' posCharGroup
 * [16]   charClassSub ::= ( posCharGroup | negCharGroup ) '-' charClassExpr
 * [12]   charClassExpr ::= '[' charGroup ']'
 */
static void
xmlFAParseCharGroup(xmlRegParserCtxtPtr ctxt) {
    int n = ctxt->neg;
    while ((CUR != ']') && (ctxt->error == 0)) {
	if (CUR == '^') {
	    int neg = ctxt->neg;

	    NEXT;
	    ctxt->neg = !ctxt->neg;
	    xmlFAParsePosCharGroup(ctxt);
	    ctxt->neg = neg;
	} else if ((CUR == '-') && (NXT(1) == '[')) {
	    int neg = ctxt->neg;
	    ctxt->neg = 2;
	    NEXT;	/* eat the '-' */
	    NEXT;	/* eat the '[' */
	    xmlFAParseCharGroup(ctxt);
	    if (CUR == ']') {
		NEXT;
	    } else {
		REGEXP_ERROR("charClassExpr: ']' expected");
		break;
	    }
	    ctxt->neg = neg;
	    break;
	} else if (CUR != ']') {
	    xmlFAParsePosCharGroup(ctxt);
	}
    }
    ctxt->neg = n;
}

/**
 * xmlFAParseCharClass:
 * @ctxt:  a regexp parser context
 *
 * [11]   charClass   ::=     charClassEsc | charClassExpr
 * [12]   charClassExpr   ::=   '[' charGroup ']'
 */
static void
xmlFAParseCharClass(xmlRegParserCtxtPtr ctxt) {
    if (CUR == '[') {
	NEXT;
	ctxt->atom = xmlRegNewAtom(ctxt, XML_REGEXP_RANGES);
	if (ctxt->atom == NULL)
	    return;
	xmlFAParseCharGroup(ctxt);
	if (CUR == ']') {
	    NEXT;
	} else {
	    REGEXP_ERROR("xmlFAParseCharClass: ']' expected");
	}
    } else {
	xmlFAParseCharClassEsc(ctxt);
    }
}

/**
 * xmlFAParseQuantExact:
 * @ctxt:  a regexp parser context
 *
 * [8]   QuantExact   ::=   [0-9]+
 *
 * Returns 0 if success or -1 in case of error
 */
static int
xmlFAParseQuantExact(xmlRegParserCtxtPtr ctxt) {
    int ret = 0;
    int ok = 0;

    while ((CUR >= '0') && (CUR <= '9')) {
	ret = ret * 10 + (CUR - '0');
	ok = 1;
	NEXT;
    }
    if (ok != 1) {
	return(-1);
    }
    return(ret);
}

/**
 * xmlFAParseQuantifier:
 * @ctxt:  a regexp parser context
 *
 * [4]   quantifier   ::=   [?*+] | ( '{' quantity '}' )
 * [5]   quantity   ::=   quantRange | quantMin | QuantExact
 * [6]   quantRange   ::=   QuantExact ',' QuantExact
 * [7]   quantMin   ::=   QuantExact ','
 * [8]   QuantExact   ::=   [0-9]+
 */
static int
xmlFAParseQuantifier(xmlRegParserCtxtPtr ctxt) {
    int cur;

    cur = CUR;
    if ((cur == '?') || (cur == '*') || (cur == '+')) {
	if (ctxt->atom != NULL) {
	    if (cur == '?')
		ctxt->atom->quant = XML_REGEXP_QUANT_OPT;
	    else if (cur == '*')
		ctxt->atom->quant = XML_REGEXP_QUANT_MULT;
	    else if (cur == '+')
		ctxt->atom->quant = XML_REGEXP_QUANT_PLUS;
	}
	NEXT;
	return(1);
    }
    if (cur == '{') {
	int min = 0, max = 0;

	NEXT;
	cur = xmlFAParseQuantExact(ctxt);
	if (cur >= 0)
	    min = cur;
	if (CUR == ',') {
	    NEXT;
	    if (CUR == '}')
	        max = INT_MAX;
	    else {
	        cur = xmlFAParseQuantExact(ctxt);
	        if (cur >= 0)
		    max = cur;
		else {
		    REGEXP_ERROR("Improper quantifier");
		}
	    }
	}
	if (CUR == '}') {
	    NEXT;
	} else {
	    REGEXP_ERROR("Unterminated quantifier");
	}
	if (max == 0)
	    max = min;
	if (ctxt->atom != NULL) {
	    ctxt->atom->quant = XML_REGEXP_QUANT_RANGE;
	    ctxt->atom->min = min;
	    ctxt->atom->max = max;
	}
	return(1);
    }
    return(0);
}

/**
 * xmlFAParseAtom:
 * @ctxt:  a regexp parser context
 *
 * [9]   atom   ::=   Char | charClass | ( '(' regExp ')' )
 */
static int
xmlFAParseAtom(xmlRegParserCtxtPtr ctxt) {
    int codepoint, len;

    codepoint = xmlFAIsChar(ctxt);
    if (codepoint > 0) {
	ctxt->atom = xmlRegNewAtom(ctxt, XML_REGEXP_CHARVAL);
	if (ctxt->atom == NULL)
	    return(-1);
	codepoint = CUR_SCHAR(ctxt->cur, len);
	ctxt->atom->codepoint = codepoint;
	NEXTL(len);
	return(1);
    } else if (CUR == '|') {
	return(0);
    } else if (CUR == 0) {
	return(0);
    } else if (CUR == ')') {
	return(0);
    } else if (CUR == '(') {
	xmlRegStatePtr start, oldend, start0;

	NEXT;
	/*
	 * this extra Epsilon transition is needed if we count with 0 allowed
	 * unfortunately this can't be known at that point
	 */
	xmlFAGenerateEpsilonTransition(ctxt, ctxt->state, NULL);
	start0 = ctxt->state;
	xmlFAGenerateEpsilonTransition(ctxt, ctxt->state, NULL);
	start = ctxt->state;
	oldend = ctxt->end;
	ctxt->end = NULL;
	ctxt->atom = NULL;
	xmlFAParseRegExp(ctxt, 0);
	if (CUR == ')') {
	    NEXT;
	} else {
	    REGEXP_ERROR("xmlFAParseAtom: expecting ')'");
	}
	ctxt->atom = xmlRegNewAtom(ctxt, XML_REGEXP_SUBREG);
	if (ctxt->atom == NULL)
	    return(-1);
	ctxt->atom->start = start;
	ctxt->atom->start0 = start0;
	ctxt->atom->stop = ctxt->state;
	ctxt->end = oldend;
	return(1);
    } else if ((CUR == '[') || (CUR == '\\') || (CUR == '.')) {
	xmlFAParseCharClass(ctxt);
	return(1);
    }
    return(0);
}

/**
 * xmlFAParsePiece:
 * @ctxt:  a regexp parser context
 *
 * [3]   piece   ::=   atom quantifier?
 */
static int
xmlFAParsePiece(xmlRegParserCtxtPtr ctxt) {
    int ret;

    ctxt->atom = NULL;
    ret = xmlFAParseAtom(ctxt);
    if (ret == 0)
	return(0);
    if (ctxt->atom == NULL) {
	REGEXP_ERROR("internal: no atom generated");
    }
    xmlFAParseQuantifier(ctxt);
    return(1);
}

/**
 * xmlFAParseBranch:
 * @ctxt:  a regexp parser context
 * @to: optional target to the end of the branch
 *
 * @to is used to optimize by removing duplicate path in automata
 * in expressions like (a|b)(c|d)
 *
 * [2]   branch   ::=   piece*
 */
static int
xmlFAParseBranch(xmlRegParserCtxtPtr ctxt, xmlRegStatePtr to) {
    xmlRegStatePtr previous;
    int ret;

    previous = ctxt->state;
    ret = xmlFAParsePiece(ctxt);
    if (ret != 0) {
	if (xmlFAGenerateTransitions(ctxt, previous,
	        (CUR=='|' || CUR==')') ? to : NULL, ctxt->atom) < 0)
	    return(-1);
	previous = ctxt->state;
	ctxt->atom = NULL;
    }
    while ((ret != 0) && (ctxt->error == 0)) {
	ret = xmlFAParsePiece(ctxt);
	if (ret != 0) {
	    if (xmlFAGenerateTransitions(ctxt, previous,
	            (CUR=='|' || CUR==')') ? to : NULL, ctxt->atom) < 0)
		    return(-1);
	    previous = ctxt->state;
	    ctxt->atom = NULL;
	}
    }
    return(0);
}

/**
 * xmlFAParseRegExp:
 * @ctxt:  a regexp parser context
 * @top:  is this the top-level expression ?
 *
 * [1]   regExp   ::=     branch  ( '|' branch )*
 */
static void
xmlFAParseRegExp(xmlRegParserCtxtPtr ctxt, int top) {
    xmlRegStatePtr start, end;

    /* if not top start should have been generated by an epsilon trans */
    start = ctxt->state;
    ctxt->end = NULL;
    xmlFAParseBranch(ctxt, NULL);
    if (top) {
#ifdef DEBUG_REGEXP_GRAPH
	printf("State %d is final\n", ctxt->state->no);
#endif
	ctxt->state->type = XML_REGEXP_FINAL_STATE;
    }
    if (CUR != '|') {
	ctxt->end = ctxt->state;
	return;
    }
    end = ctxt->state;
    while ((CUR == '|') && (ctxt->error == 0)) {
	NEXT;
	ctxt->state = start;
	ctxt->end = NULL;
	xmlFAParseBranch(ctxt, end);
    }
    if (!top) {
	ctxt->state = end;
	ctxt->end = end;
    }
}

/************************************************************************
 * 									*
 * 			The basic API					*
 * 									*
 ************************************************************************/

/**
 * xmlRegexpCompile:
 * @regexp:  a regular expression string
 *
 * Parses a regular expression conforming to XML Schemas Part 2 Datatype
 * Appendix F and builds an automata suitable for testing strings against
 * that regular expression
 *
 * Returns the compiled expression or NULL in case of error
 */
xmlRegexpPtr
xmlRegexpCompile(const xmlChar *regexp) {
    xmlRegexpPtr ret;
    xmlRegParserCtxtPtr ctxt;

    ctxt = xmlRegNewParserCtxt(regexp);
    if (ctxt == NULL)
	return(NULL);

    /* initialize the parser */
    ctxt->end = NULL;
    ctxt->start = ctxt->state = xmlRegNewState(ctxt);
    xmlRegStatePush(ctxt, ctxt->start);

    /* parse the expression building an automata */
    xmlFAParseRegExp(ctxt, 1);
    if (CUR != 0) {
	REGEXP_ERROR("xmlFAParseRegExp: extra characters");
    }
    if (ctxt->error != 0) {
	xmlRegFreeParserCtxt(ctxt);
	return(NULL);
    }
    ctxt->end = ctxt->state;
    ctxt->start->type = XML_REGEXP_START_STATE;
    ctxt->end->type = XML_REGEXP_FINAL_STATE;

    /* remove the Epsilon except for counted transitions */
    xmlFAEliminateEpsilonTransitions(ctxt);


    if (ctxt->error != 0) {
	xmlRegFreeParserCtxt(ctxt);
	return(NULL);
    }
    ret = xmlRegEpxFromParse(ctxt);
    xmlRegFreeParserCtxt(ctxt);
    return(ret);
}

/**
 * xmlRegexpExec:
 * @comp:  the compiled regular expression
 * @content:  the value to check against the regular expression
 *
 * Check if the regular expression generates the value
 *
 * Returns 1 if it matches, 0 if not and a negative value in case of error
 */
int
xmlRegexpExec(xmlRegexpPtr comp, const xmlChar *content) {
    if ((comp == NULL) || (content == NULL))
	return(-1);
    return(xmlFARegExec(comp, content));
}

/**
 * xmlRegexpIsDeterminist:
 * @comp:  the compiled regular expression
 *
 * Check if the regular expression is determinist
 *
 * Returns 1 if it yes, 0 if not and a negative value in case of error
 */
int
xmlRegexpIsDeterminist(xmlRegexpPtr comp) {
    xmlAutomataPtr am;
    int ret;

    if (comp == NULL)
	return(-1);
    if (comp->determinist != -1)
	return(comp->determinist);

    am = xmlNewAutomata();
    if (am->states != NULL) {
	int i;

	for (i = 0;i < am->nbStates;i++)
	    xmlRegFreeState(am->states[i]);
	REGEXP_FREE(am->states);
    }
    am->nbAtoms = comp->nbAtoms;
    am->atoms = comp->atoms;
    am->nbStates = comp->nbStates;
    am->states = comp->states;
    am->determinist = -1;
    am->flags = comp->flags;
    ret = xmlFAComputesDeterminism(am);
    am->atoms = NULL;
    am->states = NULL;
    xmlFreeAutomata(am);
    comp->determinist = ret;
    return(ret);
}

/**
 * xmlRegFreeRegexp:
 * @regexp:  the regexp
 *
 * Free a regexp
 */
void
xmlRegFreeRegexp(xmlRegexpPtr regexp) {
    int i;
    if (regexp == NULL)
	return;

    if (regexp->string != NULL)
	REGEXP_FREE(regexp->string);
    if (regexp->states != NULL) {
	for (i = 0;i < regexp->nbStates;i++)
	    xmlRegFreeState(regexp->states[i]);
	REGEXP_FREE(regexp->states);
    }
    if (regexp->atoms != NULL) {
	for (i = 0;i < regexp->nbAtoms;i++)
	    xmlRegFreeAtom(regexp->atoms[i]);
	REGEXP_FREE(regexp->atoms);
    }
    if (regexp->counters != NULL)
	REGEXP_FREE(regexp->counters);
    if (regexp->compact != NULL)
	REGEXP_FREE(regexp->compact);
    if (regexp->transdata != NULL)
	REGEXP_FREE(regexp->transdata);
    if (regexp->stringMap != NULL) {
	for (i = 0; i < regexp->nbstrings;i++)
	    REGEXP_FREE(regexp->stringMap[i]);
	REGEXP_FREE(regexp->stringMap);
    }

    REGEXP_FREE(regexp);
}

/************************************************************************
 * 									*
 * 			The Automata interface				*
 * 									*
 ************************************************************************/

/**
 * xmlNewAutomata:
 *
 * Create a new automata
 *
 * Returns the new object or NULL in case of failure
 */
static xmlAutomataPtr
xmlNewAutomata(void) {
    xmlAutomataPtr ctxt;

    ctxt = xmlRegNewParserCtxt(NULL);
    if (ctxt == NULL)
	return(NULL);

    /* initialize the parser */
    ctxt->end = NULL;
    ctxt->start = ctxt->state = xmlRegNewState(ctxt);
    if (ctxt->start == NULL) {
	xmlFreeAutomata(ctxt);
	return(NULL);
    }
    ctxt->start->type = XML_REGEXP_START_STATE;
    if (xmlRegStatePush(ctxt, ctxt->start) < 0) {
        xmlRegFreeState(ctxt->start);
	xmlFreeAutomata(ctxt);
	return(NULL);
    }
    ctxt->flags = 0;

    return(ctxt);
}

/**
 * xmlFreeAutomata:
 * @am: an automata
 *
 * Free an automata
 */
static void
xmlFreeAutomata(xmlAutomataPtr am) {
    if (am == NULL)
	return;
    xmlRegFreeParserCtxt(am);
}

#include <xsde/c/post.h>
