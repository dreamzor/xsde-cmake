// file      : xsde/cxx/parser/non-validating/int.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_NON_VALIDATING_INT_HXX
#define XSDE_CXX_PARSER_NON_VALIDATING_INT_HXX

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
        // 32-bit signed integer
        //
#ifdef XSDE_REUSE_STYLE_MIXIN
        struct int_pimpl: virtual int_pskel, number
#else
        struct int_pimpl: int_pskel, number
#endif
        {
          virtual void
          _pre ();

          virtual void
          _characters (const ro_string&);

          virtual int
          post_int ();

        protected:
          // We only need strlen("02147483648") + 1 characters to hold all
          // valid and trimmed string representations of int.
          //
          char str_[12];
        };
      }
    }
  }
}

#endif  // XSDE_CXX_PARSER_NON_VALIDATING_INT_HXX
