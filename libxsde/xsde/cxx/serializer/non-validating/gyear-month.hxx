// file      : xsde/cxx/serializer/non-validating/gyear-month.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_NON_VALIDATING_GYEAR_MONTH_HXX
#define XSDE_CXX_SERIALIZER_NON_VALIDATING_GYEAR_MONTH_HXX

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
        struct gyear_month_simpl: virtual gyear_month_sskel
#else
        struct gyear_month_simpl: gyear_month_sskel
#endif
        {
          virtual void
          pre (const gyear_month&);

          virtual void
          _serialize_content ();

          gyear_month_simpl (); // Keep it last.

        protected:
          gyear_month value_;
        };
      }
    }
  }
}

#include <xsde/cxx/serializer/non-validating/gyear-month.ixx>

#endif // XSDE_CXX_SERIALIZER_NON_VALIDATING_GYEAR_MONTH_HXX
