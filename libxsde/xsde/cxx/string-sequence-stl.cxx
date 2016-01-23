// file      : xsde/cxx/string-sequence-stl.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/string-sequence-stl.hxx>

#ifdef XSDE_CUSTOM_ALLOCATOR
#  include <xsde/cxx/allocator.hxx>
#endif

namespace xsde
{
  namespace cxx
  {
    void string_sequence::
    clear ()
    {
      typedef std::string type;
      for (size_t i = 0;  i < size_; ++i)
        static_cast<std::string*> (data_)[i].~type ();

      size_ = 0;
    }

#ifdef XSDE_EXCEPTIONS
    void string_sequence::
    copy (string_sequence& c) const
    {
      if (c.size_ != 0)
        c.clear ();

      c.reserve (size_);

      for (; c.size_ < size_; ++c.size_)
      {
        new (static_cast<std::string*> (c.data_) + c.size_) std::string (
          static_cast<std::string*> (data_)[c.size_]);
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
    sequence_base::error string_sequence::
    copy (string_sequence& c) const
    {
      if (c.size_ != 0)
        c.clear ();

      if (error r = c.reserve (size_))
        return r;

      for (; c.size_ < size_; ++c.size_)
      {
        new (static_cast<std::string*> (c.data_) + c.size_) std::string (
          static_cast<std::string*> (data_)[c.size_]);
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

#ifdef XSDE_EXCEPTIONS
    struct guard
    {
      guard (std::string* p, size_t& n) : p_ (p), n_ (n) {}

      ~guard ()
      {
        typedef std::string type;
        if (p_)
          for (; n_ > 0; --n_)
            p_[n_ - 1].~type ();
      }

      void
      release () { p_ = 0; }

    private:
      std::string* p_;
      size_t& n_;
    };

    void string_sequence::
    move_ (void* dst, void* src, size_t n)
    {
      std::string* d = static_cast<std::string*> (dst);
      std::string* s = static_cast<std::string*> (src);

      // The copy c-tor can throw in which case we need to destroy
      // whatever objects we already copied into d.
      //
      size_t i = 0;
      guard g (d, i);

      for (; i < n; i++)
        new (d + i) std::string (s[i]);

      g.release ();

      typedef std::string type;
      for (size_t j = 0; j < n; j++)
        s[j].~type ();
    }
#else
    void string_sequence::
    move_ (void* dst, void* src, size_t n)
    {
      std::string* d = static_cast<std::string*> (dst);
      std::string* s = static_cast<std::string*> (src);

      for (size_t i = 0; i < n; i++)
      {
        typedef std::string type;
        new (d + i) std::string (s[i]);
        s[i].~type ();
      }
    }
#endif

    void string_sequence::
    move_forward_ (void* p, size_t n)
    {
      // We are moving a sequence of elements one position to the left.
      // The tricky part is to make sure we are in at least destructable
      // state if things turn bad. We assume that there is a valid
      // element at position p.
      //
      std::string* d = static_cast<std::string*> (p);

      for (size_t i = 0; i < n; i++)
        d[i] = d[i + 1];

      typedef std::string type;
      d[n].~type ();
    }

#ifdef XSDE_EXCEPTIONS
    void string_sequence::
    move_backward_ (void* p, size_t n, size_t& size)
    {
      // We are moving a sequence of elements one position to the right.
      // The tricky part is to make sure we are in at least destructable
      // state if things turn bad.
      //
      std::string* d = static_cast<std::string*> (p);
      std::string* e = d + n;

      new (e) std::string;
      size++;

      for (size_t i = n; i > 0; i--)
        d[i] = d[i - 1];
    }
#else
    void string_sequence::
    move_backward_ (void* p, size_t n)
    {
      // We are moving a sequence of elements one position to the right.
      //
      std::string* d = static_cast<std::string*> (p);
      std::string* e = d + n;

      new (e) std::string;

      for (size_t i = n; i > 0; i--)
        d[i] = d[i - 1];
    }
#endif

    bool
    operator== (const string_sequence& x, const string_sequence& y)
    {
      if (x.size () != y.size ())
        return false;

      for (string_sequence::const_iterator
             xi (x.begin ()), yi (y.begin ()), xe (x.end ());
           xi != xe; ++xi, ++yi)
      {
        if (*xi != *yi)
          return false;
      }

      return true;
    }
  }
}
