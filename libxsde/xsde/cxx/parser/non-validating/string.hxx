// file      : xsde/cxx/parser/non-validating/string.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_NON_VALIDATING_STRING_HXX
#define XSDE_CXX_PARSER_NON_VALIDATING_STRING_HXX

#include <xsde/cxx/string.hxx>

#include <xsde/cxx/parser/non-validating/xml-schema-pskel.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace non_validating
      {
#ifdef XSDE_REUSE_STYLE_MIXIN
        struct string_pimpl: virtual string_pskel
#else
        struct string_pimpl: string_pskel
#endif
        {
          virtual void
          _pre ();

          virtual void
          _characters (const ro_string&);

          virtual char*
          post_string ();

        protected:
          string str_;
        };
      }
    }
  }
}

#endif  // XSDE_CXX_PARSER_NON_VALIDATING_STRING_HXX
