// file      : xsde/cxx/hybrid/xdr/ostream.ixx
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
      typedef  bool_t (*oxdr_longlong_p) (XDR*, long long*);

      extern "C"
      typedef  bool_t (*oxdr_u_longlong_p) (XDR*, unsigned long long*);

      inline oxdrstream::
      oxdrstream (XDR& xdr)
          : xdr_ (xdr)
      {
      }

      inline XDR& oxdrstream::
      impl ()
      {
        return xdr_;
      }

#ifdef XSDE_EXCEPTIONS

      inline void oxdrstream::
      operator<< (bool x)
      {
        bool_t v = static_cast<bool_t> (x);

        if (!xdr_bool (&xdr_, &v))
          throw xdr_exception ();
      }

      inline void oxdrstream::
      operator<< (signed char x)
      {
        char v = static_cast<char> (x);

        if (!xdr_char (&xdr_, &v))
          throw xdr_exception ();
      }


      inline void oxdrstream::
      operator<< (unsigned char x)
      {
        if (!xdr_u_char (&xdr_, &x))
          throw xdr_exception ();
      }

      inline void oxdrstream::
      operator<< (short x)
      {
        if (!xdr_short (&xdr_, &x))
          throw xdr_exception ();
      }

      inline void oxdrstream::
      operator<< (unsigned short x)
      {
        if (!xdr_u_short (&xdr_, &x))
          throw xdr_exception ();
      }

      inline void oxdrstream::
      operator<< (int x)
      {
        if (!xdr_int (&xdr_, &x))
          throw xdr_exception ();
      }

      inline void oxdrstream::
      operator<< (unsigned int x)
      {
        if (!xdr_u_int (&xdr_, &x))
          throw xdr_exception ();
      }

      inline void oxdrstream::
      operator<< (long x)
      {
        int v = static_cast<int> (x);

        if (!xdr_int (&xdr_, &v))
          throw xdr_exception ();
      }

      inline void oxdrstream::
      operator<< (unsigned long x)
      {
        unsigned int v = static_cast<unsigned int> (x);

        if (!xdr_u_int (&xdr_, &v))
          throw xdr_exception ();
      }

#ifdef XSDE_LONGLONG
      inline void oxdrstream::
      operator<< (long long x)
      {
        oxdr_longlong_p f =
          reinterpret_cast<oxdr_longlong_p> (::xdr_longlong_t);

        if (!f (&xdr_, &x))
          throw xdr_exception ();
      }

      inline void oxdrstream::
      operator<< (unsigned long long x)
      {
        oxdr_u_longlong_p f =
          reinterpret_cast<oxdr_u_longlong_p> (::xdr_u_longlong_t);

        if (!f (&xdr_, &x))
          throw xdr_exception ();
      }
#endif

      inline void oxdrstream::
      operator<< (as_size x)
      {
        // Assume size is 32-bit.
        //
        unsigned int v = static_cast<unsigned int> (x.s_);

        if (!xdr_u_int (&xdr_, &v))
          throw xdr_exception ();
      }

      inline void oxdrstream::
      operator<< (float x)
      {
        if (!xdr_float (&xdr_, &x))
          throw xdr_exception ();
      }

      inline void oxdrstream::
      operator<< (double x)
      {
        if (!xdr_double (&xdr_, &x))
          throw xdr_exception ();
      }

      inline void
      operator<< (oxdrstream&, const any_type&)
      {
      }

#else // XSDE_EXCEPTIONS

      inline bool oxdrstream::
      operator<< (bool x)
      {
        bool_t v = static_cast<bool_t> (x);
        return xdr_bool (&xdr_, &v);
      }

      inline bool oxdrstream::
      operator<< (signed char x)
      {
        char v = static_cast<char> (x);
        return xdr_char (&xdr_, &v);
      }

      inline bool oxdrstream::
      operator<< (unsigned char x)
      {
        return xdr_u_char (&xdr_, &x);
      }

      inline bool oxdrstream::
      operator<< (short x)
      {
        return xdr_short (&xdr_, &x);
      }

      inline bool oxdrstream::
      operator<< (unsigned short x)
      {
        return xdr_u_short (&xdr_, &x);
      }

      inline bool oxdrstream::
      operator<< (int x)
      {
        return xdr_int (&xdr_, &x);
      }

      inline bool oxdrstream::
      operator<< (unsigned int x)
      {
        return xdr_u_int (&xdr_, &x);
      }

      inline bool oxdrstream::
      operator<< (long x)
      {
        int v = static_cast<int> (x);
        return xdr_int (&xdr_, &v);
      }

      inline bool oxdrstream::
      operator<< (unsigned long x)
      {
        unsigned int v = static_cast<unsigned int> (x);
        return xdr_u_int (&xdr_, &v);
      }

#ifdef XSDE_LONGLONG
      inline bool oxdrstream::
      operator<< (long long x)
      {
        oxdr_longlong_p f =
          reinterpret_cast<oxdr_longlong_p> (::xdr_longlong_t);

        return f (&xdr_, &x);
      }

      inline bool oxdrstream::
      operator<< (unsigned long long x)
      {
        oxdr_u_longlong_p f =
          reinterpret_cast<oxdr_u_longlong_p> (::xdr_u_longlong_t);

        return f (&xdr_, &x);
      }
#endif

      inline bool oxdrstream::
      operator<< (as_size x)
      {
        // Assume size is 32-bit.
        //
        unsigned int v = static_cast<unsigned int> (x.s_);
        return xdr_u_int (&xdr_, &v);
      }

      inline bool oxdrstream::
      operator<< (float x)
      {
        return xdr_float (&xdr_, &x);
      }

      inline bool oxdrstream::
      operator<< (double x)
      {
        return xdr_double (&xdr_, &x);
      }

      inline bool
      operator<< (oxdrstream&, const any_type&)
      {
        return true;
      }

#endif // XSDE_EXCEPTIONS
    }
  }
}
