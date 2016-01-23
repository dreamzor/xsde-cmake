// file      : xsde/cxx/parser/non-validating/parser.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace non_validating
      {
        // empty_content
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline empty_content::
        empty_content ()
        {
        }

        inline empty_content::
        empty_content (empty_content* impl, void*)
            : parser_base (impl, 0)
        {
        }
#endif

        // simple_content
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline simple_content::
        simple_content ()
        {
        }

        inline simple_content::
        simple_content (simple_content* impl, void*)
            : empty_content (impl, 0)
        {
        }
#endif

        // complex_content
        //
        inline complex_content::
        complex_content ()
            : depth_ (0), parser_stack_ (previous_)
        {
        }

#ifdef XSDE_REUSE_STYLE_TIEIN
        inline complex_content::
        complex_content (complex_content* impl, void*)
            : empty_content (impl, 0), depth_ (0), parser_stack_ (previous_)
        {
        }
#endif

        // list_base
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline list_base::
        list_base ()
        {
        }

        inline list_base::
        list_base (list_base* impl, void*)
            : simple_content (impl, 0)
        {
        }
#endif
      }
    }
  }
}
