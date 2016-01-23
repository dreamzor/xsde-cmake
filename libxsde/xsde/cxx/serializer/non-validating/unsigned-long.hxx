// file      : xsde/cxx/serializer/non-validating/unsigned-long.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_NON_VALIDATING_UNSIGNED_LONG_HXX
#define XSDE_CXX_SERIALIZER_NON_VALIDATING_UNSIGNED_LONG_HXX

#include <xsde/cxx/serializer/non-validating/xml-schema-sskel.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace non_validating
      {
        // Fall-back implementation when 64 bit long long is not available.
        //
#ifdef XSDE_REUSE_STYLE_MIXIN
        struct unsigned_long_simpl: virtual unsigned_long_sskel
#else
        struct unsigned_long_simpl: unsigned_long_sskel
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

#endif  // XSDE_CXX_SERIALIZER_NON_VALIDATING_UNSIGNED_LONG_HXX
