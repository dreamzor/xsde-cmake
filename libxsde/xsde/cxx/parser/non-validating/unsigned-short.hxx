// file      : xsde/cxx/parser/non-validating/unsigned-short.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_NON_VALIDATING_UNSIGNED_SHORT_HXX
#define XSDE_CXX_PARSER_NON_VALIDATING_UNSIGNED_SHORT_HXX

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
        // 16-bit unsigned integer
        //
#ifdef XSDE_REUSE_STYLE_MIXIN
        struct unsigned_short_pimpl: virtual unsigned_short_pskel, number
#else
        struct unsigned_short_pimpl: unsigned_short_pskel, number
#endif
        {
          virtual void
          _pre ();

          virtual void
          _characters (const ro_string&);

          virtual unsigned short
          post_unsigned_short ();

        protected:
          // We only need strlen("065535") + 1 characters to hold all valid
          // and trimmed string representations of unsigned short.
          //
          char str_[7];
        };
      }
    }
  }
}

#endif  // XSDE_CXX_PARSER_NON_VALIDATING_UNSIGNED_SHORT_HXX
