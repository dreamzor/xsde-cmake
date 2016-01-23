// file      : xsde/cxx/parser/validating/idrefs-stl.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_VALIDATING_IDREFS_STL_HXX
#define XSDE_CXX_PARSER_VALIDATING_IDREFS_STL_HXX

#include <xsde/cxx/parser/validating/xml-schema-pskel.hxx>
#include <xsde/cxx/parser/validating/idref-stl.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
      {
#ifdef XSDE_REUSE_STYLE_MIXIN
        struct idrefs_pimpl: virtual idrefs_pskel
#else
        struct idrefs_pimpl: idrefs_pskel
#endif
        {
          ~idrefs_pimpl ();
          idrefs_pimpl (bool base = false);

          void
          pre_impl (string_sequence*);

          virtual void
          _pre ();

          virtual void
          _xsde_parse_item (const ro_string&);

          virtual void
          _post ();

          virtual string_sequence*
          post_idrefs ();

          virtual void
          _reset ();

        protected:
          bool base_;
          idref_pimpl parser_;
          string_sequence* seq_;
        };
      }
    }
  }
}

#endif  // XSDE_CXX_PARSER_VALIDATING_IDREFS_STL_HXX
