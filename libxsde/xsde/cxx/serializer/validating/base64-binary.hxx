// file      : xsde/cxx/serializer/validating/base64-binary.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_VALIDATING_BASE64_BINARY_HXX
#define XSDE_CXX_SERIALIZER_VALIDATING_BASE64_BINARY_HXX

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
        struct base64_binary_simpl: virtual base64_binary_sskel
#else
        struct base64_binary_simpl: base64_binary_sskel
#endif
        {
          virtual
          ~base64_binary_simpl ();

          base64_binary_simpl (bool free = false);

          virtual void
          pre (const buffer*);

          virtual void
          _serialize_content ();

        protected:
          bool free_;
          const buffer* value_;
        };
      }
    }
  }
}

#include <xsde/cxx/serializer/validating/base64-binary.ixx>

#endif // XSDE_CXX_SERIALIZER_VALIDATING_BASE64_BINARY_HXX
