// file      : xsde/cxx/serializer/validating/date-time.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_VALIDATING_DATE_TIME_HXX
#define XSDE_CXX_SERIALIZER_VALIDATING_DATE_TIME_HXX

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
        struct date_time_simpl: virtual date_time_sskel
#else
        struct date_time_simpl: date_time_sskel
#endif
        {
          virtual void
          pre (const date_time&);

          virtual void
          _serialize_content ();

          date_time_simpl (); // Keep it last.

        protected:
          date_time value_;
        };
      }
    }
  }
}

#include <xsde/cxx/serializer/validating/date-time.ixx>

#endif // XSDE_CXX_SERIALIZER_VALIDATING_DATE_TIME_HXX
