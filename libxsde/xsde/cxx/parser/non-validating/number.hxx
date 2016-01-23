// file      : xsde/cxx/parser/non-validating/number.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_NON_VALIDATING_NUMBER_HXX
#define XSDE_CXX_PARSER_NON_VALIDATING_NUMBER_HXX

#include <stddef.h> // size_t

#include <xsde/cxx/ro-string.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace non_validating
      {
        class number
        {
        protected:
          void
          parse (const ro_string&, char* str, size_t max);

        protected:
          size_t size_;
          enum {leading_ws, sign, leading_zeros, literal, trailing_ws} state_;
          enum {none, plus, minus} sign_;
        };
      }
    }
  }
}

#endif  // XSDE_CXX_PARSER_NON_VALIDATING_NUMBER_HXX
