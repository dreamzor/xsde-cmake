// file      : xsde/cxx/sequence-base.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <string.h> // memcpy, memmove

#include <xsde/cxx/sequence-base.hxx>

namespace xsde
{
  namespace cxx
  {
    void sequence_base::
    erase_ (void* vp, size_t es, move_forward_func mv)
    {
      char* p = static_cast<char*> (vp);
      char* d = static_cast<char*> (data_);

      if (mv)
        mv (p, size_ - 1 - (p - d) / es);
      else
        memmove (p, p + es, (size_ - 1) * es - (p - d));

      --size_;
    }

#ifdef XSDE_EXCEPTIONS
    struct guard
    {
      guard (void* p) : p_ (p) {}
      ~guard ()
      {
        if (p_)
#ifndef XSDE_CUSTOM_ALLOCATOR
          operator delete (p_);
#else
          cxx::free (p_);
#endif
      }

      void
      release () { p_ = 0; }

    private:
      void* p_;
    };

    void sequence_base::
    grow_ (size_t n, size_t es, move_func mv)
    {
      size_t c = n == 0 ? (capacity_ != 0 ? capacity_ * 2 : 8) : n;

#ifndef XSDE_CUSTOM_ALLOCATOR
      void* d = operator new (c * es);
#else
      void* d = alloc (c * es);
#endif

      if (size_)
      {
        if (mv)
        {
          guard g (d);
          mv (d, data_, size_);
          g.release ();
        }
        else
          memcpy (d, data_, size_ * es);
      }

      if (data_)
#ifndef XSDE_CUSTOM_ALLOCATOR
        operator delete (data_);
#else
        cxx::free (data_);
#endif

      data_ = d;
      capacity_ = c;
    }

    void* sequence_base::
    insert_ (void* vp, size_t es, move_func mv, move_backward_func mvb)
    {
      size_t i = static_cast<char*> (vp) - static_cast<char*> (data_);

      if (capacity_ < size_ + 1)
        grow_ (0, es, mv);

      char* d = static_cast<char*> (data_);
      char* p = d + i;

      if (mvb)
        mvb (p, size_ - i / es, size_); // increments size_
      else
      {
        memmove (p + es, p, size_ * es - i);
        ++size_;
      }

      return p;
    }
#else
    sequence_base::error sequence_base::
    grow_ (size_t n, size_t es, move_func mv)
    {
      size_t c = n == 0 ? (capacity_ != 0 ? capacity_ * 2 : 8) : n;
#ifndef XSDE_CUSTOM_ALLOCATOR
      void* d = operator new (c * es);
#else
      void* d = alloc (c * es);
#endif

      if (d == 0)
        return error_no_memory;

      if (size_)
      {
        if (mv)
          mv (d, data_, size_);
        else
          memcpy (d, data_, size_ * es);
      }

      if (data_)
#ifndef XSDE_CUSTOM_ALLOCATOR
        operator delete (data_);
#else
        cxx::free (data_);
#endif

      data_ = d;
      capacity_ = c;

      return error_none;
    }

    void* sequence_base::
    insert_ (void* vp, size_t es, move_func mv, move_backward_func mvb)
    {
      size_t i = static_cast<char*> (vp) - static_cast<char*> (data_);

      if (capacity_ < size_ + 1 && grow_ (0, es, mv) != error_none)
        return 0;

      char* d = static_cast<char*> (data_);
      char* p = d + i;

      if (mvb)
        mvb (p, size_ - i / es);
      else
        memmove (p + es, p, size_ * es - i);

      ++size_;
      return p;
    }
#endif
  }
}
