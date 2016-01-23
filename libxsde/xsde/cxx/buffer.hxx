// file      : xsde/cxx/buffer.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_BUFFER_HXX
#define XSDE_CXX_BUFFER_HXX

#include <stddef.h> // size_t

#include <xsde/cxx/config.hxx>

namespace xsde
{
  namespace cxx
  {
    // Binary buffer. Used for the base64Binary and hexBinary types.
    //
    class buffer
    {
    public:
#ifdef XSDE_EXCEPTIONS
      class bounds {}; // Out of bounds exception.
#else
      enum error
      {
        error_none,
        error_bounds,
        error_no_memory
      };
#endif

    public:
      ~buffer ();
      buffer ();

#ifdef XSDE_EXCEPTIONS
      explicit
      buffer (size_t size);
      buffer (size_t size, size_t capacity);
      buffer (const void* data, size_t size);
      buffer (const void* data, size_t size, size_t capacity);

      enum ownership_value { assume_ownership };

      // This constructor assumes ownership of the memory passed.
      //
      buffer (void* data, size_t size, size_t capacity, ownership_value);
#endif

    private:
      buffer (const buffer&);

      buffer&
      operator= (const buffer&);

    public:
#ifndef XSDE_EXCEPTIONS
      error
#else
      void
#endif
      assign (void* data, size_t size);

#ifndef XSDE_EXCEPTIONS
      error
#else
      void
#endif
      attach (void* data, size_t size, size_t capacity);

      void*
      detach ();

      void
      swap (buffer&);

      buffer*
      _clone () const;

#ifndef XSDE_EXCEPTIONS
      bool
#else
      void
#endif
      _copy (buffer&) const;

    public:
      size_t
      capacity () const;

      // Returns true if the underlying buffer has moved.
      //
#ifdef XSDE_EXCEPTIONS
      bool
      capacity (size_t);
#else
      error
      capacity (size_t);

      error
      capacity (size_t, bool& moved);
#endif

    public:
      size_t
      size () const;

      // Returns true if the underlying buffer has moved.
      //
#ifdef XSDE_EXCEPTIONS
      bool
      size (size_t);
#else
      error
      size (size_t);

      error
      size (size_t, bool& moved);
#endif

    public:
      const char*
      data () const;

      char*
      data ();

      const char*
      begin () const;

      char*
      begin ();

      const char*
      end () const;

      char*
      end ();

    private:
#ifdef XSDE_EXCEPTIONS
      bool
      capacity (size_t capacity, bool copy);
#else
      error
      capacity (size_t capacity, bool copy, bool* moved);
#endif

    private:
      char* data_;
      size_t size_;
      size_t capacity_;
    };

    bool
    operator== (const buffer&, const buffer&);

    bool
    operator!= (const buffer&, const buffer&);
  }
}

#include <xsde/cxx/buffer.ixx>

#endif  // XSDE_CXX_BUFFER_HXX
