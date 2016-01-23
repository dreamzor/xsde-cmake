// file      : xsde/cxx/parser/validating/any-simple-type-stl.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_VALIDATING_ANY_SIMPLE_TYPE_STL_HXX
#define XSDE_CXX_PARSER_VALIDATING_ANY_SIMPLE_TYPE_STL_HXX

#include <string>

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
        struct any_simple_type_pimpl: virtual any_simple_type_pskel
#else
        struct any_simple_type_pimpl: any_simple_type_pskel
#endif
        {
          virtual void
          _pre ();

          virtual void
          _characters (const ro_string&);

          virtual std::string
          post_any_simple_type ();

        protected:
          std::string str_;
        };
      }
    }
  }
}

#endif  // XSDE_CXX_PARSER_VALIDATING_ANY_SIMPLE_TYPE_STL_HXX
