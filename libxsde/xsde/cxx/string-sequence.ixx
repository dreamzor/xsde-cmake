// file      : xsde/cxx/string-sequence.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifdef XSDE_CUSTOM_ALLOCATOR
#  include <xsde/cxx/allocator.hxx>
#endif

namespace xsde
{
  namespace cxx
  {
    inline string_sequence::
    ~string_sequence ()
    {
      clear ();
    }

    inline size_t string_sequence::
    max_size () const
    {
      return size_t (-1) / sizeof (char*);
    }

    inline void string_sequence::
    swap (string_sequence& x)
    {
      swap_ (x);
    }

    inline string_sequence::iterator string_sequence::
    begin ()
    {
      return static_cast<char**> (data_);
    }

    inline string_sequence::const_iterator string_sequence::
    begin () const
    {
      // g++ 2.95 does not like static_cast here.
      //
      return (const char* const*) (data_);
    }

    inline string_sequence::iterator string_sequence::
    end ()
    {
      return static_cast<char**> (data_) + size_;
    }

    inline string_sequence::const_iterator string_sequence::
    end () const
    {
      return ((const char* const*) (data_)) + size_;
    }

    inline char* string_sequence::
    front ()
    {
      return *static_cast<char**> (data_);
    }

    inline const char* string_sequence::
    front () const
    {
      return *((const char* const*) (data_));
    }

    inline char* string_sequence::
    back ()
    {
      return static_cast<char**> (data_)[size_ - 1];
    }

    inline const char* string_sequence::
    back () const
    {
      return ((const char* const*) (data_))[size_ - 1];
    }

    inline char* string_sequence::
    operator[] (size_t i)
    {
      return static_cast<char**> (data_)[i];
    }

    inline const char* string_sequence::
    operator[] (size_t i) const
    {
      return ((const char* const*) (data_))[i];
    }

    inline void string_sequence::
    pop_back ()
    {
#ifndef XSDE_CUSTOM_ALLOCATOR
      delete[] static_cast<char**> (data_)[size_ - 1];
#else
      cxx::free (static_cast<char**> (data_)[size_ - 1]);
#endif
      --size_;
    }

    inline string_sequence::iterator string_sequence::
    erase (iterator i)
    {
#ifndef XSDE_CUSTOM_ALLOCATOR
      delete[] *i;
#else
      cxx::free (*i);
#endif

      if (i != static_cast<char**> (data_) + (size_ - 1))
        erase_ (i, sizeof (char*), 0);
      else
        --size_;

      return i;
    }

#ifdef XSDE_EXCEPTIONS
    namespace string_sequence_bits
    {
      struct guard
      {
        ~guard ()
        {
#ifndef XSDE_CUSTOM_ALLOCATOR
          delete[] p_;
#else
          cxx::free (p_);
#endif
        }

        guard (char* p) : p_ (p) {}

        void
        release () { p_ = 0; }

      private:
        char* p_;
      };
    }

    inline void string_sequence::
    push_back (char* x)
    {
      string_sequence_bits::guard g (x);

      if (capacity_ < size_ + 1)
        grow_ (0, sizeof (char*), 0);

      static_cast<char**> (data_)[size_++] = x;

      g.release ();
    }

    inline string_sequence::iterator string_sequence::
    insert (iterator i, char* x)
    {
      string_sequence_bits::guard g (x);
      char** p = static_cast<char**> (insert_ (i, sizeof (char*), 0, 0));
      *p = x;
      g.release ();
      return p;
    }

    inline void string_sequence::
    reserve (size_t n)
    {
      if (capacity_ < n)
        grow_ (n, sizeof (char*), 0);
    }

    inline void string_sequence::
    _copy (string_sequence& c) const
    {
      copy (c);
    }
#else
    inline sequence_base::error string_sequence::
    push_back (char* x)
    {
      error r = error_none;

      if (capacity_ < size_ + 1)
        r = grow_ (0, sizeof (char*), 0);

      if (r == error_none)
        static_cast<char**> (data_)[size_++] = x;
      else
#ifndef XSDE_CUSTOM_ALLOCATOR
        delete[] x;
#else
        cxx::free (x);
#endif

      return r;
    }

    inline sequence_base::error string_sequence::
    insert (iterator i, char* x)
    {
      char** p = static_cast<char**> (insert_ (i, sizeof (char*), 0, 0));

      if (p)
      {
        *p = x;
        return error_none;
      }
      else
      {
#ifndef XSDE_CUSTOM_ALLOCATOR
        delete[] x;
#else
        cxx::free (x);
#endif
        return error_no_memory;
      }
    }

    inline sequence_base::error string_sequence::
    insert (iterator i, char* x, iterator& r)
    {
      char** p = static_cast<char**> (insert_ (i, sizeof (char*), 0, 0));

      if (p)
      {
        *p = x;
        r = p;
        return error_none;
      }
      else
      {
#ifndef XSDE_CUSTOM_ALLOCATOR
        delete[] x;
#else
        cxx::free (x);
#endif
        return error_no_memory;
      }
    }

    inline sequence_base::error string_sequence::
    reserve (size_t n)
    {
      error r = error_none;
      if (capacity_ < n)
        r = grow_ (n, sizeof (char*), 0);
      return r;
    }

    inline bool string_sequence::
    _copy (string_sequence& c) const
    {
      return copy (c) == error_none;
    }
#endif

    inline char* string_sequence::
    detach (iterator p)
    {
      char* r = *p;
      *p = 0;
      return r;
    }

    inline void string_sequence::
    attach (iterator p, char* x)
    {
#ifndef XSDE_CUSTOM_ALLOCATOR
      delete[] *p;
#else
      cxx::free (*p);
#endif

      *p = x;
    }

    //
    //
    inline bool
    operator!= (const string_sequence& x, const string_sequence& y)
    {
      return !(x == y);
    }
  }
}
