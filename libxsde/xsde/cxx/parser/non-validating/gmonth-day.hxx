// file      : xsde/cxx/parser/non-validating/gmonth-day.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_NON_VALIDATING_GMONTH_DAY_HXX
#define XSDE_CXX_PARSER_NON_VALIDATING_GMONTH_DAY_HXX

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
        struct gmonth_day_pimpl: virtual gmonth_day_pskel
#else
        struct gmonth_day_pimpl: gmonth_day_pskel
#endif
        {
          virtual void
          _pre ();

          virtual void
          _characters (const ro_string&);

          virtual gmonth_day
          post_gmonth_day ();

        protected:
          string str_;
        };
      }
    }
  }
}

#endif // XSDE_CXX_PARSER_NON_VALIDATING_GMONTH_DAY_HXX
