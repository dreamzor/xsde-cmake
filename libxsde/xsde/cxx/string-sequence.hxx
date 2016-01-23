// file      : xsde/cxx/string-sequence.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_STRING_SEQUENCE_HXX
#define XSDE_CXX_STRING_SEQUENCE_HXX

#include <stddef.h> // size_t, ptrdiff_t

#include <xsde/cxx/config.hxx>
#include <xsde/cxx/sequence-base.hxx>

namespace xsde
{
  namespace cxx
  {
    class string_sequence: public sequence_base
    {
    public:
      typedef char*         value_type;
      typedef char**        pointer;
      typedef const char**  const_pointer;
      typedef char*         reference;
      typedef const char*   const_reference;

      typedef size_t        size_type;
      typedef ptrdiff_t     difference_type;

      typedef char** iterator;
      typedef const char* const* const_iterator;

    public:
      ~string_sequence ();

    public:
      iterator
      begin ();

      const_iterator
      begin () const;

      iterator
      end ();

      const_iterator
      end () const;

      char*
      front ();

      const char*
      front () const;

      char*
      back ();

      const char*
      back () const;

      char*
      operator[] (size_t);

      const char*
      operator[] (size_t) const;

    public:
      size_t
      max_size () const;

      void
      clear ();

      void
      pop_back ();

      iterator
      erase (iterator);

#ifndef XSDE_EXCEPTIONS
      error
#else
      void
#endif
      push_back (char*);

#ifndef XSDE_EXCEPTIONS
      error
#else
      void
#endif
      push_back_copy (const char*);

#ifndef XSDE_EXCEPTIONS
      error
      insert (iterator, char*);

      error
      insert (iterator, char*, iterator& result);
#else
      iterator
      insert (iterator, char*);
#endif

      // Detach a string from the sequence at a given position.
      // The string pointer at this position in the sequence is
      // set to 0.
      //
      char*
      detach (iterator);

      // Attach a string to the sequence at a given position.
      //
      void
      attach (iterator, char*);

#ifndef XSDE_EXCEPTIONS
      error
#else
      void
#endif
      reserve (size_t);

      void
      swap (string_sequence&);

#ifndef XSDE_EXCEPTIONS
      error
#else
      void
#endif
      copy (string_sequence&) const;

      string_sequence*
      _clone () const;

#ifndef XSDE_EXCEPTIONS
      bool
#else
      void
#endif
      _copy (string_sequence&) const;
    };

    bool
    operator== (const string_sequence&, const string_sequence&);

    bool
    operator!= (const string_sequence&, const string_sequence&);
  }
}

#include <xsde/cxx/string-sequence.ixx>

#endif  // XSDE_CXX_STRING_SEQUENCE_HXX
