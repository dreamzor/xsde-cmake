// file      : xsde/cxx/serializer/non-validating/boolean.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_NON_VALIDATING_BOOLEAN_HXX
#define XSDE_CXX_SERIALIZER_NON_VALIDATING_BOOLEAN_HXX

#include <xsde/cxx/serializer/non-validating/xml-schema-sskel.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace non_validating
      {
#ifdef XSDE_REUSE_STYLE_MIXIN
        struct boolean_simpl: virtual boolean_sskel
#else
        struct boolean_simpl: boolean_sskel
#endif
        {
          virtual void
          pre (bool);

          virtual void
          _serialize_content ();

        protected:
          bool value_;
        };
      }
    }
  }
}

#endif // XSDE_CXX_SERIALIZER_NON_VALIDATING_BOOLEAN_HXX
