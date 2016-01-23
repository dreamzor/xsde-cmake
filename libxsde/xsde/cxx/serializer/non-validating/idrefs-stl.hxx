// file      : xsde/cxx/serializer/non-validating/idrefs-stl.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_NON_VALIDATING_IDREFS_STL_HXX
#define XSDE_CXX_SERIALIZER_NON_VALIDATING_IDREFS_STL_HXX

#include <xsde/cxx/serializer/non-validating/xml-schema-sskel.hxx>
#include <xsde/cxx/serializer/non-validating/idref-stl.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace non_validating
      {
#ifdef XSDE_REUSE_STYLE_MIXIN
        struct idrefs_simpl: virtual idrefs_sskel
#else
        struct idrefs_simpl: idrefs_sskel
#endif
        {
          virtual
          ~idrefs_simpl ();

          idrefs_simpl (bool free = false);

          virtual void
          pre (const string_sequence*);

          virtual void
          _serialize_content ();

          virtual void
          _reset ();

        protected:
          bool free_;
          const string_sequence* value_;
          idref_simpl serializer_;
        };
      }
    }
  }
}

#include <xsde/cxx/serializer/non-validating/idrefs-stl.ixx>

#endif  // XSDE_CXX_SERIALIZER_NON_VALIDATING_IDREFS_STL_HXX
