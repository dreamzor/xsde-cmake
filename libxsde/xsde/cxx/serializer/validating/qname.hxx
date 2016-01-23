// file      : xsde/cxx/serializer/validating/qname.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_VALIDATING_QNAME_HXX
#define XSDE_CXX_SERIALIZER_VALIDATING_QNAME_HXX

#include <xsde/cxx/serializer/validating/xml-schema-sskel.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
#ifdef XSDE_REUSE_STYLE_MIXIN
        struct qname_simpl: virtual qname_sskel
#else
        struct qname_simpl: qname_sskel
#endif
        {
          virtual
          ~qname_simpl ();

          qname_simpl (bool free = false);

          virtual void
          pre (const qname*);

          virtual void
          _serialize_content ();

        protected:
          bool free_;
          const qname* value_;
        };
      }
    }
  }
}

#include <xsde/cxx/serializer/validating/qname.ixx>

#endif  // XSDE_CXX_SERIALIZER_VALIDATING_QNAME_HXX
