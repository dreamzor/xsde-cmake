// file      : xsde/cxx/parser/expat/document.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_EXPAT_DOCUMENT_HXX
#define XSDE_CXX_PARSER_EXPAT_DOCUMENT_HXX

#include <xsde/cxx/config.hxx>

#include <stddef.h> // size_t

#ifdef XSDE_STL
#  include <string>
#endif

#ifdef XSDE_IOSTREAM
#  include <iosfwd>
#endif

#include <xsde/c/expat/expat.h>

// We only support UTF-8 expat for now.
//
#ifdef XML_UNICODE
#error UTF-16 expat (XML_UNICODE defined) is not supported
#endif

#include <xsde/cxx/string.hxx>

#ifdef XSDE_STL
#  include <xsde/cxx/string-sequence-stl.hxx>
#else
#  include <xsde/cxx/string-sequence.hxx>
#endif

#include <xsde/cxx/parser/context.hxx>
#include <xsde/cxx/parser/elements.hxx>

#ifndef XSDE_EXCEPTIONS
#  include <xsde/cxx/parser/error.hxx>
#endif

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace expat
      {
        // Simple auto pointer for Expat's XML_Parser object.
        //
        struct parser_auto_ptr
        {
          ~parser_auto_ptr ();

          explicit
          parser_auto_ptr (XML_Parser = 0);

          parser_auto_ptr&
          operator= (XML_Parser);

        public:
          operator XML_Parser ()
          {
            return parser_;
          }

        private:
          parser_auto_ptr (const parser_auto_ptr&);

          parser_auto_ptr&
          operator= (const parser_auto_ptr&);

        private:
          XML_Parser parser_;
        };

        //
        //
        class document_pimpl
        {
        public:
	  virtual
          ~document_pimpl ();

#ifdef XSDE_POLYMORPHIC
          document_pimpl (parser_base&,
                          const char* root_element_name,
                          bool polymorphic = false);

          document_pimpl (parser_base&,
                          const char* root_element_namespace,
                          const char* root_element_name,
                          bool polymorphic = false);

#ifdef XSDE_STL
          document_pimpl (parser_base&,
                          const std::string& root_element_name,
                          bool polymorphic = false);

          document_pimpl (parser_base&,
                          const std::string& root_element_namespace,
                          const std::string& root_element_name,
                          bool polymorphic = false);

#endif // XSDE_STL
        protected:
          document_pimpl (); // Non-polymorphic parsing.

          document_pimpl (const char* root_element_name);

          document_pimpl (const char* root_element_namespace,
                          const char* root_element_name);

#ifdef XSDE_STL
          document_pimpl (const std::string& root_element_name);

          document_pimpl (const std::string& root_element_namespace,
                          const std::string& root_element_name);
#endif


#else // XSDE_POLYMORPHIC

          document_pimpl (parser_base&,
                          const char* root_element_name);

          document_pimpl (parser_base&,
                          const char* root_element_namespace,
                          const char* root_element_name);

#ifdef XSDE_STL
          document_pimpl (parser_base&,
                          const std::string& root_element_name);

          document_pimpl (parser_base&,
                          const std::string& root_element_namespace,
                          const std::string& root_element_name);
#endif
        protected:
          document_pimpl ();

#endif // XSDE_POLYMORPHIC

          // This function is called to obtain the root element type parser.
          // If the returned pointed is 0 then the whole document content
          // is ignored.
          //
          // The type argument contains the type name and namespace if
          // xsi:type attribute or an element that substitutes the root
          // was specified and 0 otherwise. The type argument is in the
          // form "<name> <namespace>" with the space and namespace part
          // absent if the type does not have a namespace.
          //
          //
#ifdef XSDE_POLYMORPHIC
          virtual parser_base*
          start_root_element (const ro_string& ns,
                              const ro_string& name,
                              const char* type);
#else
          virtual parser_base*
          start_root_element (const ro_string& ns, const ro_string& name);
#endif


          // This function is called to indicate the completion of document
          // parsing. The parser argument contains the pointer returned by
          // start_root_element.
          //
          virtual void
          end_root_element (const ro_string& ns,
                            const ro_string& name,
                            parser_base* parser);

        public:
          // If you override start_root_element() then you will most
          // likely also want to override reset() in order to reset
          // root element parser(s).
          //
          virtual void
          reset ();

#ifdef XSDE_IOSTREAM
        public:
          // Parse a local file. The file is accessed with std::ifstream
          // in binary mode. The std::ios_base::failure exception is used
          // to report io errors (badbit and failbit) if XSDE_EXCEPTIONS
          // is defined. Otherwise error codes are used.
          //
          void
          parse (const char* file);

#ifdef XSDE_STL
          void
          parse (const std::string& file);
#endif

          // Parse std::istream. std::ios_base::failure exception is used
          // to report io errors (badbit and failbit) if XSDE_EXCEPTIONS
          // is defined. Otherwise error codes are used.
          //
          void
          parse (std::istream&);
#endif

        public:
          // Parse a chunk of input. You can call this function multiple
          // times with the last call having the last argument true.
          //
          void
          parse (const void* data, size_t size, bool last);

        public:
          // Low-level Expat-specific parsing API. A typical use case
          // would look like this (pseudo-code):
          //
          // XML_Parser xml_parser (XML_ParserCreateNS (0, ' '));
          //
          // xxx_pimpl root;
          // document_pimpl doc (root, "root");
          //
          // root.pre ();
          // doc.parse_begin (xml_parser);
          //
          // while (more_stuff_to_parse)
          // {
          //    // Call XML_Parse or XML_ParseBuffer:
          //    //
          //    if (XML_Parse (...) != XML_STATUS_ERROR)
          //      break;
          // }
          //
          // doc.parse_end ();
          // result_type result (root.post_xxx ());
          //
          // Notes:
          //
          // 1. If your XML instances use XML namespaces, XML_ParserCreateNS
          //    functions should be used to create the XML parser. Space
          //    (XML_Char (' ')) should be used as a separator (the second
          //    argument to XML_ParserCreateNS).
          //
          // 2. If XML_Parse or XML_ParseBuffer fail, call parse_end to
          //    determine the error which is indicated either via exception
          //    or set as an error code.
          //
          void
          parse_begin (XML_Parser);

          void
          parse_end ();

#ifndef XSDE_EXCEPTIONS
        public:
          const error&
          _error () const;
#endif

        protected:
          void
          set ();

          void
          clear ();

        protected:
          static void XMLCALL
          start_element (void*, const XML_Char*, const XML_Char**);

          static void XMLCALL
          end_element (void*, const XML_Char*);

          static void XMLCALL
          characters (void*, const XML_Char*, int);

#ifdef XSDE_POLYMORPHIC
          static void XMLCALL
          start_namespace_decl (void*, const XML_Char*, const XML_Char*);

          static void XMLCALL
          end_namespace_decl (void*, const XML_Char*);
#endif

        protected:
          void
          start_element_ (const XML_Char* ns_name, const XML_Char** atts);

          void
          end_element_ (const XML_Char* ns_name);

          void
          characters_ (const XML_Char* s, size_t n);

#ifdef XSDE_POLYMORPHIC
          void
          start_namespace_decl_ (const XML_Char* prefix, const XML_Char* ns);

          void
          end_namespace_decl_ (const XML_Char* prefix);
#endif

        protected:
          bool first_;
          XML_Parser xml_parser_;
          parser_auto_ptr auto_xml_parser_;

          context context_;

          parser_base* parser_;
          string root_name_;
          string root_ns_;

#ifdef XSDE_POLYMORPHIC
          bool polymorphic_;
          string_sequence prefixes_;
          string_sequence prefix_namespaces_;
#endif

#ifndef XSDE_EXCEPTIONS
          error error_;
#endif

          // Support for ISO-8859-1 conversion.
          //
#ifdef XSDE_ENCODING_ISO8859_1
        protected:
          const char*
          conv_data (const XML_Char* utf_s, size_t iso_n, string& var);

          const char*
          conv_data (const XML_Char* utf_s,
                     size_t utf_n,
                     size_t iso_n,
                     string& var);

          const char*
          conv_name (const XML_Char* utf_s, size_t iso_n, string& var);

          xml_error xml_error_;

          char data_buf_[256];
          char name_buf_[128];
#endif
        private:
          void
          init_root_name (const char* ns, const char* name);
        };
      }
    }
  }
}

#include <xsde/cxx/parser/expat/document.ixx>

#endif  // XSDE_CXX_PARSER_EXPAT_DOCUMENT_HXX
