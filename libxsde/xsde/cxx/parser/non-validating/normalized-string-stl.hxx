// file      : xsde/cxx/parser/non-validating/normalized-string-stl.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_NON_VALIDATING_NORMALIZED_STRING_STL_HXX
#define XSDE_CXX_PARSER_NON_VALIDATING_NORMALIZED_STRING_STL_HXX

#include <string>

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
        struct normalized_string_pimpl: virtual normalized_string_pskel
#else
        struct normalized_string_pimpl: normalized_string_pskel
#endif
        {
          virtual void
          _pre ();

          virtual void
          _characters (const ro_string&);

          virtual std::string
          post_normalized_string ();

        protected:
          std::string str_;
        };
      }
    }
  }
}

#endif  // XSDE_CXX_PARSER_NON_VALIDATING_NORMALIZED_STRING_STL_HXX
