// file      : xsde/cxx/parser/non-validating/float.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_NON_VALIDATING_FLOAT_HXX
#define XSDE_CXX_PARSER_NON_VALIDATING_FLOAT_HXX

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
        struct float_pimpl: virtual float_pskel, number
#else
        struct float_pimpl: float_pskel, number
#endif
        {
          virtual void
          _pre ();

          virtual void
          _characters (const ro_string&);

          virtual float
          post_float ();

        protected:
          // Assume float values (without leading and trailing whitespaces)
          // cannot be longer than 127 characters.
          //
          char str_[128];
        };
      }
    }
  }
}

#endif  // XSDE_CXX_PARSER_NON_VALIDATING_FLOAT_HXX
