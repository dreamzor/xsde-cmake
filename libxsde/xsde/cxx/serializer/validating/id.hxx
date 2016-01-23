// file      : xsde/cxx/serializer/validating/id.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_VALIDATING_ID_HXX
#define XSDE_CXX_SERIALIZER_VALIDATING_ID_HXX

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
        struct id_simpl: virtual id_sskel
#else
        struct id_simpl: id_sskel
#endif
        {
          virtual
          ~id_simpl ();

          id_simpl (bool free = false);

          virtual void
          pre (const char*);

          virtual void
          _serialize_content ();

        protected:
          bool free_;
          const char* value_;
        };
      }
    }
  }
}

#include <xsde/cxx/serializer/validating/id.ixx>

#endif  // XSDE_CXX_SERIALIZER_VALIDATING_ID_HXX
