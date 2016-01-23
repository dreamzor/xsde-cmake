// file      : xsde/cxx/serializer/non-validating/any-simple-type-stl.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_NON_VALIDATING_ANY_SIMPLE_TYPE_STL_HXX
#define XSDE_CXX_SERIALIZER_NON_VALIDATING_ANY_SIMPLE_TYPE_STL_HXX

#include <string>

#include <xsde/cxx/serializer/non-validating/xml-schema-sskel.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace non_validating
      {
#ifdef XSDE_REUSE_STYLE_MIXIN
        struct any_simple_type_simpl: virtual any_simple_type_sskel
#else
        struct any_simple_type_simpl: any_simple_type_sskel
#endif
        {
          virtual void
          pre (const std::string&);

          virtual void
          _serialize_content ();

        protected:
          std::string value_;
        };
      }
    }
  }
}

#endif  // XSDE_CXX_SERIALIZER_NON_VALIDATING_ANY_SIMPLE_TYPE_STL_HXX
