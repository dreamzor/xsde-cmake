// file      : xsde/cxx/serializer/validating/uri.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_VALIDATING_URI_HXX
#define XSDE_CXX_SERIALIZER_VALIDATING_URI_HXX

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
        struct uri_simpl: virtual uri_sskel
#else
        struct uri_simpl: uri_sskel
#endif
        {
          virtual
          ~uri_simpl ();

          uri_simpl (bool free = false);

          virtual void
          pre (const char*);

          virtual void
          _serialize_content ();

        protected:
          bool free_;
          const char* value_;
        };
      }
    }
  }
}

#include <xsde/cxx/serializer/validating/uri.ixx>

#endif // XSDE_CXX_SERIALIZER_VALIDATING_URI_HXX
