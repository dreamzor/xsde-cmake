// file      : xsde/cxx/serializer/non-validating/double.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_NON_VALIDATING_DOUBLE_HXX
#define XSDE_CXX_SERIALIZER_NON_VALIDATING_DOUBLE_HXX

#include <float.h>

#include <xsde/cxx/serializer/non-validating/xml-schema-sskel.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace non_validating
      {
#ifdef XSDE_REUSE_STYLE_MIXIN
        struct double_simpl: virtual double_sskel
#else
        struct double_simpl: double_sskel
#endif
        {
          virtual void
          pre (double);

          virtual void
          _serialize_content ();

          enum notation
          {
            notation_auto,
            notation_fixed,
            notation_scientific
          };

#ifdef DBL_DIG
          double_simpl (notation = notation_auto,
                        unsigned int precision = DBL_DIG); // Keep it last.
#else
          double_simpl (notation = notation_auto,
                        unsigned int precision = 15)
#endif

        protected:
          notation notation_;
          unsigned int precision_;
          double value_;
        };
      }
    }
  }
}

#include <xsde/cxx/serializer/non-validating/double.ixx>

#endif  // XSDE_CXX_SERIALIZER_NON_VALIDATING_DOUBLE_HXX
