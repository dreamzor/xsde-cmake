// file      : xsde/cxx/serializer/non-validating/language.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_NON_VALIDATING_LANGUAGE_HXX
#define XSDE_CXX_SERIALIZER_NON_VALIDATING_LANGUAGE_HXX

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
        struct language_simpl: virtual language_sskel
#else
        struct language_simpl: language_sskel
#endif
        {
          virtual
          ~language_simpl ();

          language_simpl (bool free = false);

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

#include <xsde/cxx/serializer/non-validating/language.ixx>

#endif // XSDE_CXX_SERIALIZER_NON_VALIDATING_LANGUAGE_HXX
