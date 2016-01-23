// file      : xsde/cxx/serializer/non-validating/unsigned-int.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_NON_VALIDATING_UNSIGNED_INT_HXX
#define XSDE_CXX_SERIALIZER_NON_VALIDATING_UNSIGNED_INT_HXX

#include <xsde/cxx/serializer/non-validating/xml-schema-sskel.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace non_validating
      {
        // 32-bit unsigned integer
        //
#ifdef XSDE_REUSE_STYLE_MIXIN
        struct unsigned_int_simpl: virtual unsigned_int_sskel
#else
        struct unsigned_int_simpl: unsigned_int_sskel
#endif
        {
          virtual void
          pre (unsigned int);

          virtual void
          _serialize_content ();

        protected:
          unsigned int value_;
        };
      }
    }
  }
}

#endif  // XSDE_CXX_SERIALIZER_NON_VALIDATING_UNSIGNED_INT_HXX
