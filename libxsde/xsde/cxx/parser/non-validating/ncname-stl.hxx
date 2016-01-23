// file      : xsde/cxx/parser/non-validating/ncname-stl.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_NON_VALIDATING_NCNAME_STL_HXX
#define XSDE_CXX_PARSER_NON_VALIDATING_NCNAME_STL_HXX

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
        struct ncname_pimpl: virtual ncname_pskel
#else
        struct ncname_pimpl: ncname_pskel
#endif
        {
          virtual void
          _pre ();

          virtual void
          _characters (const ro_string&);

          virtual std::string
          post_ncname ();

        protected:
          std::string str_;
        };
      }
    }
  }
}

#endif  // XSDE_CXX_PARSER_NON_VALIDATING_NCNAME_STL_HXX
