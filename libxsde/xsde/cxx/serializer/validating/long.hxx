// file      : xsde/cxx/serializer/validating/long.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_VALIDATING_LONG_HXX
#define XSDE_CXX_SERIALIZER_VALIDATING_LONG_HXX

#include <xsde/cxx/serializer/validating/xml-schema-sskel.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
        // Fall-back implementation when 64 bit long long is not available.
        //
#ifdef XSDE_REUSE_STYLE_MIXIN
        struct long_simpl: virtual long_sskel
#else
        struct long_simpl: long_sskel
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

#endif  // XSDE_CXX_SERIALIZER_VALIDATING_LONG_HXX
