/*
 * Summary: regular expressions handling
 * Description: basic API for libxml regular expressions handling used
 *              for XML Schemas and validation.
 *
 * See COPYING for the status of this software.
 */

#ifndef __XML_REGEXP_H__
#define __XML_REGEXP_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * xmlRegexpPtr:
 *
 * A libxml regular expression, they can actually be far more complex
 * thank the POSIX regex expressions.
 */
typedef struct _xmlRegexp xmlRegexp;
typedef xmlRegexp *xmlRegexpPtr;

typedef unsigned char xmlChar;

/*
 * The POSIX like API
 */
xmlRegexpPtr xmlRegexpCompile (const xmlChar *regexp);
void xmlRegFreeRegexp (xmlRegexpPtr regexp);
int xmlRegexpExec (xmlRegexpPtr comp, const xmlChar *value);
int xmlRegexpIsDeterminist (xmlRegexpPtr comp);

#ifdef __cplusplus
}
#endif

#endif /*__XML_REGEXP_H__ */
