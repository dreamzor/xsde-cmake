// file      : xsde/cxx/hybrid/any-type-pimpl.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/config.hxx>

#ifdef XSDE_CUSTOM_ALLOCATOR
#  include <xsde/cxx/allocator.hxx>
#endif

#include <xsde/cxx/hybrid/any-type-pimpl.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace hybrid
    {
      any_type_pimpl::
      ~any_type_pimpl ()
      {
        if (!base_ && val_)
        {
#ifndef XSDE_CUSTOM_ALLOCATOR
          delete val_;
#else
          val_->~any_type ();
          cxx::free (val_);
#endif
        }
      }

      void any_type_pimpl::
      _reset ()
      {
        any_type_pskel::_reset ();

        if (!base_ && val_)
        {
#ifndef XSDE_CUSTOM_ALLOCATOR
          delete val_;
#else
          val_->~any_type ();
          cxx::free (val_);
#endif
          val_ = 0;
        }
      }

      any_type_pimpl::
      any_type_pimpl (bool base)
          : base_ (base), val_ (0)
      {
      }

      void any_type_pimpl::
      pre_impl (any_type* qn)
      {
        val_ = qn;
      }

      void any_type_pimpl::
      _pre ()
      {
        if (val_ == 0)
        {
#ifndef XSDE_CUSTOM_ALLOCATOR
          val_ = new any_type ();
#else
          val_ = static_cast<any_type*> (alloc (sizeof (any_type)));

#ifdef XSDE_EXCEPTIONS
          alloc_guard ag (val_);
          new (val_) any_type ();
          ag.release ();
#else
          if (val_)
            new (val_) any_type ();
#endif
#endif

#ifndef XSDE_EXCEPTIONS
          if (val_ == 0)
          {
            _sys_error (sys_error::no_memory);
            return;
          }
#endif
        }
      }

      any_type* any_type_pimpl::
      post_any_type ()
      {
        any_type* r = val_;
        val_ = 0;
        return r;
      }
    }
  }
}
