// file      : xsde/cxx/serializer/non-validating/serializer.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsde
{
  namespace cxx
  {
    namespace serializer
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
            : serializer_base (impl, 0)
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
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline complex_content::
        complex_content ()
        {
        }

        inline complex_content::
        complex_content (complex_content* impl, void*)
            : empty_content (impl, 0)
        {
        }
#endif
      }
    }
  }
}
