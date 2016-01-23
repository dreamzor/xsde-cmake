// file      : xsde/cxx/string-sequence.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <string.h> // strcmp

#include <xsde/cxx/strdupx.hxx>
#include <xsde/cxx/string-sequence.hxx>

namespace xsde
{
  namespace cxx
  {
    void string_sequence::
    clear ()
    {
      for (size_t i = 0;  i < size_; ++i)
#ifndef XSDE_CUSTOM_ALLOCATOR
        delete[] static_cast<char**> (data_)[i];
#else
        cxx::free (static_cast<char**> (data_)[i]);
#endif

      size_ = 0;
    }

#ifdef XSDE_EXCEPTIONS
    void string_sequence::
    push_back_copy (const char* cs)
    {
      if (capacity_ < size_ + 1)
        grow_ (0, sizeof (char*), 0);

      static_cast<char**> (data_)[size_++] = strdupx (cs);
    }

    void string_sequence::
    copy (string_sequence& c) const
    {
      if (c.size_ != 0)
        c.clear ();

      c.reserve (size_);

      for (; c.size_ < size_; ++c.size_)
      {
        static_cast<char**> (c.data_)[c.size_] =
          strdupx (static_cast<char**> (data_)[c.size_]);
      }
    }

    struct string_sequence_guard
    {
      string_sequence_guard (string_sequence* p) : p_ (p) {}

      ~string_sequence_guard ()
      {
#ifndef XSDE_CUSTOM_ALLOCATOR
        delete p_;
#else
        if (p_ != 0)
        {
          p_->~string_sequence ();
          cxx::free (p_);
        }
#endif
      }

      void
      release () { p_ = 0; }

    private:
      string_sequence* p_;
    };

    string_sequence* string_sequence::
    _clone () const
    {
#ifndef XSDE_CUSTOM_ALLOCATOR
      string_sequence* c = new string_sequence;
#else
      // Default string_sequence c-tor cannot throw so we don't need
      // alloc_guard.
      //
      string_sequence* c = static_cast<string_sequence*> (
        cxx::alloc (sizeof (string_sequence)));
      new (c) string_sequence;
#endif
      string_sequence_guard g (c);
      _copy (*c);
      g.release ();
      return c;
    }
#else
    string_sequence::error string_sequence::
    push_back_copy (const char* cs)
    {
      error r = error_none;

      if (capacity_ < size_ + 1)
        r = grow_ (0, sizeof (char*), 0);

      if (r == error_none)
      {
        char* s = strdupx (cs);

        if (s != 0)
          static_cast<char**> (data_)[size_++] = s;
        else
          r = error_no_memory;
      }

      return r;
    }

    sequence_base::error string_sequence::
    copy (string_sequence& c) const
    {
      if (c.size_ != 0)
        c.clear ();

      if (error r = c.reserve (size_))
        return r;

      for (; c.size_ < size_; ++c.size_)
      {
        char* x = strdupx (static_cast<char**> (data_)[c.size_]);

        if (x == 0)
          return error_no_memory;

        static_cast<char**> (c.data_)[c.size_] = x;
      }

      return error_none;
    }

    string_sequence* string_sequence::
    _clone () const
    {
#ifndef XSDE_CUSTOM_ALLOCATOR
      string_sequence* c = new string_sequence;
#else
      string_sequence* c = static_cast<string_sequence*> (
        cxx::alloc (sizeof (string_sequence)));
#endif

      if (c == 0)
        return 0;

#ifdef XSDE_CUSTOM_ALLOCATOR
      new (c) string_sequence;
#endif

      if (!_copy (*c))
      {
#ifndef XSDE_CUSTOM_ALLOCATOR
        delete c;
#else
        c->~string_sequence ();
        cxx::free (c);
#endif
        return 0;
      }

      return c;
    }
#endif

    bool
    operator== (const string_sequence& x, const string_sequence& y)
    {
      if (x.size () != y.size ())
        return false;

      for (size_t i = 0; i < x.size (); ++i)
        if (strcmp (x[i], y[i]) != 0)
          return false;

      return true;
    }
  }
}
