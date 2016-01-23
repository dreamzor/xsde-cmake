// file      : xsde/cxx/serializer/validating/decimal.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_VALIDATING_DECIMAL_HXX
#define XSDE_CXX_SERIALIZER_VALIDATING_DECIMAL_HXX

#include <float.h>

#include <xsde/cxx/serializer/validating/xml-schema-sskel.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
#ifdef XSDE_REUSE_STYLE_MIXIN
        struct decimal_simpl: virtual decimal_sskel
#else
        struct decimal_simpl: decimal_sskel
#endif
        {
          virtual void
          pre (double);

          virtual void
          _serialize_content ();

#ifdef DBL_DIG
          decimal_simpl (unsigned int precision = DBL_DIG); // Keep it last.
#else
          decimal_simpl (unsigned int precision = 15)
#endif
        protected:
          unsigned int precision_;
          double value_;
        };
      }
    }
  }
}

#include <xsde/cxx/serializer/validating/decimal.ixx>

#endif  // XSDE_CXX_SERIALIZER_VALIDATING_DECIMAL_HXX
