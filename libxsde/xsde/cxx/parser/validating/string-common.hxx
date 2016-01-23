// file      : xsde/cxx/parser/validating/string-common.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_VALIDATING_STRING_COMMON_HXX
#define XSDE_CXX_PARSER_VALIDATING_STRING_COMMON_HXX

#include <xsde/cxx/config.hxx>

#ifdef XSDE_STL
#include <string>
#else
#include <xsde/cxx/string.hxx>
#endif

#include <xsde/cxx/parser/validating/xml-schema-pskel.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
      {
        struct string_common
        {
          static bool
          validate_facets (
#ifdef XSDE_STL
            std::string& str,
#else
            string& str,
#endif
            const string_facets::facets&,
            context&);
        };
      }
    }
  }
}

#endif  // XSDE_CXX_PARSER_VALIDATING_STRING_COMMON_HXX
