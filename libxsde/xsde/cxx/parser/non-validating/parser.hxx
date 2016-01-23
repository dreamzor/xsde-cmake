// file      : xsde/cxx/parser/non-validating/parser.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_NON_VALIDATING_PARSER_HXX
#define XSDE_CXX_PARSER_NON_VALIDATING_PARSER_HXX

#include <xsde/cxx/config.hxx>

#include <stddef.h> // size_t

#include <xsde/cxx/string.hxx>
#include <xsde/cxx/ro-string.hxx>

#include <xsde/cxx/parser/elements.hxx>
#include <xsde/cxx/parser/state.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace non_validating
      {
        struct empty_content: parser_base
        {
          //
          //
#ifdef XSDE_POLYMORPHIC
          virtual bool
          _start_element_impl (const ro_string&,
                               const ro_string&,
                               const char*);
#else
          virtual bool
          _start_element_impl (const ro_string&,
                               const ro_string&);
#endif

          virtual bool
          _end_element_impl (const ro_string&,
                             const ro_string&);

          virtual bool
          _attribute_impl (const ro_string&,
                           const ro_string&,
                           const ro_string&);

          virtual bool
          _characters_impl (const ro_string&);


          //
          //
#ifdef XSDE_POLYMORPHIC
          virtual void
          _start_element (const ro_string&,
                          const ro_string&,
                          const char*);
#else
          virtual void
          _start_element (const ro_string&,
                          const ro_string&);
#endif

          virtual void
          _end_element (const ro_string&,
                        const ro_string&);

          virtual void
          _attribute (const ro_string&,
                      const ro_string&,
                      const ro_string&);

          virtual void
          _characters (const ro_string&);

          //
          //
#ifdef XSDE_REUSE_STYLE_TIEIN
          empty_content ();
          empty_content (empty_content* impl, void*);
#endif
        };


        //
        //
        struct simple_content: empty_content
        {
          //
          //
          virtual void
          _attribute (const ro_string&,
                      const ro_string&,
                      const ro_string&);

          virtual void
          _characters (const ro_string&);

          //
          //
#ifdef XSDE_REUSE_STYLE_TIEIN
          simple_content ();
          simple_content (simple_content* impl, void*);
#endif
        };


        //
        //
        struct complex_content: empty_content
        {
#ifdef XSDE_POLYMORPHIC
          virtual void
          _start_element (const ro_string&,
                          const ro_string&,
                          const char*);
#else
          virtual void
          _start_element (const ro_string&,
                          const ro_string&);
#endif
          virtual void
          _end_element (const ro_string&,
                        const ro_string&);

          virtual void
          _attribute (const ro_string&,
                      const ro_string&,
                      const ro_string&);

          virtual void
          _characters (const ro_string&);


          //
          //
          virtual void
          _pre_impl (context&);

          virtual void
          _post_impl ();

          //
          //
          virtual void
          _reset ();

          //
          //
          complex_content ();

#ifdef XSDE_REUSE_STYLE_TIEIN
          complex_content (complex_content* impl, void*);
#endif
        protected:
          size_t depth_;
          parser_stack parser_stack_;
        };

        // Base for xsd:list.
        //
        struct list_base: simple_content
        {
          virtual void
          _xsde_parse_item (const ro_string&);

          virtual void
          _pre_impl (context&);

          virtual void
          _characters (const ro_string&);

          virtual void
          _post_impl ();

          //
          //
#ifdef XSDE_REUSE_STYLE_TIEIN
          list_base ();
          list_base (list_base* impl, void*);
#endif
        protected:
          string buf_;
        };
      }
    }
  }
}

#include <xsde/cxx/parser/non-validating/parser.ixx>

#endif  // XSDE_CXX_PARSER_NON_VALIDATING_PARSER_HXX
