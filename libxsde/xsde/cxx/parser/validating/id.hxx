// file      : xsde/cxx/parser/validating/id.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_VALIDATING_ID_HXX
#define XSDE_CXX_PARSER_VALIDATING_ID_HXX

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
        struct id_pimpl: virtual id_pskel
#else
        struct id_pimpl: id_pskel
#endif
        {
          virtual void
          _pre ();

          virtual void
          _characters (const ro_string&);

          virtual void
          _post ();

          virtual char*
          post_id ();

        protected:
          string str_;
        };
      }
    }
  }
}

#endif  // XSDE_CXX_PARSER_VALIDATING_ID_HXX
