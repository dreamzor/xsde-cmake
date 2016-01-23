// file      : xsde/cxx/stack.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/stack.hxx>

namespace xsde
{
  namespace cxx
  {
    stack::
    ~stack ()
    {
      for (block* n = next_; n != 0;)
      {
        block* t = n;
        n = n->next;

#ifndef XSDE_CUSTOM_ALLOCATOR
        operator delete (t);
#else
        cxx::free (t);
#endif
      }
    }

#ifdef XSDE_EXCEPTIONS
    void stack::
#else
    stack::error stack::
#endif
    push_impl ()
    {
      bool first = (cap_ == 1);
      block*& n = first ? next_ : cur_->next;
      size_t c = first ? 8 : cap_ * 2;

      if (n == 0)
      {
#ifndef XSDE_CUSTOM_ALLOCATOR
        n = static_cast<block*> (operator new (sizeof (block) + c * el_size_));
#else
        n = static_cast<block*> (alloc (sizeof (block) + c * el_size_));
#endif

#ifndef XSDE_EXCEPTIONS
        if (n == 0)
          return error_no_memory;
#endif
        n->next = 0;
        n->prev = cur_;
      }

      cur_ = n;
      cap_ = c;
      num_ = 1;

#ifndef XSDE_EXCEPTIONS
      return error_none;
#endif
    }

    size_t stack::
    size () const
    {
      size_t r = num_;

      for (size_t c = cap_; c != 1;)
      {
        c = c == 8 ? 1 : c / 2;
        r += c;
      }

      return r;
    }
  }
}
