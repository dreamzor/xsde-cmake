// file      : xsde/cxx/serializer/non-validating/date.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_NON_VALIDATING_DATE_HXX
#define XSDE_CXX_SERIALIZER_NON_VALIDATING_DATE_HXX

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
        struct date_simpl: virtual date_sskel
#else
        struct date_simpl: date_sskel
#endif
        {
          virtual void
          pre (const date&);

          virtual void
          _serialize_content ();

          date_simpl (); // Keep it last.

        protected:
          date value_;
        };
      }
    }
  }
}

#include <xsde/cxx/serializer/non-validating/date.ixx>

#endif // XSDE_CXX_SERIALIZER_NON_VALIDATING_DATE_HXX
