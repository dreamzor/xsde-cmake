// file      : xsde/cxx/hybrid/any-type-pimpl.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_HYBRID_ANY_TYPE_PIMPL_HXX
#define XSDE_CXX_HYBRID_ANY_TYPE_PIMPL_HXX

#include <xsde/cxx/config.hxx>

#include <xsde/cxx/hybrid/any-type-pskel.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace hybrid
    {
#ifdef XSDE_REUSE_STYLE_MIXIN
      struct any_type_pimpl: virtual any_type_pskel
#else
      struct any_type_pimpl: any_type_pskel
#endif
      {
        ~any_type_pimpl ();
        any_type_pimpl (bool base = false);

        void
        pre_impl (any_type*);

        virtual void
        _pre ();

        virtual any_type*
        post_any_type ();

        virtual void
        _reset ();

      protected:
        bool base_;
        any_type* val_;
      };
    }
  }
}

#endif  // XSDE_CXX_HYBRID_ANY_TYPE_PIMPL_HXX
