// file      : xsde/cxx/parser/non-validating/hex-binary.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_NON_VALIDATING_HEX_BINARY_HXX
#define XSDE_CXX_PARSER_NON_VALIDATING_HEX_BINARY_HXX

#include <xsde/cxx/string.hxx>

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
        struct hex_binary_pimpl: virtual hex_binary_pskel
#else
        struct hex_binary_pimpl: hex_binary_pskel
#endif
        {
          ~hex_binary_pimpl ();
          hex_binary_pimpl (bool base = false);

          void
          pre_impl (buffer*);

          virtual void
          _pre ();

          virtual void
          _characters (const ro_string&);

          virtual buffer*
          post_hex_binary ();

          virtual void
          _reset ();

        protected:
          bool base_;
          string str_;
          buffer* buf_;
        };
      }
    }
  }
}

#endif // XSDE_CXX_PARSER_NON_VALIDATING_HEX_BINARY_HXX
