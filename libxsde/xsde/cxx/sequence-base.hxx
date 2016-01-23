// file      : xsde/cxx/sequence-base.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SEQUENCE_BASE_HXX
#define XSDE_CXX_SEQUENCE_BASE_HXX

#include <xsde/cxx/config.hxx>

#include <stddef.h> // size_t

namespace xsde
{
  namespace cxx
  {
    //
    //
    class sequence_base
    {
    public:
#ifndef XSDE_EXCEPTIONS
      enum error
      {
        error_none,
        error_no_memory
      };
#endif

    private:
      sequence_base (sequence_base&);
      sequence_base& operator= (sequence_base&);

    public:
      ~sequence_base ();
      sequence_base ();

      bool
      empty () const;

      size_t
      size () const;

      size_t
      capacity () const;

    protected:
      typedef void (*move_func) (void*, void*, size_t);
      typedef void (*move_forward_func) (void*, size_t);
#ifdef XSDE_EXCEPTIONS
      typedef void (*move_backward_func) (void*, size_t, size_t&);
#else
      typedef void (*move_backward_func) (void*, size_t);
#endif


#ifndef XSDE_EXCEPTIONS
      error
#else
      void
#endif
      grow_ (size_t n, size_t element_size, move_func);

      void
      erase_ (void*, size_t element_size, move_forward_func);

      void*
      insert_ (void*, size_t element_size, move_func, move_backward_func);

      void
      swap_ (sequence_base&);

    protected:
      void* data_;
      size_t size_;
      size_t capacity_;
    };
  }
}

#include <xsde/cxx/sequence-base.ixx>

#endif  // XSDE_CXX_SEQUENCE_BASE_HXX
