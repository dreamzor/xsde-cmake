// file      : xsde/cxx/hybrid/xdr/string-sequence.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/hybrid/xdr/istream.hxx>
#include <xsde/cxx/hybrid/xdr/ostream.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace hybrid
    {
#ifdef XSDE_EXCEPTIONS

      void
      operator<< (oxdrstream& s, const string_sequence& x)
      {
        s << oxdrstream::as_size (x.size ());

        for (string_sequence::const_iterator i = x.begin ();
             i != x.end (); ++i)
        {
          s << *i;
        }
      }

      void
      operator>> (ixdrstream& s, string_sequence& x)
      {
        size_t n;
        ixdrstream::as_size as_size (n);
        s >> as_size;

        x.clear ();

        if (n > 0)
        {
          x.reserve (n);

#ifdef XSDE_STL
          std::string i;
#else
          char* i;
#endif
          while (n--)
          {
            s >> i;
            x.push_back (i);
          }
        }
      }

#else // XSDE_EXCEPTIONS

      bool
      operator<< (oxdrstream& s, const string_sequence& x)
      {
        if (!(s << oxdrstream::as_size (x.size ())))
          return false;

        for (string_sequence::const_iterator i = x.begin ();
             i != x.end (); ++i)
        {
          if (!(s << *i))
            return false;
        }

        return true;
      }

      bool
      operator>> (ixdrstream& s, string_sequence& x)
      {
        size_t n;
        ixdrstream::as_size as_size (n);

        if (!(s >> as_size))
          return false;

        x.clear ();

        if (n > 0)
        {
          if (x.reserve (n))
            return false;

#ifdef XSDE_STL
          std::string i;
#else
          char* i;
#endif
          while (n--)
          {
            if (!(s >> i) || x.push_back (i))
              return false;
          }
        }

        return true;
      }

#endif // XSDE_EXCEPTIONS
    }
  }
}
