// file      : xsde/cxx/parser/non-validating/qname.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_NON_VALIDATING_QNAME_HXX
#define XSDE_CXX_PARSER_NON_VALIDATING_QNAME_HXX

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
        struct qname_pimpl: virtual qname_pskel
#else
        struct qname_pimpl: qname_pskel
#endif
        {
          ~qname_pimpl ();
          qname_pimpl (bool base = false);

          void
          pre_impl (qname*);

          virtual void
          _pre ();

          virtual void
          _characters (const ro_string&);

          virtual qname*
          post_qname ();

          virtual void
          _reset ();

        protected:
          bool base_;
          string str_;
          qname* qn_;
        };
      }
    }
  }
}

#endif  // XSDE_CXX_PARSER_NON_VALIDATING_QNAME_HXX
