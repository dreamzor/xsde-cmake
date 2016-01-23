// file      : xsde/cxx/string-sequence-stl.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_STRING_SEQUENCE_STL_HXX
#define XSDE_CXX_STRING_SEQUENCE_STL_HXX

#include <string>
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
      typedef std::string         value_type;
      typedef std::string*        pointer;
      typedef const std::string*  const_pointer;
      typedef std::string&        reference;
      typedef const std::string&  const_reference;

      typedef size_t              size_type;
      typedef ptrdiff_t           difference_type;

      typedef std::string*        iterator;
      typedef const std::string*  const_iterator;

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

      std::string&
      front ();

      const std::string&
      front () const;

      std::string&
      back ();

      const std::string&
      back () const;

      std::string&
      operator[] (size_t);

      const std::string&
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
      push_back (const std::string&);

#ifndef XSDE_EXCEPTIONS
      error
      insert (iterator, const std::string&);

      error
      insert (iterator, const std::string&, iterator& result);
#else
      iterator
      insert (iterator, const std::string&);
#endif

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

    private:
      static void
      move_ (void* dst, void* src, size_t n);

      static void
      move_forward_ (void* p, size_t n);

#ifdef XSDE_EXCEPTIONS
      static void
      move_backward_ (void* p, size_t n, size_t& size);
#else
      static void
      move_backward_ (void* p, size_t n);
#endif
    };

    bool
    operator== (const string_sequence&, const string_sequence&);

    bool
    operator!= (const string_sequence&, const string_sequence&);
  }
}

#include <xsde/cxx/string-sequence-stl.ixx>

#endif  // XSDE_CXX_STRING_SEQUENCE_STL_HXX
