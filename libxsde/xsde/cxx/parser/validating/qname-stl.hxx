// file      : xsde/cxx/parser/validating/qname-stl.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_VALIDATING_QNAME_STL_HXX
#define XSDE_CXX_PARSER_VALIDATING_QNAME_STL_HXX

#include <string>

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
        struct qname_pimpl: virtual qname_pskel
#else
        struct qname_pimpl: qname_pskel
#endif
        {
          virtual void
          _pre ();

          virtual void
          _characters (const ro_string&);

          virtual void
          _post ();

          virtual qname
          post_qname ();

        protected:
          std::string str_;
          std::string name_;
          std::string prefix_;
        };
      }
    }
  }
}

#endif // XSDE_CXX_PARSER_VALIDATING_QNAME_STL_HXX
