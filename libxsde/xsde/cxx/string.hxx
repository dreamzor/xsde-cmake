// file      : xsde/cxx/string.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_STRING_HXX
#define XSDE_CXX_STRING_HXX

#include <stddef.h> // size_t

namespace xsde
{
  namespace cxx
  {
    // Simple string for situations where std::string is not available.
    //
    struct string
    {
      enum error
      {
        error_none,
        error_no_memory
      };

      typedef size_t size_type;

      ~string ();

      // The default c-tor creates an uninitialized string, not an
      // empty string. Use assign() to initialize it.
      //
      string ();

      error
      assign (const char*);

      error
      assign (const char*, size_t);

      error
      append (const char*);

      error
      append (const char*, size_t);

      char&
      operator[] (size_t);

      const char&
      operator[] (size_t) const;

      size_t
      size () const;

      char*
      data ();

      const char*
      data () const;

      bool
      empty () const;

      void
      swap (string&);

    public:
      size_t
      capacity () const;

      void
      truncate (size_t);

      char*
      detach ();

      void
      attach (char*);

      void
      attach (char*, size_t);

    private:
      string (const string&);

      string&
      operator= (const string&);

    private:
      error
      resize (size_t capacity, bool copy);

    private:
      char* data_;
      size_t size_;
      size_t capacity_;
    };

    bool
    operator== (const string&, const char*);

    bool
    operator== (const char*, const string&);

    bool
    operator!= (const string&, const char*);

    bool
    operator!= (const char*, const string&);
  }
}

#include <xsde/cxx/string.ixx>

#endif  // XSDE_CXX_STRING_HXX
