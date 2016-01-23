// file      : xsde/cxx/serializer/validating/duration.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_VALIDATING_DURATION_HXX
#define XSDE_CXX_SERIALIZER_VALIDATING_DURATION_HXX

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
        struct duration_simpl: virtual duration_sskel
#else
        struct duration_simpl: duration_sskel
#endif
        {
          virtual void
          pre (const duration&);

          virtual void
          _serialize_content ();

          duration_simpl (); // Keep it last.

        protected:
          duration value_;
        };
      }
    }
  }
}

#include <xsde/cxx/serializer/validating/duration.ixx>

#endif // XSDE_CXX_SERIALIZER_VALIDATING_DURATION_HXX
