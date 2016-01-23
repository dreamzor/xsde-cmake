// file      : xsde/cxx/serializer/non-validating/gmonth.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_NON_VALIDATING_GMONTH_HXX
#define XSDE_CXX_SERIALIZER_NON_VALIDATING_GMONTH_HXX

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
        struct gmonth_simpl: virtual gmonth_sskel
#else
        struct gmonth_simpl: gmonth_sskel
#endif
        {
          virtual void
          pre (const gmonth&);

          virtual void
          _serialize_content ();

          gmonth_simpl (); // Keep it last.

        protected:
          gmonth value_;
        };
      }
    }
  }
}

#include <xsde/cxx/serializer/non-validating/gmonth.ixx>

#endif // XSDE_CXX_SERIALIZER_NON_VALIDATING_GMONTH_HXX
