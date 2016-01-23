// file      : xsde/cxx/guard.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_GUARD_HXX
#define XSDE_CXX_GUARD_HXX

#include <xsde/cxx/config.hxx>

#ifdef XSDE_CUSTOM_ALLOCATOR
#  include <xsde/cxx/allocator.hxx>
#endif

namespace xsde
{
  namespace cxx
  {
#ifdef XSDE_EXCEPTIONS
    template <typename T>
    struct guard
    {
      guard (T* p) : p_ (p) {}

      ~guard ()
      {
#ifndef XSDE_CUSTOM_ALLOCATOR
        delete p_;
#else
        if (p_ != 0)
        {
          p_->~T ();
          cxx::free (p_);
        }
#endif
      }

      void
      release () { p_ = 0; }

    private:
      T* p_;
    };
#endif // XSDE_EXCEPTIONS
  }
}

#endif // XSDE_CXX_GUARD_HXX
