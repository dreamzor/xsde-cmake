// file      : xsde/cxx/ro-string.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_RO_STRING_HXX
#define XSDE_CXX_RO_STRING_HXX

#include <xsde/cxx/config.hxx>

#include <stddef.h> // size_t

#ifdef XSDE_STL
#  include <string>
#endif

#ifdef XSDE_IOSTREAM
#  include <iosfwd>
#endif

#include <xsde/cxx/string.hxx>

namespace xsde
{
  namespace cxx
  {
    // Read-only string.
    //
    struct ro_string
    {
      typedef size_t size_type;
      static const size_t npos;

    public:
      ro_string ();
      ro_string (const char*);
      ro_string (const char*, size_t);
      ro_string (const string&);

#ifdef XSDE_STL
      ro_string (const std::string&);
      operator std::string () const;
#endif

    private:
      ro_string (const ro_string&);

      ro_string&
      operator= (const ro_string&);

    public:
      // The returned string is not necessarily terminated  with '\0'.
      // If size() returns 0, the returned pointer may be 0.
      //
      const char*
      data () const;

      size_t
      size () const;

      size_t
      length () const;

    public:
      bool
      empty () const;

      char
      operator[] (size_t) const;

    public:
      void
      assign (const char*);

      void
      assign (const char*, size_t);

      void
      assign (const ro_string&);

      void
      assign (const string&);

#ifdef XSDE_STL
      void
      assign (const std::string&);
#endif

    public:
      int
      compare (const ro_string&) const;

      int
      compare (const char*) const;

      int
      compare (const char*, size_t) const;

      int
      compare (const string&) const;

#ifdef XSDE_STL
      int
      compare (const std::string&) const;
#endif

    public:
      size_t
      find (char, size_t pos = 0) const;

    private:
      const char* data_;
      size_t size_;
    };


    // operator ==
    //

    bool
    operator== (const ro_string&, const ro_string&);

    bool
    operator== (const ro_string&, const char*);

    bool
    operator== (const char*, const ro_string&);

    bool
    operator== (const ro_string&, const string&);

    bool
    operator== (const string&, const ro_string&);

#ifdef XSDE_STL
    bool
    operator== (const ro_string&, const std::string&);

    bool
    operator== (const std::string&, const ro_string&);
#endif


    // operator !=
    //

    bool
    operator!= (const ro_string&, const ro_string&);

    bool
    operator!= (const ro_string&, const char*);

    bool
    operator!= (const char*, const ro_string&);

    bool
    operator!= (const ro_string&, const string&);

    bool
    operator!= (const string&, const ro_string&);

#ifdef XSDE_STL
    bool
    operator!= (const ro_string&, const std::string&);

    bool
    operator!= (const std::string&, const ro_string&);
#endif


    // operator <
    //

    bool
    operator< (const ro_string&, const ro_string&);

    bool
    operator< (const ro_string&, const char*);

    bool
    operator< (const char*, const ro_string&);

#ifdef XSDE_STL
    bool
    operator< (const ro_string&, const std::string&);

    bool
    operator< (const std::string&, const ro_string&);
#endif


    // operator >
    //

    bool
    operator> (const ro_string&, const ro_string&);

    bool
    operator> (const ro_string&, const char*);

    bool
    operator> (const char*, const ro_string&);

#ifdef XSDE_STL
    bool
    operator> (const ro_string&, const std::string&);

    bool
    operator> (const std::string&, const ro_string&);
#endif


    // operator <=
    //

    bool
    operator<= (const ro_string&, const ro_string&);

    bool
    operator<= (const ro_string&, const char*);

    bool
    operator<= (const char*, const ro_string&);

#ifdef XSDE_STL
    bool
    operator<= (const ro_string&, const std::string&);

    bool
    operator<= (const std::string&, const ro_string&);
#endif


    // operator>=
    //

    bool
    operator>= (const ro_string&, const ro_string&);

    bool
    operator>= (const ro_string&, const char*);

    bool
    operator>= (const char*, const ro_string&);

#ifdef XSDE_STL
    bool
    operator>= (const ro_string&, const std::string&);

    bool
    operator>= (const std::string&, const ro_string&);
#endif

    // operator +=
    //
#ifdef XSDE_STL
    std::string&
    operator+= (std::string&, const ro_string&);
#endif

    // operator <<
    //
#ifdef XSDE_IOSTREAM
    std::ostream&
    operator<< (std::ostream&, const ro_string&);
#endif

    // Trim leading and trailing XML whitespaces. Return the new
    // string size.
    //
    size_t
    trim_left (ro_string&);

    size_t
    trim_right (ro_string&);

    size_t
    trim (ro_string&);
  }
}

#include <xsde/cxx/ro-string.ixx>

#endif  // XSDE_CXX_RO_STRING_HXX
