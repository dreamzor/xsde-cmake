// file      : xsde/cxx/parser/validating/boolean.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_VALIDATING_BOOLEAN_HXX
#define XSDE_CXX_PARSER_VALIDATING_BOOLEAN_HXX

#include <stddef.h> // size_t

#include <xsde/cxx/parser/validating/xml-schema-pskel.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
      {
#ifdef XSDE_REUSE_STYLE_MIXIN
        struct boolean_pimpl: virtual boolean_pskel
#else
        struct boolean_pimpl: boolean_pskel
#endif
        {
          virtual void
          _pre ();

          virtual void
          _characters (const ro_string&);

          virtual void
          _post ();

          virtual bool
          post_boolean ();

        protected:
          // We only need strlen("false") + 1 characters to hold all valid
          // and trimmed string representations of boolean.
          //
          char str_[6];
          size_t size_;
          enum { leading_ws, literal, trailing_ws } state_;

          bool value_;
        };
      }
    }
  }
}

#endif  // XSDE_CXX_PARSER_VALIDATING_BOOLEAN_HXX
