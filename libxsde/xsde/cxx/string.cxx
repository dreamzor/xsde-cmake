// file      : xsde/cxx/string.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <string.h>

#include <xsde/cxx/string.hxx>

namespace xsde
{
  namespace cxx
  {
    string::error string::
    assign (const char* s, size_t size)
    {
      if (size + 1 > capacity_)
        if (error e = resize (size + 1, false))
          return e;

      if (size != 0)
        memcpy (data_, s, size);

      data_[size] = '\0';

      size_ = size;

      return error_none;
    }

    string::error string::
    append (const char* s, size_t size)
    {
      if (size_ + size + 1 > capacity_)
        if (error e = resize (size_ + size + 1, true))
          return e;

      if (size != 0)
        memcpy (data_ + size_, s, size);

      size_ += size;
      data_[size_] = '\0';

      return error_none;
    }

    string::error string::
    resize (size_t new_cap, bool copy)
    {
      // Start with at least 64 chars (32 * 2).
      //
      size_t cap = capacity_ ? capacity_ : 32;

      if (new_cap <= 2 * cap)
        new_cap = 2 * cap;
      else
        new_cap += (new_cap & 1) ? 1 : 0; // Make even.

#ifndef XSDE_CUSTOM_ALLOCATOR
      char* p = new char[new_cap];
#else
      char* p = static_cast<char*> (alloc (new_cap));
#endif

      if (p == 0)
        return error_no_memory;

      if (copy && size_ != 0)
        memcpy (p, data_, size_ + 1);

#ifndef XSDE_CUSTOM_ALLOCATOR
      delete[] data_;
#else
      cxx::free (data_);
#endif

      data_ = p;
      capacity_ = new_cap;

      return error_none;
    }
  }
}
