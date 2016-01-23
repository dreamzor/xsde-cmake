// file      : xsde/cxx/buffer.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <string.h> // memcmp

#ifdef XSDE_CUSTOM_ALLOCATOR
#  include <xsde/cxx/allocator.hxx>
#endif

namespace xsde
{
  namespace cxx
  {
    // c-tors & d-tor
    //
    inline buffer::
    ~buffer ()
    {
      if (data_)
#ifndef XSDE_CUSTOM_ALLOCATOR
        operator delete (data_);
#else
        cxx::free (data_);
#endif
    }

    inline buffer::
    buffer ()
        : data_ (0), size_ (0), capacity_ (0)
    {
    }

#ifndef XSDE_EXCEPTIONS
    inline buffer::error buffer::
#else
    inline void buffer::
#endif
    attach (void* data, size_t size, size_t cap)
    {
      if (size > cap)
      {
#ifdef XSDE_EXCEPTIONS
        throw bounds ();
#else
        return error_bounds;
#endif
      }

      if (data_)
#ifndef XSDE_CUSTOM_ALLOCATOR
        operator delete (data_);
#else
        cxx::free (data_);
#endif

      data_ = reinterpret_cast<char*> (data);
      size_ = size;
      capacity_ = cap;

#ifndef XSDE_EXCEPTIONS
      return error_none;
#endif
    }

    inline void* buffer::
    detach ()
    {
      void* r = data_;

      data_ = 0;
      size_ = 0;
      capacity_ = 0;

      return r;
    }

    inline void buffer::
    swap (buffer& other)
    {
      char* d = data_;
      size_t s = size_;
      size_t c = capacity_;

      data_ = other.data_;
      size_ = other.size_;
      capacity_ = other.capacity_;

      other.data_ = d;
      other.size_ = s;
      other.capacity_ = c;
    }

    //
    //
    inline size_t buffer::
    capacity () const
    {
      return capacity_;
    }

#ifdef XSDE_EXCEPTIONS
    inline bool buffer::
    capacity (size_t cap)
    {
      return capacity (cap, true);
    }
#else
    inline buffer::error buffer::
    capacity (size_t cap)
    {
      return capacity (cap, true, 0);
    }

    inline buffer::error buffer::
    capacity (size_t cap, bool& moved)
    {
      return capacity (cap, true, &moved);
    }
#endif

    inline size_t buffer::
    size () const
    {
      return size_;
    }

#ifdef XSDE_EXCEPTIONS
    inline bool buffer::
    size (size_t size)
    {
      bool r = false;

      if (size > capacity_)
        r = capacity (size);

      size_ = size;

      return r;
    }
#else
    inline buffer::error buffer::
    size (size_t size)
    {
      error r = error_none;

      if (size > capacity_)
        r = capacity (size);

      if (r == error_none)
        size_ = size;

      return r;
    }

    inline buffer::error buffer::
    size (size_t size, bool& moved)
    {
      error r = error_none;
      moved = false;

      if (size > capacity_)
        r = capacity (size, moved);

      if (r == error_none)
        size_ = size;

      return r;
    }
#endif

    //
    //
    inline const char* buffer::
    data () const
    {
      return data_;
    }

    inline char* buffer::
    data ()
    {
      return data_;
    }

    inline const char* buffer::
    begin () const
    {
      return data_;
    }

    inline char* buffer::
    begin ()
    {
      return data_;
    }

    inline const char* buffer::
    end () const
    {
      return data_ + size_;
    }

    inline char* buffer::
    end ()
    {
      return data_ + size_;
    }

    inline bool
    operator== (const buffer& x, const buffer& y)
    {
      return x.size () == y.size () &&
        memcmp (x.data (), y.data (), x.size ()) == 0;
    }

    inline bool
    operator!= (const buffer& x, const buffer& y)
    {
      return !(x == y);
    }

    //
    //
#ifndef XSDE_EXCEPTIONS
    inline bool buffer::
    _copy (buffer& c) const
    {
      return c.assign (data_, size_) == error_none;
    }
#else
    inline void buffer::
    _copy (buffer& c) const
    {
      c.assign (data_, size_);
    }
#endif
  }
}
