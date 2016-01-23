// file      : xsde/cxx/parser/validating/long-long.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_VALIDATING_LONG_LONG_HXX
#define XSDE_CXX_PARSER_VALIDATING_LONG_LONG_HXX

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
        // 64-bit signed integer
        //
#ifdef XSDE_REUSE_STYLE_MIXIN
        struct long_pimpl: virtual long_pskel, number
#else
        struct long_pimpl: long_pskel, number
#endif
        {
          virtual void
          _pre ();

          virtual void
          _characters (const ro_string&);

          virtual void
          _post ();

          virtual long long
          post_long ();

        protected:
          // We only need strlen("09223372036854775808") + 1 characters to
          // hold all valid and trimmed string representations of long long.
          //
          char str_[21];
          long long value_;
        };
      }
    }
  }
}

#endif  // XSDE_CXX_PARSER_VALIDATING_LONG_LONG_HXX
