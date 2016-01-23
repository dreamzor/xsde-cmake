// file      : xsde/cxx/stack.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifdef XSDE_CUSTOM_ALLOCATOR
#  include <xsde/cxx/allocator.hxx>
#else
#  include <new> // operator new/delete
#endif

namespace xsde
{
  namespace cxx
  {
    inline stack::
    stack (size_t el_size, void* first_el)
        : el_size_ (el_size),
          cur_ (static_cast<block*> (first_el)),
          next_ (0),
          cap_ (1),
          num_ (0)
    {
    }

    inline void stack::
    pop ()
    {
      if (cap_ == 1)
        --num_;
      else
      {
        if (num_ > 1)
          --num_;
        else
        {
          // Move to the previous block.
          //
          cap_ = cur_ == next_ ? 1 : cap_ / 2;
          cur_ = cur_->prev;
          num_ = cap_;
        }
      }
    }

#ifdef XSDE_EXCEPTIONS
    inline void stack::
#else
    inline stack::error stack::
#endif
    push ()
    {
      if (num_ < cap_)
      {
        num_++;
#ifndef XSDE_EXCEPTIONS
        return error_none;
#endif
      }
      else
      {
#ifdef XSDE_EXCEPTIONS
        push_impl ();
#else
        return push_impl ();
#endif
      }
    }

    inline void* stack::
    top ()
    {
      if (cap_ == 1)
        return cur_;
      else
      {
        char* data = reinterpret_cast<char*> (cur_) + sizeof (block);
        return data + (num_ - 1) * el_size_;
      }
    }

    inline void stack::
    clear ()
    {
      cap_ = 1;
      num_ = 0;

      // Reset cur_ to the first block.
      //
      if (next_)
        cur_ = next_->prev;
    }

    inline bool stack::
    empty () const
    {
      return num_ == 0;
    }

    inline size_t stack::
    element_size () const
    {
      return el_size_;
    }
  }
}
