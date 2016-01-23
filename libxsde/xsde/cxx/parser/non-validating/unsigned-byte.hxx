// file      : xsde/cxx/parser/non-validating/unsigned-byte.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_NON_VALIDATING_UNSIGNED_BYTE_HXX
#define XSDE_CXX_PARSER_NON_VALIDATING_UNSIGNED_BYTE_HXX

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
        // 8-bit unsigned integer
        //
#ifdef XSDE_REUSE_STYLE_MIXIN
        struct unsigned_byte_pimpl: virtual unsigned_byte_pskel, number
#else
        struct unsigned_byte_pimpl: unsigned_byte_pskel, number
#endif
        {
          virtual void
          _pre ();

          virtual void
          _characters (const ro_string&);

          virtual unsigned char
          post_unsigned_byte ();

        protected:
          // We only need strlen("0256") + 1 characters to hold all valid
          // and trimmed string representations of unsigned byte.
          //
          char str_[5];
        };
      }
    }
  }
}

#endif  // XSDE_CXX_PARSER_NON_VALIDATING_UNSIGNED_BYTE_HXX
