// file      : xsde/cxx/hybrid/any-type-sskel.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsde
{
  namespace cxx
  {
    namespace hybrid
    {
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline any_type_sskel::
        any_type_sskel ()
            : any_type_impl_ (0)
        {
        }

        inline any_type_sskel::
        any_type_sskel (any_type_sskel* impl, void*)
            : complex_content (impl, 0), any_type_impl_ (impl)
        {
        }
#endif
    }
  }
}
