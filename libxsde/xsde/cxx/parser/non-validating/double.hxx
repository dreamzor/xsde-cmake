// file      : xsde/cxx/parser/non-validating/double.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_NON_VALIDATING_DOUBLE_HXX
#define XSDE_CXX_PARSER_NON_VALIDATING_DOUBLE_HXX

#include <xsde/cxx/parser/non-validating/number.hxx>
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
        struct double_pimpl: virtual double_pskel, number
#else
        struct double_pimpl: double_pskel, number
#endif
        {
          virtual void
          _pre ();

          virtual void
          _characters (const ro_string&);

          virtual double
          post_double ();

        protected:
          // Assume double values (without leading and trailing whitespaces)
          // cannot be longer than 127 characters.
          //
          char str_[128];
        };
      }
    }
  }
}

#endif  // XSDE_CXX_PARSER_NON_VALIDATING_DOUBLE_HXX
