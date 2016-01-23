// file      : xsde/cxx/parser/validating/normalized-string.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_VALIDATING_NORMALIZED_STRING_HXX
#define XSDE_CXX_PARSER_VALIDATING_NORMALIZED_STRING_HXX

#include <xsde/cxx/string.hxx>

#include <xsde/cxx/parser/validating/xml-schema-pskel.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
      {
#ifdef XSDE_REUSE_STYLE_MIXIN
        struct normalized_string_pimpl: virtual normalized_string_pskel
#else
        struct normalized_string_pimpl: normalized_string_pskel
#endif
        {
          virtual void
          _pre ();

          virtual void
          _characters (const ro_string&);

          virtual void
          _post ();

          virtual char*
          post_normalized_string ();

        protected:
          string str_;
        };
      }
    }
  }
}

#endif  // XSDE_CXX_PARSER_VALIDATING_NORMALIZED_STRING_HXX
