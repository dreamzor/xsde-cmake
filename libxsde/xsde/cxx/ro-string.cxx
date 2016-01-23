// file      : xsde/cxx/ro-string.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/ro-string.hxx>

#ifdef XSDE_IOSTREAM
#  include <iostream>
#endif

namespace xsde
{
  namespace cxx
  {
    // ro_string
    const size_t ro_string::npos = ~(size_t (0));
  
    // operator <<
    //
#ifdef XSDE_IOSTREAM
    std::ostream&
    operator<< (std::ostream& os, const ro_string& str)
    {
      if (str.size () != 0)
        os.write (str.data (), str.size ());

      return os;
    }
#endif

    size_t
    trim_left (ro_string& s)
    {
      size_t size = s.size ();

      if (size != 0)
      {
        const char* f = s.data ();
        const char* l = f + size;
        const char* of = f;

        while (f < l &&
               (*f == 0x20 || *f == 0x0A || *f == 0x0D || *f == 0x09))
          ++f;

        if (f != of)
        {
          size = f <= l ? l - f : 0;
          s.assign ((f <= l ? f : 0), size);
        }
      }

      return size;
    }

    size_t
    trim_right (ro_string& s)
    {
      size_t size = s.size ();

      if (size != 0)
      {
        const char* f = s.data ();
        const char* l = f + size - 1;
        const char* ol = l;

        while (l > f &&
               (*l == 0x20 || *l == 0x0A || *l == 0x0D || *l == 0x09))
          --l;

        if (l != ol)
        {
          size = f <= l ? l - f + 1 : 0;
          s.assign ((f <= l ? f : 0), size);
        }
      }

      return size;
    }

    size_t
    trim (ro_string& s)
    {
      size_t size = s.size ();

      if (size != 0)
      {
        const char* f = s.data ();
        const char* l = f + size;

        const char* of = f;

        while (f < l &&
               (*f == 0x20 || *f == 0x0A || *f == 0x0D || *f == 0x09))
          ++f;

        --l;

        const char* ol = l;

        while (l > f &&
               (*l == 0x20 || *l == 0x0A || *l == 0x0D || *l == 0x09))
          --l;

        if (f != of || l != ol)
        {
          size = f <= l ? l - f + 1 : 0;
          s.assign ((f <= l ? f : 0), size);
        }
      }

      return size;
    }
  }
}
