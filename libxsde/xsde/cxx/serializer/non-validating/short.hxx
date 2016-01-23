// file      : xsde/cxx/serializer/non-validating/short.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_NON_VALIDATING_SHORT_HXX
#define XSDE_CXX_SERIALIZER_NON_VALIDATING_SHORT_HXX

#include <xsde/cxx/serializer/non-validating/xml-schema-sskel.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace non_validating
      {
        // 16-bit signed integer
        //
#ifdef XSDE_REUSE_STYLE_MIXIN
        struct short_simpl: virtual short_sskel
#else
        struct short_simpl: short_sskel
#endif
        {
          virtual void
          pre (short);

          virtual void
          _serialize_content ();

        protected:
          short value_;
        };
      }
    }
  }
}

#endif  // XSDE_CXX_SERIALIZER_NON_VALIDATING_SHORT_HXX
