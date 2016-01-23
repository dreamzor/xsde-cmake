// file      : xsde/cxx/allocator.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_ALLOCATOR_HXX
#define XSDE_CXX_ALLOCATOR_HXX

#include <stddef.h> // size_t
#include <new>      // placement new

#include <xsde/cxx/config.hxx>

namespace xsde
{
  namespace cxx
  {
    // Allocate a memory block using custom allocator. If exceptions
    // are enabled this function throws std::bad_alloc on failure.
    // Otherwise it returns 0.
    //
    void*
    alloc (size_t);

    void
    free (void*);

#ifdef XSDE_EXCEPTIONS
    struct alloc_guard
    {
      alloc_guard (void* p) : p_ (p) {}
      ~alloc_guard () { if (p_) cxx::free (p_); }

      void*
      get () const { return p_; }

      void
      release () { p_ = 0; }

    private:
      void* p_;
    };
#endif
  }
}

#include <xsde/cxx/allocator.ixx>

#endif // XSDE_CXX_ALLOCATOR_HXX
