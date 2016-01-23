// file      : xsde/cxx/string.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <string.h>

#include <xsde/cxx/config.hxx>

#ifdef XSDE_CUSTOM_ALLOCATOR
#  include <xsde/cxx/allocator.hxx>
#endif

namespace xsde
{
  namespace cxx
  {
    inline string::
    ~string ()
    {
#ifndef XSDE_CUSTOM_ALLOCATOR
      delete[] data_;
#else
      cxx::free (data_);
#endif
    }

    inline string::
    string ()
        : data_ (0), size_ (0), capacity_ (0)
    {
    }

    inline char* string::
    detach ()
    {
      char* r = data_;
      data_ = 0;
      size_ = 0;
      capacity_ = 0;
      return r;
    }

    inline void string::
    attach (char* s)
    {
      attach (s, s != 0 ? strlen (s) : 0);
    }

    inline void string::
    attach (char* s, size_t n)
    {
#ifndef XSDE_CUSTOM_ALLOCATOR
      delete[] data_;
#else
      cxx::free (data_);
#endif

      data_ = s;
      size_ = n;
      capacity_ = n + 1;
    }

    inline string::error string::
    assign (const char* s)
    {
      return assign (s, strlen (s));
    }

    inline string::error string::
    append (const char* s)
    {
      return append (s, strlen (s));
    }

    inline char& string::
    operator[] (size_t i)
    {
      return data_[i];
    }

    inline const char& string::
    operator[] (size_t i) const
    {
      return data_[i];
    }

    inline size_t string::
    size () const
    {
      return size_;
    }

    inline char* string::
    data ()
    {
      return data_;
    }

    inline const char* string::
    data () const
    {
      return data_;
    }

    inline bool string::
    empty () const
    {
      return size_ == 0;
    }

    inline void string::
    swap (string& str)
    {
      char* d = data_;
      data_ = str.data_;
      str.data_ = d;

      size_t s = size_;
      size_ = str.size_;
      str.size_ = s;

      size_t c = capacity_;
      capacity_ = str.capacity_;
      str.capacity_ = c;
    }

    inline size_t string::
    capacity () const
    {
      return capacity_;
    }

    inline void string::
    truncate (size_t s)
    {
      if (s < size_)
      {
        size_ = s;
        data_[s] = '\0';
      }
    }

    inline bool
    operator== (const string& a, const char* b)
    {
      return strcmp (a.data (), b) == 0;
    }

    inline bool
    operator== (const char* a, const string& b)
    {
      return strcmp (b.data (), a) == 0;
    }

    inline bool
    operator!= (const string& a, const char* b)
    {
      return strcmp (a.data (), b) != 0;
    }

    inline bool
    operator!= (const char* a, const string& b)
    {
      return strcmp (b.data (), a) != 0;
    }
  }
}
