// file      : xsde/cxx/parser/non-validating/any-type.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_NON_VALIDATING_ANY_TYPE_HXX
#define XSDE_CXX_PARSER_NON_VALIDATING_ANY_TYPE_HXX

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
        struct any_type_pimpl: virtual any_type_pskel
#else
        struct any_type_pimpl: any_type_pskel
#endif
        {
        };
      }
    }
  }
}

#endif // XSDE_CXX_PARSER_NON_VALIDATING_ANY_TYPE_HXX
