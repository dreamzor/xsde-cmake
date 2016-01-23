// file      : xsde/cxx/serializer/validating/integer.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_VALIDATING_INTEGER_HXX
#define XSDE_CXX_SERIALIZER_VALIDATING_INTEGER_HXX

#include <xsde/cxx/serializer/validating/xml-schema-sskel.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
        // Arbitrary-length integer. Mapped to long.
        //
#ifdef XSDE_REUSE_STYLE_MIXIN
        struct integer_simpl: virtual integer_sskel
#else
        struct integer_simpl: integer_sskel
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

#endif  // XSDE_CXX_SERIALIZER_VALIDATING_INTEGER_HXX
