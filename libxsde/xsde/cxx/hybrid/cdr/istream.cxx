// file      : xsde/cxx/hybrid/cdr/istream.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/hybrid/cdr/istream.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace hybrid
    {
#ifdef XSDE_EXCEPTIONS

#ifdef XSDE_STL
      struct str_guard
      {
        str_guard (char* s) : s_ (s) {}
        ~str_guard ()
        {
#ifndef XSDE_CUSTOM_ALLOCATOR
          delete[] s_;
#else
          cxx::free (s_);
#endif
        }

      private:
        char* s_;
      };

      void icdrstream::
      operator>> (std::string& x)
      {
        char* v;

        if (!cdr_.read_string (v))
          throw cdr_exception ();

        str_guard g (v);
        x = v;
      }
#else
      void icdrstream::
      operator>> (char*& x)
      {
        if (!cdr_.read_string (x))
          throw cdr_exception ();
      }
#endif

      void icdrstream::
      operator>> (buffer& x)
      {
        ACE_CDR::ULong n;

        if (!cdr_.read_ulong (n))
          throw cdr_exception ();

        x.size (n);

        if (!cdr_.read_octet_array (
              reinterpret_cast<ACE_CDR::Octet*> (x.data ()), n))
          throw cdr_exception ();
      }

#else // XSDE_EXCEPTIONS

#ifdef XSDE_STL
      bool icdrstream::
      operator>> (std::string& x)
      {
        char* v;

        if (!cdr_.read_string (v))
          return false;

        x = v;
#ifndef XSDE_CUSTOM_ALLOCATOR
        delete[] v;
#else
        cxx::free (v);
#endif
        return true;
      }
#else
      bool icdrstream::
      operator>> (char*& x)
      {
        return cdr_.read_string (x);
      }
#endif

      bool icdrstream::
      operator>> (buffer& x)
      {
        ACE_CDR::ULong n;

        if (!cdr_.read_ulong (n))
          return false;

        x.size (n);
        return cdr_.read_octet_array (
          reinterpret_cast<ACE_CDR::Octet*> (x.data ()), n);
      }

#endif // XSDE_EXCEPTIONS

    }
  }
}
