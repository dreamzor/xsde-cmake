// file      : xsde/cxx/hybrid/xdr/ostream.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/config.hxx>

#ifndef XSDE_STL
#  include <string.h>
#endif

#include <xsde/cxx/hybrid/xdr/ostream.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace hybrid
    {
#ifdef XSDE_EXCEPTIONS

      // XDR strings always use 32-bit length.
      //
#ifdef XSDE_STL
      void oxdrstream::
      operator<< (const std::string& x)
      {
        char* p = const_cast<char*> (x.c_str ());
        unsigned int n = static_cast<unsigned int> (x.length ());

        if (!xdr_u_int (&xdr_, &n) || !xdr_opaque (&xdr_, p, n))
          throw xdr_exception ();
      }
#else
      void oxdrstream::
      operator<< (const char* x)
      {
        unsigned int n = static_cast<unsigned int> (strlen (x));

        if (!xdr_u_int (&xdr_, &n) ||
            !xdr_opaque (&xdr_, const_cast<char*> (x), n))
          throw xdr_exception ();
      }
#endif

      void oxdrstream::
      operator<< (const buffer& x)
      {
        // XDR arrays are limited to 32-bit size.
        //
        unsigned int n = static_cast<unsigned int> (x.size ());

        if (!xdr_u_int (&xdr_, &n) ||
            !xdr_opaque (&xdr_, const_cast<char*> (x.data ()), n))
          throw xdr_exception ();
      }

#else // XSDE_EXCEPTIONS

#ifdef XSDE_STL
      bool oxdrstream::
      operator<< (const std::string& x)
      {
        char* p = const_cast<char*> (x.c_str ());
        unsigned int n = static_cast<unsigned int> (x.length ());
        return xdr_u_int (&xdr_, &n) && xdr_opaque (&xdr_, p, n);
      }
#else
      bool oxdrstream::
      operator<< (const char* x)
      {
        unsigned int n = static_cast<unsigned int> (strlen (x));
        return xdr_u_int (&xdr_, &n) &&
          xdr_opaque (&xdr_, const_cast<char*> (x), n);
      }
#endif

      bool oxdrstream::
      operator<< (const buffer& x)
      {
        // XDR arrays are limited to 32-bit size.
        //
        unsigned int n = static_cast<unsigned int> (x.size ());
        return xdr_u_int (&xdr_, &n) &&
          xdr_opaque (&xdr_, const_cast<char*> (x.data ()), n);
      }

#endif // XSDE_EXCEPTIONS

    }
  }
}
