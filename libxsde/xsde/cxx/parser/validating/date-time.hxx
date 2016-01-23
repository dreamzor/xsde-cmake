// file      : xsde/cxx/parser/validating/date-time.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_VALIDATING_DATE_TIME_HXX
#define XSDE_CXX_PARSER_VALIDATING_DATE_TIME_HXX

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
        struct date_time_pimpl: virtual date_time_pskel
#else
        struct date_time_pimpl: date_time_pskel
#endif
        {
          virtual void
          _pre ();

          virtual void
          _characters (const ro_string&);

          virtual void
          _post ();

          virtual date_time
          post_date_time ();

        protected:
          string str_;
          int year_;
          unsigned short month_, day_;
          unsigned short hours_, minutes_;
          double seconds_;
          bool z_;
          short zh_, zm_;
        };
      }
    }
  }
}

#endif // XSDE_CXX_PARSER_VALIDATING_DATE_TIME_HXX
