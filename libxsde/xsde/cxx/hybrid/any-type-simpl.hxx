// file      : xsde/cxx/hybrid/any-type-simpl.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_HYBRID_ANY_TYPE_SIMPL_HXX
#define XSDE_CXX_HYBRID_ANY_TYPE_SIMPL_HXX

#include <xsde/cxx/config.hxx>

#include <xsde/cxx/hybrid/any-type-sskel.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace hybrid
    {
#ifdef XSDE_REUSE_STYLE_MIXIN
      struct any_type_simpl: virtual any_type_sskel
#else
      struct any_type_simpl: any_type_sskel
#endif
      {
        virtual void
        pre (const any_type&);
      };
    }
  }
}

#endif  // XSDE_CXX_HYBRID_ANY_TYPE_SIMPL_HXX
