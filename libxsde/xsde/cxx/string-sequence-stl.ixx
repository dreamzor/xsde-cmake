// file      : xsde/cxx/string-sequence-stl.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

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
      return size_t (-1) / sizeof (std::string);
    }

    inline void string_sequence::
    swap (string_sequence& x)
    {
      swap_ (x);
    }

    inline std::string* string_sequence::
    begin ()
    {
      return static_cast<std::string*> (data_);
    }

    inline const std::string* string_sequence::
    begin () const
    {
      // g++ 2.95 does not like static_cast here.
      //
      return (const std::string*) (data_);
    }

    inline std::string* string_sequence::
    end ()
    {
      return static_cast<std::string*> (data_) + size_;
    }

    inline const std::string* string_sequence::
    end () const
    {
      return ((const std::string*) (data_)) + size_;
    }

    inline std::string& string_sequence::
    front ()
    {
      return *static_cast<std::string*> (data_);
    }

    inline const std::string& string_sequence::
    front () const
    {
      return *((const std::string*) (data_));
    }

    inline std::string& string_sequence::
    back ()
    {
      return static_cast<std::string*> (data_)[size_ - 1];
    }

    inline const std::string& string_sequence::
    back () const
    {
      return ((const std::string*) (data_))[size_ - 1];
    }

    inline std::string& string_sequence::
    operator[] (size_t i)
    {
      return static_cast<std::string*> (data_)[i];
    }

    inline const std::string& string_sequence::
    operator[] (size_t i) const
    {
      return ((const std::string*) (data_))[i];
    }

    inline void string_sequence::
    pop_back ()
    {
      typedef std::string type;
      static_cast<std::string*> (data_)[size_ - 1].~type ();
      --size_;
    }

    inline std::string* string_sequence::
    erase (std::string* i)
    {
      if (i != static_cast<std::string*> (data_) + (size_ - 1))
        erase_ (i, sizeof (std::string), &move_forward_);
      else
      {
        typedef std::string type;
        static_cast<std::string*> (data_)[size_ - 1].~type ();
        --size_;
      }

      return i;
    }

#ifdef XSDE_EXCEPTIONS
    inline void string_sequence::
    push_back (const std::string& x)
    {
      if (capacity_ < size_ + 1)
        grow_ (0, sizeof (std::string), &move_);

      new (static_cast<std::string*> (data_) + size_) std::string (x);
      size_++;
    }

    inline std::string* string_sequence::
    insert (std::string* i, const std::string& x)
    {
      std::string* p = static_cast<std::string*> (
        insert_ (i, sizeof (std::string), &move_, &move_backward_));
      *p = x;
      return p;
    }

    inline void string_sequence::
    reserve (size_t n)
    {
      if (capacity_ < n)
        grow_ (n, sizeof (std::string), &move_);
    }

    inline void string_sequence::
    _copy (string_sequence& c) const
    {
      copy (c);
    }

#else
    inline sequence_base::error string_sequence::
    push_back (const std::string& x)
    {
      error r = error_none;

      if (capacity_ < size_ + 1)
        r = grow_ (0, sizeof (std::string), &move_);

      if (r == error_none)
      {
        new (static_cast<std::string*> (data_) + size_) std::string (x);
        size_++;
      }

      return r;
    }

    inline sequence_base::error string_sequence::
    insert (std::string* i, const std::string& x)
    {
      std::string* p = static_cast<std::string*> (
        insert_ (i, sizeof (std::string), &move_, &move_backward_));

      if (p)
      {
        *p = x;
        return error_none;
      }
      else
        return error_no_memory;
    }

    inline sequence_base::error string_sequence::
    insert (std::string* i, const std::string& x, std::string*& r)
    {
      std::string* p = static_cast<std::string*> (
        insert_ (i, sizeof (std::string), &move_, &move_backward_));

      if (p)
      {
        *p = x;
        r = p;
        return error_none;
      }
      else
        return error_no_memory;
    }

    inline sequence_base::error string_sequence::
    reserve (size_t n)
    {
      error r = error_none;
      if (capacity_ < n)
        r = grow_ (n, sizeof (std::string), &move_);
      return r;
    }

    inline bool string_sequence::
    _copy (string_sequence& c) const
    {
      return copy (c) == error_none;
    }
#endif

    inline bool
    operator!= (const string_sequence& x, const string_sequence& y)
    {
      return !(x == y);
    }
  }
}
