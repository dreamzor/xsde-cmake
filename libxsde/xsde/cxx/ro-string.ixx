// file      : xsde/cxx/ro-string.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <string.h>

namespace xsde
{
  namespace cxx
  {
    inline ro_string::
    ro_string ()
        : data_ (0), size_ (0)
    {
    }

    inline ro_string::
    ro_string (const char* s)
        : data_ (s), size_ (s ? strlen (s) : 0)
    {
    }

    inline ro_string::
    ro_string (const char* s, size_t size)
        : data_ (s), size_ (size)
    {
    }

    inline ro_string::
    ro_string (const string& s)
        : data_ (s.data ()), size_ (s.size ())
    {
    }

#ifdef XSDE_STL
    inline ro_string::
    ro_string (const std::string& s)
        : data_ (s.data ()), size_ (s.size ())
    {
    }

    inline ro_string::
    operator std::string () const
    {
      return size () ? std::string (data (), size ()) : std::string ();
    }
#endif

    inline const char* ro_string::
    data () const
    {
      return data_;
    }

    inline size_t ro_string::
    size () const
    {
      return size_;
    }

    inline size_t ro_string::
    length () const
    {
      return size_;
    }

    inline bool ro_string::
    empty () const
    {
      return size_ == 0;
    }

    inline char ro_string::
    operator[] (size_t pos) const
    {
      return data_[pos];
    }

    inline void ro_string::
    assign (const char* s)
    {
      data_ = s;
      size_ = s ? strlen (s) : 0;
    }

    inline void ro_string::
    assign (const char* s, size_t size)
    {
      data_ = s;
      size_ = size;
    }

    inline void ro_string::
    assign (const ro_string& s)
    {
      data_ = s.data ();
      size_ = s.size ();
    }

    inline void ro_string::
    assign (const string& s)
    {
      data_ = s.data ();
      size_ = s.size ();
    }

#ifdef XSDE_STL
    inline void ro_string::
    assign (const std::string& s)
    {
      data_ = s.c_str ();
      size_ = s.size ();
    }
#endif

    inline int ro_string::
    compare (const ro_string& str) const
    {
      return compare (str.data (), str.size ());
    }

    inline int ro_string::
    compare (const char* str) const
    {
      return compare (str, str ? strlen (str) : 0);
    }

    inline int ro_string::
    compare (const char* str, size_t n) const
    {
      size_t s = size_ < n ? size_ : n;

      int r = s != 0 ? strncmp (data_, str, s) : 0;

      if (!r && size_ != n)
        r = size_ < n ? -1 : 1;

      return r;
    }

    inline int ro_string::
    compare (const string& s) const
    {
      return compare (s.data (), s.size ());
    }

#ifdef XSDE_STL
    inline int ro_string::
    compare (const std::string& str) const
    {
      return compare (str.c_str (), str.size ());
    }
#endif

    inline size_t ro_string::
    find (char c, size_type pos) const
    {
      for (; pos < size_; ++pos)
        if (data_[pos] == c)
          return pos;

      return npos;
    }

    // operator ==
    //

    inline bool
    operator== (const ro_string& a, const ro_string& b)
    {
      return a.compare (b) == 0;
    }

    inline bool
    operator== (const ro_string& a, const char* b)
    {
      return a.compare (b) == 0;
    }

    inline bool
    operator== (const char* a, const ro_string& b)
    {
      return b.compare (a) == 0;
    }

    inline bool
    operator== (const ro_string& a, const string& b)
    {
      return a.compare (b) == 0;
    }

    inline bool
    operator== (const string& a, const ro_string& b)
    {
      return b.compare (a) == 0;
    }

#ifdef XSDE_STL
    inline bool
    operator== (const ro_string& a, const std::string& b)
    {
      return a.compare (b) == 0;
    }

    inline bool
    operator== (const std::string& a, const ro_string& b)
    {
      return b.compare (a) == 0;
    }
#endif


    // operator !=
    //

    inline bool
    operator!= (const ro_string& a, const ro_string& b)
    {
      return a.compare (b) != 0;
    }

    inline bool
    operator!= (const ro_string& a, const char* b)
    {
      return a.compare (b) != 0;
    }

    inline bool
    operator!= (const char* a, const ro_string& b)
    {
      return b.compare (a) != 0;
    }

    inline bool
    operator!= (const ro_string& a, const string& b)
    {
      return a.compare (b) != 0;
    }

    inline bool
    operator!= (const string& a, const ro_string& b)
    {
      return b.compare (a) != 0;
    }

#ifdef XSDE_STL
    inline bool
    operator!= (const ro_string& a, const std::string& b)
    {
      return a.compare (b) != 0;
    }

    inline bool
    operator!= (const std::string& a, const ro_string& b)
    {
      return b.compare (a) != 0;
    }
#endif


    // operator <
    //

    inline bool
    operator< (const ro_string& l, const ro_string& r)
    {
      return l.compare (r) < 0;
    }

    inline bool
    operator< (const ro_string& l, const char* r)
    {
      return l.compare (r) < 0;
    }

    inline bool
    operator< (const char* l, const ro_string& r)
    {
      return r.compare (l) > 0;
    }

#ifdef XSDE_STL
    inline bool
    operator< (const ro_string& l, const std::string& r)
    {
      return l.compare (r) < 0;
    }

    inline bool
    operator< (const std::string& l, const ro_string& r)
    {
      return r.compare (l) > 0;
    }
#endif


    // operator >
    //

    inline bool
    operator> (const ro_string& l, const ro_string& r)
    {
      return l.compare (r) > 0;
    }

    inline bool
    operator> (const ro_string& l, const char* r)
    {
      return l.compare (r) > 0;
    }

    inline bool
    operator> (const char* l, const ro_string& r)
    {
      return r.compare (l) < 0;
    }

#ifdef XSDE_STL
    inline bool
    operator> (const ro_string& l, const std::string& r)
    {
      return l.compare (r) > 0;
    }

    inline bool
    operator> (const std::string& l, const ro_string& r)
    {
      return r.compare (l) < 0;
    }
#endif


    // operator <=
    //

    inline bool
    operator<= (const ro_string& l, const ro_string& r)
    {
      return l.compare (r) <= 0;
    }

    inline bool
    operator<= (const ro_string& l, const char* r)
    {
      return l.compare (r) <= 0;
    }

    inline bool
    operator<= (const char* l, const ro_string& r)
    {
      return r.compare (l) >= 0;
    }

#ifdef XSDE_STL
    inline bool
    operator<= (const ro_string& l, const std::string& r)
    {
      return l.compare (r) <= 0;
    }

    inline bool
    operator<= (const std::string& l, const ro_string& r)
    {
      return r.compare (l) >= 0;
    }
#endif


    // operator>=
    //

    inline bool
    operator>= (const ro_string& l, const ro_string& r)
    {
      return l.compare (r) >= 0;
    }

    inline bool
    operator>= (const ro_string& l, const char* r)
    {
      return l.compare (r) >= 0;
    }

    inline bool
    operator>= (const char* l, const ro_string& r)
    {
      return r.compare (l) <= 0;
    }

#ifdef XSDE_STL
    inline bool
    operator>= (const ro_string& l, const std::string& r)
    {
      return l.compare (r) >= 0;
    }

    inline bool
    operator>= (const std::string& l, const ro_string& r)
    {
      return r.compare (l) <= 0;
    }
#endif

    // operator +=
    //
#ifdef XSDE_STL
    inline std::string&
    operator+= (std::string& l, const ro_string& r)
    {
      l.append (r.data (), r.size ());
      return l;
    }
#endif
  }
}
