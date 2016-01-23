// file      : xsde/cxx/parser/validating/gyear-month.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_VALIDATING_GYEAR_MONTH_HXX
#define XSDE_CXX_PARSER_VALIDATING_GYEAR_MONTH_HXX

#include <xsde/cxx/string.hxx>

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
        struct gyear_month_pimpl: virtual gyear_month_pskel
#else
        struct gyear_month_pimpl: gyear_month_pskel
#endif
        {
          virtual void
          _pre ();

          virtual void
          _characters (const ro_string&);

          virtual void
          _post ();

          virtual gyear_month
          post_gyear_month ();

        protected:
          string str_;
          int year_;
          unsigned short month_;
          bool z_;
          short zh_, zm_;
        };
      }
    }
  }
}

#endif // XSDE_CXX_PARSER_VALIDATING_GYEAR_MONTH_HXX
