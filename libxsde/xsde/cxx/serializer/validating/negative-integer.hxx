// file      : xsde/cxx/serializer/validating/negative-integer.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_VALIDATING_NEGATIVE_INTEGER_HXX
#define XSDE_CXX_SERIALIZER_VALIDATING_NEGATIVE_INTEGER_HXX

#include <xsde/cxx/serializer/validating/xml-schema-sskel.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
        // Arbitrary-length negative integer. Mapped to long.
        //
#ifdef XSDE_REUSE_STYLE_MIXIN
        struct negative_integer_simpl: virtual negative_integer_sskel
#else
        struct negative_integer_simpl: negative_integer_sskel
#endif
        {
          virtual void
          pre (long);

          virtual void
          _serialize_content ();

        protected:
          long value_;
        };
      }
    }
  }
}

#endif  // XSDE_CXX_SERIALIZER_VALIDATING_NEGATIVE_INTEGER_HXX
