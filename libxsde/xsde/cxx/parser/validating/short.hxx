// file      : xsde/cxx/parser/validating/short.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_VALIDATING_SHORT_HXX
#define XSDE_CXX_PARSER_VALIDATING_SHORT_HXX

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
        // 16-bit signed integer
        //
#ifdef XSDE_REUSE_STYLE_MIXIN
        struct short_pimpl: virtual short_pskel, number
#else
        struct short_pimpl: short_pskel, number
#endif
        {
          virtual void
          _pre ();

          virtual void
          _characters (const ro_string&);

          virtual void
          _post ();

          virtual short
          post_short ();

        protected:
          // We only need strlen("032768") + 1 characters to hold all valid
          // and trimmed string representations of short.
          //
          char str_[7];
          short value_;
        };
      }
    }
  }
}

#endif  // XSDE_CXX_PARSER_VALIDATING_SHORT_HXX
