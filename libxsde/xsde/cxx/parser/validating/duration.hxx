// file      : xsde/cxx/parser/validating/duration.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_VALIDATING_DURATION_HXX
#define XSDE_CXX_PARSER_VALIDATING_DURATION_HXX

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
        struct duration_pimpl: virtual duration_pskel
#else
        struct duration_pimpl: duration_pskel
#endif
        {
          virtual void
          _pre ();

          virtual void
          _characters (const ro_string&);

          virtual void
          _post ();

          virtual duration
          post_duration ();

        protected:
          string str_;
          bool negative_;
          unsigned int years_, months_, days_;
          unsigned int hours_, minutes_;
          double seconds_;
        };
      }
    }
  }
}

#endif // XSDE_CXX_PARSER_VALIDATING_DURATION_HXX
