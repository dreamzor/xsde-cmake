// file      : xsde/cxx/serializer/validating/non-negative-integer.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_VALIDATING_NON_NEGATIVE_INTEGER_HXX
#define XSDE_CXX_SERIALIZER_VALIDATING_NON_NEGATIVE_INTEGER_HXX

#include <xsde/cxx/serializer/validating/xml-schema-sskel.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
        // Arbitrary-length non-negative integer. Mapped to unsigned long.
        //
#ifdef XSDE_REUSE_STYLE_MIXIN
        struct non_negative_integer_simpl: virtual non_negative_integer_sskel
#else
        struct non_negative_integer_simpl: non_negative_integer_sskel
#endif
        {
          virtual void
          pre (unsigned long);

          virtual void
          _serialize_content ();

        protected:
          unsigned long value_;
        };
      }
    }
  }
}

#endif  // XSDE_CXX_SERIALIZER_VALIDATING_NON_NEGATIVE_INTEGER_HXX
