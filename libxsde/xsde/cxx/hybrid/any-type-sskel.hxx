// file      : xsde/cxx/hybrid/any-type-sskel.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_HYBRID_ANY_TYPE_SSKEL_HXX
#define XSDE_CXX_HYBRID_ANY_TYPE_SSKEL_HXX

#include <xsde/cxx/config.hxx>

#ifdef XSDE_SERIALIZER_VALIDATION
#  include <xsde/cxx/serializer/validating/serializer.hxx>
#else
#  include <xsde/cxx/serializer/non-validating/serializer.hxx>
#endif

#include <xsde/cxx/hybrid/any-type.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace hybrid
    {
#ifdef XSDE_SERIALIZER_VALIDATION
      struct any_type_sskel: serializer::validating::complex_content
#else
      struct any_type_sskel: serializer::non_validating::complex_content
#endif
      {
        virtual void
        pre (const any_type&) = 0;

        // Override the following two functions to implement
        // your logic.
        //

        // virtual void
        // _serialize_attributes ();

        // virtual void
        // _serialize_content ();

#ifdef XSDE_POLYMORPHIC
        static const char*
        _static_type ();

        virtual const char*
        _dynamic_type () const;
#endif

#ifdef XSDE_REUSE_STYLE_TIEIN
        any_type_sskel ();
        any_type_sskel (any_type_sskel* impl, void*);

      protected:
        any_type_sskel* any_type_impl_;
#endif
      };
    }
  }
}

#include <xsde/cxx/hybrid/any-type-sskel.ixx>

#endif  // XSDE_CXX_HYBRID_ANY_TYPE_SSKEL_HXX
