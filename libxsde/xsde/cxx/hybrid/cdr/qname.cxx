// file      : xsde/cxx/hybrid/cdr/qname.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/hybrid/cdr/istream.hxx>
#include <xsde/cxx/hybrid/cdr/ostream.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace hybrid
    {
#ifdef XSDE_EXCEPTIONS

      void
      operator<< (ocdrstream& s, const qname& x)
      {
        s << x.prefix ();
        s << x.name ();
      }

      void
      operator>> (icdrstream& s, qname& x)
      {

#ifdef XSDE_STL
        std::string p, n;
#else
        char* p;
        char* n;
#endif
        s >> p;
        x.prefix (p);

        s >> n; // x will free p in case extraction fails
        x.name (n);
      }

#else // XSDE_EXCEPTIONS

      bool
      operator<< (ocdrstream& s, const qname& x)
      {
        return s << x.prefix () && s << x.name ();
      }

      bool
      operator>> (icdrstream& s, qname& x)
      {

#ifdef XSDE_STL
        std::string p, n;
#else
        char* p;
        char* n;
#endif
        if (!(s >> p))
          return false;

        x.prefix (p);

        if (!(s >> n))
          return false; // x will free p

        x.name (n);
        return true;
      }

#endif // XSDE_EXCEPTIONS
    }
  }
}
