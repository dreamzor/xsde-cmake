// file      : xsde/cxx/parser/non-validating/unsigned-long-long.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_NON_VALIDATING_UNSIGNED_LONG_LONG_HXX
#define XSDE_CXX_PARSER_NON_VALIDATING_UNSIGNED_LONG_LONG_HXX

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
        // 64-bit unsigned integer
        //
#ifdef XSDE_REUSE_STYLE_MIXIN
        struct unsigned_long_pimpl: virtual unsigned_long_pskel, number
#else
        struct unsigned_long_pimpl: unsigned_long_pskel, number
#endif
        {
          virtual void
          _pre ();

          virtual void
          _characters (const ro_string&);

          virtual unsigned long long
          post_unsigned_long ();

        protected:
          // We only need strlen("018446744073709551615") + 1 characters to
          // hold all valid and trimmed string representations of unsigned
          // long long.
          //
          char str_[22];
        };
      }
    }
  }
}

#endif  // XSDE_CXX_PARSER_NON_VALIDATING_UNSIGNED_LONG_LONG_HXX
