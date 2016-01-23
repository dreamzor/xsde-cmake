// file      : xsde/cxx/parser/validating/byte.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_VALIDATING_BYTE_HXX
#define XSDE_CXX_PARSER_VALIDATING_BYTE_HXX

#include <xsde/cxx/parser/validating/number.hxx>
#include <xsde/cxx/parser/validating/xml-schema-pskel.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
      {
        // 8-bit signed integer
        //
#ifdef XSDE_REUSE_STYLE_MIXIN
        struct byte_pimpl: virtual byte_pskel, number
#else
        struct byte_pimpl: byte_pskel, number
#endif
        {
          virtual void
          _pre ();

          virtual void
          _characters (const ro_string&);

          virtual void
          _post ();

          virtual signed char
          post_byte ();

        protected:
          // We only need strlen("0128") + 1 characters to hold all valid
          // and trimmed string representations of signed byte.
          //
          char str_[5];
          signed char value_;
        };
      }
    }
  }
}

#endif  // XSDE_CXX_PARSER_VALIDATING_BYTE_HXX
