// file      : xsde/cxx/parser/non-validating/string-common.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_NON_VALIDATING_STRING_COMMON_HXX
#define XSDE_CXX_PARSER_NON_VALIDATING_STRING_COMMON_HXX

#include <xsde/cxx/config.hxx>

#ifdef XSDE_STL
#include <string>
#else
#include <xsde/cxx/string.hxx>
#endif

#include <xsde/cxx/parser/non-validating/xml-schema-pskel.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace non_validating
      {
        struct string_common
        {
          static void
          process_facets (
#ifdef XSDE_STL
            std::string& str,
#else
            string& str,
#endif
            const string_facets::facets&);
        };
      }
    }
  }
}

#endif  // XSDE_CXX_PARSER_NON_VALIDATING_STRING_COMMON_HXX
