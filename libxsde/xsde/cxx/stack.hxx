// file      : xsde/cxx/stack.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_STACK_HXX
#define XSDE_CXX_STACK_HXX

#include <stddef.h> // size_t

#include <xsde/cxx/config.hxx>

namespace xsde
{
  namespace cxx
  {
    // POD stack with pre-allocated first element. You may
    // need to pad your elements to get the proper alignment.
    //
    struct stack
    {
#ifndef XSDE_EXCEPTIONS
      enum error
      {
        error_none,
        error_no_memory
      };
#endif

      ~stack ();
      stack (size_t element_size, void* first_element);

    private:
      stack (stack&);
      stack& operator= (stack&);

    public:
      void
      pop ();

#ifdef XSDE_EXCEPTIONS
      void
#else
      error
#endif
      push ();

      void*
      top ();

      void
      clear ();

      bool
      empty () const;

      // Note: expensive, non-inline function.
      //
      size_t
      size () const;

      size_t
      element_size () const;

    private:
#ifdef XSDE_EXCEPTIONS
      void
#else
      error
#endif
      push_impl ();

    private:
      // The stack is implemented as a doubly-linked list of memory
      // regions. The first region is special since it is the single,
      // pre-allocated element. It also doesn't have the embedded
      // 'next' and 'prev' fields. Instead, the next_ member is used
      // for this purpose. The memory blocks have fixed sizes: 1, 8,
      // 16, ... elements.
      //
      struct block
      {
        block* prev;
        block* next;
        //char data[0]; Sufficiently padded (2 * sizeof(void*)).
      };

      size_t el_size_; // Element size in bytes.
      block* cur_;     // Current block (the first element if cap_ == 1).
      block* next_;    // Next block of the special first block.
      size_t cap_;     // Capacity of the current block in elements.
      size_t num_;     // Number of elements in the current block.
    };
  }
}

#include <xsde/cxx/stack.ixx>

#endif // XSDE_CXX_STACK_HXX
