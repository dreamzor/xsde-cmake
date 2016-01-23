// file      : xsde/cxx/buffer.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <string.h> // memcpy

#include <xsde/cxx/buffer.hxx>

namespace xsde
{
  namespace cxx
  {
    // c-tors
    //

#ifdef XSDE_EXCEPTIONS
    buffer::
    buffer (size_t size)
        : data_ (0), size_ (0), capacity_ (0)
    {
      capacity (size);
      size_ = size;
    }

    buffer::
    buffer (size_t size, size_t cap)
        : data_ (0), size_ (0), capacity_ (0)
    {
      if (size > cap)
        throw bounds ();

      capacity (cap);
      size_ = size;
    }

    buffer::
    buffer (const void* data, size_t size)
        : data_ (0), size_ (0), capacity_ (0)
    {
      capacity (size);
      size_ = size;

      if (size_)
        memcpy (data_, data, size_);
    }

    buffer::
    buffer (const void* data, size_t size, size_t cap)
        : data_ (0), size_ (0), capacity_ (0)
    {
      if (size > cap)
        throw bounds ();

      capacity (cap);
      size_ = size;

      if (size_)
        memcpy (data_, data, size_);
    }

    buffer::
    buffer (void* data, size_t size, size_t cap, ownership_value)
        : data_ (0), size_ (0), capacity_ (0)
    {
      if (size > cap)
        throw bounds ();

      data_ = reinterpret_cast<char*> (data);
      size_ = size;
      capacity_ = cap;
    }
#endif // XSDE_EXCEPTIONS

    //
    //

#ifdef XSDE_EXCEPTIONS
    bool buffer::
    capacity (size_t capacity, bool copy)
    {
      if (size_ > capacity)
        throw bounds ();

      if (capacity <= capacity_)
      {
        return false; // Do nothing if shrinking is requested.
      }
      else
      {
#ifndef XSDE_CUSTOM_ALLOCATOR
        char* data = static_cast<char*> (operator new (capacity));
#else
        char* data = static_cast<char*> (alloc (capacity));
#endif

        if (copy && size_ > 0)
          memcpy (data, data_, size_);

        if (data_)
#ifndef XSDE_CUSTOM_ALLOCATOR
          operator delete (data_);
#else
          cxx::free (data_);
#endif

        data_ = data;
        capacity_ = capacity;

        return true;
      }
    }

    void buffer::
    assign (void* data, size_t size)
    {
      capacity (size);
      size_ = size;

      if (size_)
        memcpy (data_, data, size_);
    }

    struct buffer_guard
    {
      buffer_guard (buffer* p) : p_ (p) {}

      ~buffer_guard ()
      {
#ifndef XSDE_CUSTOM_ALLOCATOR
        delete p_;
#else
        if (p_ != 0)
        {
          p_->~buffer ();
          cxx::free (p_);
        }
#endif
      }

      void
      release () { p_ = 0; }

    private:
      buffer* p_;
    };

    buffer* buffer::
    _clone () const
    {
#ifndef XSDE_CUSTOM_ALLOCATOR
      buffer* c = new buffer;
#else
      // Default buffer c-tor cannot throw so we don't need alloc_guard.
      //
      buffer* c = static_cast<buffer*> (cxx::alloc (sizeof (buffer)));
      new (c) buffer;
#endif
      buffer_guard g (c);
      _copy (*c);
      g.release ();
      return c;
    }

#else
    buffer::error buffer::
    capacity (size_t capacity, bool copy, bool* moved)
    {
      if (size_ > capacity)
        return error_bounds;

      if (capacity <= capacity_)
      {
        // Do nothing if shrinking is requested.
        //
        if (moved)
          *moved = false;
      }
      else
      {
#ifndef XSDE_CUSTOM_ALLOCATOR
        char* data = static_cast<char*> (operator new (capacity));
#else
        char* data = static_cast<char*> (alloc (capacity));
#endif

        if (data != 0)
        {
          if (copy && size_ > 0)
            memcpy (data, data_, size_);

          if (data_)
#ifndef XSDE_CUSTOM_ALLOCATOR
            operator delete (data_);
#else
            cxx::free (data_);
#endif

          data_ = data;
          capacity_ = capacity;

          if (moved)
            *moved = true;
        }
        else
          return error_no_memory;
      }

      return error_none;
    }

    buffer::error buffer::
    assign (void* data, size_t size)
    {
      if (error r = capacity (size))
        return r;

      size_ = size;

      if (size_)
        memcpy (data_, data, size_);

      return error_none;
    }

    buffer* buffer::
    _clone () const
    {
#ifndef XSDE_CUSTOM_ALLOCATOR
      buffer* c = new buffer;
#else
      buffer* c = static_cast<buffer*> (cxx::alloc (sizeof (buffer)));
#endif

      if (c == 0)
        return 0;

#ifdef XSDE_CUSTOM_ALLOCATOR
      new (c) buffer;
#endif

      if (!_copy (*c))
      {
#ifndef XSDE_CUSTOM_ALLOCATOR
        delete c;
#else
        c->~buffer ();
        cxx::free (c);
#endif
        return 0;
      }

      return c;
    }
#endif
  }
}
