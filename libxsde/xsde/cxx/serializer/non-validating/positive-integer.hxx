// file      : xsde/cxx/serializer/non-validating/positive-integer.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_NON_VALIDATING_POSITIVE_INTEGER_HXX
#define XSDE_CXX_SERIALIZER_NON_VALIDATING_POSITIVE_INTEGER_HXX

#include <xsde/cxx/serializer/non-validating/xml-schema-sskel.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace non_validating
      {
        // Arbitrary-length positive integer. Mapped to unsigned long.
        //
#ifdef XSDE_REUSE_STYLE_MIXIN
        struct positive_integer_simpl: virtual positive_integer_sskel
#else
        struct positive_integer_simpl: positive_integer_sskel
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

#endif  // XSDE_CXX_SERIALIZER_NON_VALIDATING_POSITIVE_INTEGER_HXX
