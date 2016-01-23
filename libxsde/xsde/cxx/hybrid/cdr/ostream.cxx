// file      : xsde/cxx/hybrid/cdr/ostream.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/config.hxx>

#ifndef XSDE_STL
#  include <string.h>
#endif

#include <xsde/cxx/hybrid/cdr/ostream.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace hybrid
    {
#ifdef XSDE_EXCEPTIONS

      // CDR strings always use 32-bit length.
      //
#ifdef XSDE_STL
      void ocdrstream::
      operator<< (const std::string& x)
      {
        if (!cdr_.write_string (
              static_cast<ACE_CDR::ULong> (x.length ()), x.c_str ()))
          throw cdr_exception ();
      }
#else
      void ocdrstream::
      operator<< (const char* x)
      {
        if (!cdr_.write_string (static_cast<ACE_CDR::ULong> (strlen (x)), x))
          throw cdr_exception ();
      }
#endif

      void ocdrstream::
      operator<< (const buffer& x)
      {
        // CDR arrays are limited to 32-bit size.
        //
        size_t n = x.size ();

        if (!cdr_.write_ulong (static_cast<ACE_CDR::ULong> (n)) ||
            !cdr_.write_octet_array (
              reinterpret_cast<const ACE_CDR::Octet*> (x.data ()), n))
          throw cdr_exception ();
      }

#else // XSDE_EXCEPTIONS

#ifdef XSDE_STL
      bool ocdrstream::
      operator<< (const std::string& x)
      {
        return cdr_.write_string (
          static_cast<ACE_CDR::ULong> (x.length ()), x.c_str ());
      }
#else
      bool ocdrstream::
      operator<< (const char* x)
      {
        return cdr_.write_string (
          static_cast<ACE_CDR::ULong> (strlen (x)), x);
      }
#endif

      bool ocdrstream::
      operator<< (const buffer& x)
      {
        // CDR arrays are limited to 32-bit size.
        //
        size_t n = x.size ();

        return cdr_.write_ulong (static_cast<ACE_CDR::ULong> (n)) &&
          cdr_.write_octet_array (
            reinterpret_cast<const ACE_CDR::Octet*> (x.data ()), n);
      }

#endif // XSDE_EXCEPTIONS

    }
  }
}
