// file      : xsde/cxx/serializer/non-validating/gyear.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_NON_VALIDATING_GYEAR_HXX
#define XSDE_CXX_SERIALIZER_NON_VALIDATING_GYEAR_HXX

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
        struct gyear_simpl: virtual gyear_sskel
#else
        struct gyear_simpl: gyear_sskel
#endif
        {
          virtual void
          pre (const gyear&);

          virtual void
          _serialize_content ();

          gyear_simpl (); // Keep it last.

        protected:
          gyear value_;
        };
      }
    }
  }
}

#include <xsde/cxx/serializer/non-validating/gyear.ixx>

#endif // XSDE_CXX_SERIALIZER_NON_VALIDATING_GYEAR_HXX
