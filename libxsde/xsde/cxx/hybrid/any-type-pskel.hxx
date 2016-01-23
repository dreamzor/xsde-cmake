// file      : xsde/cxx/hybrid/any-type-pskel.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_HYBRID_ANY_TYPE_PSKEL_HXX
#define XSDE_CXX_HYBRID_ANY_TYPE_PSKEL_HXX

#include <xsde/cxx/config.hxx>

#ifdef XSDE_PARSER_VALIDATION
#  include <xsde/cxx/parser/validating/parser.hxx>
#else
#  include <xsde/cxx/parser/non-validating/parser.hxx>
#endif

#include <xsde/cxx/hybrid/any-type.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace hybrid
    {
#ifdef XSDE_PARSER_VALIDATION
      struct any_type_pskel: parser::validating::complex_content
#else
      struct any_type_pskel: parser::non_validating::complex_content
#endif
      {
#ifdef XSDE_POLYMORPHIC
        virtual bool
        _start_element_impl (const ro_string&,
                             const ro_string&,
                             const char*);
#else
        virtual bool
        _start_element_impl (const ro_string&, const ro_string&);
#endif

        virtual bool
        _end_element_impl (const ro_string&, const ro_string&);

#ifdef XSDE_PARSER_VALIDATION
        virtual bool
        _attribute_impl_phase_two (const ro_string&,
                                   const ro_string&,
                                   const ro_string&);
#else
        virtual bool
        _attribute_impl (const ro_string&,
                         const ro_string&,
                         const ro_string&);
#endif

        virtual bool
        _characters_impl (const ro_string&);

        virtual any_type*
        post_any_type () = 0;

#ifdef XSDE_POLYMORPHIC
        static const char*
        _static_type ();

        virtual const char*
        _dynamic_type () const;
#endif

#ifdef XSDE_REUSE_STYLE_TIEIN
        any_type_pskel ();
        any_type_pskel (any_type_pskel* impl, void*);

      protected:
        any_type_pskel* any_type_impl_;
#endif
      };
    }
  }
}

#include <xsde/cxx/hybrid/any-type-pskel.ixx>

#endif  // XSDE_CXX_HYBRID_ANY_TYPE_PSKEL_HXX
