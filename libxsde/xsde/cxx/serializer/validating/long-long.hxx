// file      : xsde/cxx/serializer/validating/long-long.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_VALIDATING_LONG_LONG_HXX
#define XSDE_CXX_SERIALIZER_VALIDATING_LONG_LONG_HXX

#include <xsde/cxx/serializer/validating/xml-schema-sskel.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
        // 64-bit signed integer
        //
#ifdef XSDE_REUSE_STYLE_MIXIN
        struct long_simpl: virtual long_sskel
#else
        struct long_simpl: long_sskel
#endif
        {
          virtual void
          pre (long long);

          virtual void
          _serialize_content ();

        protected:
          long long value_;
        };
      }
    }
  }
}

#endif  // XSDE_CXX_SERIALIZER_VALIDATING_LONG_LONG_HXX
