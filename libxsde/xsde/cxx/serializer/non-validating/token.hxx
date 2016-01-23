// file      : xsde/cxx/serializer/non-validating/token.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_NON_VALIDATING_TOKEN_HXX
#define XSDE_CXX_SERIALIZER_NON_VALIDATING_TOKEN_HXX

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
        struct token_simpl: virtual token_sskel
#else
        struct token_simpl: token_sskel
#endif
        {
          virtual
          ~token_simpl ();

          token_simpl (bool free = false);

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

#include <xsde/cxx/serializer/non-validating/token.ixx>

#endif  // XSDE_CXX_SERIALIZER_NON_VALIDATING_TOKEN_HXX
