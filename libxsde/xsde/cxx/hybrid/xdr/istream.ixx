// file      : xsde/cxx/hybrid/xdr/istream.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsde
{
  namespace cxx
  {
    namespace hybrid
    {
      extern "C"
      typedef  bool_t (*ixdr_longlong_p) (XDR*, long long*);

      extern "C"
      typedef  bool_t (*ixdr_u_longlong_p) (XDR*, unsigned long long*);

      inline ixdrstream::
      ixdrstream (XDR& xdr)
          : xdr_ (xdr)
      {
      }

      inline XDR& ixdrstream::
      impl ()
      {
        return xdr_;
      }

#ifdef XSDE_EXCEPTIONS

      inline void ixdrstream::
      operator>> (bool& x)
      {
        bool_t v;

        if (!xdr_bool (&xdr_, &v))
          throw xdr_exception ();

        x = static_cast<bool> (v);
      }

      inline void ixdrstream::
      operator>> (signed char& x)
      {
        char v;

        if (!xdr_char (&xdr_, &v))
          throw xdr_exception ();

        x = static_cast<signed char> (v);
      }


      inline void ixdrstream::
      operator>> (unsigned char& x)
      {
        if (!xdr_u_char (&xdr_, &x))
          throw xdr_exception ();
      }

      inline void ixdrstream::
      operator>> (short& x)
      {
        if (!xdr_short (&xdr_, &x))
          throw xdr_exception ();
      }

      inline void ixdrstream::
      operator>> (unsigned short& x)
      {
        if (!xdr_u_short (&xdr_, &x))
          throw xdr_exception ();
      }

      inline void ixdrstream::
      operator>> (int& x)
      {
        if (!xdr_int (&xdr_, &x))
          throw xdr_exception ();
      }

      inline void ixdrstream::
      operator>> (unsigned int& x)
      {
        if (!xdr_u_int (&xdr_, &x))
          throw xdr_exception ();
      }

      inline void ixdrstream::
      operator>> (long& x)
      {
        int v;

        if (!xdr_int (&xdr_, &v))
          throw xdr_exception ();

        x = static_cast<long> (v);
      }

      inline void ixdrstream::
      operator>> (unsigned long& x)
      {
        unsigned int v;

        if (!xdr_u_int (&xdr_, &v))
          throw xdr_exception ();

        x = static_cast<unsigned long> (v);
      }

#ifdef XSDE_LONGLONG
      inline void ixdrstream::
      operator>> (long long& x)
      {
        ixdr_longlong_p f =
          reinterpret_cast<ixdr_longlong_p> (::xdr_longlong_t);

        if (!f (&xdr_, &x))
          throw xdr_exception ();
      }

      inline void ixdrstream::
      operator>> (unsigned long long& x)
      {
        ixdr_u_longlong_p f =
          reinterpret_cast<ixdr_u_longlong_p> (::xdr_u_longlong_t);

        if (!f (&xdr_, &x))
          throw xdr_exception ();
      }
#endif

      inline void ixdrstream::
      operator>> (as_size& x)
      {
        // Assume size is 32-bit.
        //
        unsigned int v;

        if (!xdr_u_int (&xdr_, &v))
          throw xdr_exception ();

        x.s_ = static_cast<size_t> (v);
      }

      inline void ixdrstream::
      operator>> (float& x)
      {
        if (!xdr_float (&xdr_, &x))
          throw xdr_exception ();
      }

      inline void ixdrstream::
      operator>> (double& x)
      {
        if (!xdr_double (&xdr_, &x))
          throw xdr_exception ();
      }

      inline void
      operator>> (ixdrstream&, any_type&)
      {
      }

#else // XSDE_EXCEPTIONS

      inline bool ixdrstream::
      operator>> (bool& x)
      {
        bool_t v;

        if (!xdr_bool (&xdr_, &v))
          return false;

        x = static_cast<bool> (v);
        return true;
      }

      inline bool ixdrstream::
      operator>> (signed char& x)
      {
        char v;

        if (!xdr_char (&xdr_, &v))
          return false;

        x = static_cast<signed char> (v);
        return true;
      }


      inline bool ixdrstream::
      operator>> (unsigned char& x)
      {
        return xdr_u_char (&xdr_, &x);
      }

      inline bool ixdrstream::
      operator>> (short& x)
      {
        return xdr_short (&xdr_, &x);
      }

      inline bool ixdrstream::
      operator>> (unsigned short& x)
      {
        return xdr_u_short (&xdr_, &x);
      }

      inline bool ixdrstream::
      operator>> (int& x)
      {
        return xdr_int (&xdr_, &x);
      }

      inline bool ixdrstream::
      operator>> (unsigned int& x)
      {
        return xdr_u_int (&xdr_, &x);
      }

      inline bool ixdrstream::
      operator>> (long& x)
      {
        int v;

        if (!xdr_int (&xdr_, &v))
          return false;

        x = static_cast<long> (v);
        return true;
      }

      inline bool ixdrstream::
      operator>> (unsigned long& x)
      {
        unsigned int v;

        if (!xdr_u_int (&xdr_, &v))
          return false;

        x = static_cast<unsigned long> (v);
        return true;
      }

#ifdef XSDE_LONGLONG
      inline bool ixdrstream::
      operator>> (long long& x)
      {
        ixdr_longlong_p f =
          reinterpret_cast<ixdr_longlong_p> (::xdr_longlong_t);

        return f (&xdr_, &x);
      }

      inline bool ixdrstream::
      operator>> (unsigned long long& x)
      {
        ixdr_u_longlong_p f =
          reinterpret_cast<ixdr_u_longlong_p> (::xdr_u_longlong_t);

        return f (&xdr_, &x);
      }
#endif

      inline bool ixdrstream::
      operator>> (as_size& x)
      {
        // Assume size is 32-bit.
        //
        unsigned int v;

        if (!xdr_u_int (&xdr_, &v))
          return false;

        x.s_ = static_cast<size_t> (v);
        return true;
      }

      inline bool ixdrstream::
      operator>> (float& x)
      {
        return xdr_float (&xdr_, &x);
      }

      inline bool ixdrstream::
      operator>> (double& x)
      {
        return xdr_double (&xdr_, &x);
      }

      inline bool
      operator>> (ixdrstream&, any_type&)
      {
        return true;
      }

#endif // XSDE_EXCEPTIONS
    }
  }
}
