// file      : xsde/cxx/hybrid/cdr/istream.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsde
{
  namespace cxx
  {
    namespace hybrid
    {
      inline icdrstream::
      icdrstream (ACE_InputCDR& cdr)
          : cdr_ (cdr)
      {
      }

      inline ACE_InputCDR& icdrstream::
      impl ()
      {
        return cdr_;
      }

#ifdef XSDE_EXCEPTIONS

      inline void icdrstream::
      operator>> (bool& x)
      {
        ACE_CDR::Boolean v;

        if (!cdr_.read_boolean (v))
          throw cdr_exception ();

        x = static_cast<bool> (v);
      }

      inline void icdrstream::
      operator>> (signed char& x)
      {
        ACE_CDR::Octet v;

        if (!cdr_.read_octet (v))
          throw cdr_exception ();

        x = static_cast<signed char> (v);
      }


      inline void icdrstream::
      operator>> (unsigned char& x)
      {
        ACE_CDR::Octet v;

        if (!cdr_.read_octet (v))
          throw cdr_exception ();

        x = static_cast<unsigned char> (v);
      }

      inline void icdrstream::
      operator>> (short& x)
      {
        ACE_CDR::Short v;

        if (!cdr_.read_short (v))
          throw cdr_exception ();

        x = static_cast<short> (v);
      }

      inline void icdrstream::
      operator>> (unsigned short& x)
      {
        ACE_CDR::UShort v;

        if (!cdr_.read_ushort (v))
          throw cdr_exception ();

        x = static_cast<unsigned short> (v);
      }

      inline void icdrstream::
      operator>> (int& x)
      {
        ACE_CDR::Long v;

        if (!cdr_.read_long (v))
          throw cdr_exception ();

        x = static_cast<int> (v);
      }

      inline void icdrstream::
      operator>> (unsigned int& x)
      {
        ACE_CDR::ULong v;

        if (!cdr_.read_ulong (v))
          throw cdr_exception ();

        x = static_cast<unsigned int> (v);
      }

      inline void icdrstream::
      operator>> (long& x)
      {
        ACE_CDR::Long v;

        if (!cdr_.read_long (v))
          throw cdr_exception ();

        x = static_cast<long> (v);
      }

      inline void icdrstream::
      operator>> (unsigned long& x)
      {
        ACE_CDR::ULong v;

        if (!cdr_.read_ulong (v))
          throw cdr_exception ();

        x = static_cast<unsigned long> (v);
      }

#ifdef XSDE_LONGLONG
      inline void icdrstream::
      operator>> (long long& x)
      {
        ACE_CDR::LongLong v;

        if (!cdr_.read_longlong (v))
          throw cdr_exception ();

        x = static_cast<long long> (v);
      }

      inline void icdrstream::
      operator>> (unsigned long long& x)
      {
        ACE_CDR::ULongLong v;

        if (!cdr_.read_ulonglong (v))
          throw cdr_exception ();

        x = static_cast<unsigned long long> (v);
      }
#endif

      inline void icdrstream::
      operator>> (as_size& x)
      {
        // Assume size is 32-bit.
        //
        ACE_CDR::ULong v;

        if (!cdr_.read_ulong (v))
          throw cdr_exception ();

        x.s_ = static_cast<size_t> (v);
      }

      inline void icdrstream::
      operator>> (float& x)
      {
        ACE_CDR::Float v;

        if (!cdr_.read_float (v))
          throw cdr_exception ();

        x = static_cast<float> (v);
      }

      inline void icdrstream::
      operator>> (double& x)
      {
        ACE_CDR::Double v;

        if (!cdr_.read_double (v))
          throw cdr_exception ();

        x = static_cast<double> (v);
      }

      inline void
      operator>> (icdrstream&, any_type&)
      {
      }

#else // XSDE_EXCEPTIONS

      inline bool icdrstream::
      operator>> (bool& x)
      {
        ACE_CDR::Boolean v;

        if (!cdr_.read_boolean (v))
          return false;

        x = static_cast<bool> (v);
        return true;
      }

      inline bool icdrstream::
      operator>> (signed char& x)
      {
        ACE_CDR::Octet v;

        if (!cdr_.read_octet (v))
          return false;

        x = static_cast<signed char> (v);
        return true;
      }


      inline bool icdrstream::
      operator>> (unsigned char& x)
      {
        ACE_CDR::Octet v;

        if (!cdr_.read_octet (v))
          return false;

        x = static_cast<unsigned char> (v);
        return true;
      }

      inline bool icdrstream::
      operator>> (short& x)
      {
        ACE_CDR::Short v;

        if (!cdr_.read_short (v))
          return false;

        x = static_cast<short> (v);
        return true;
      }

      inline bool icdrstream::
      operator>> (unsigned short& x)
      {
        ACE_CDR::UShort v;

        if (!cdr_.read_ushort (v))
          return false;

        x = static_cast<unsigned short> (v);
        return true;
      }

      inline bool icdrstream::
      operator>> (int& x)
      {
        ACE_CDR::Long v;

        if (!cdr_.read_long (v))
          return false;

        x = static_cast<int> (v);
        return true;
      }

      inline bool icdrstream::
      operator>> (unsigned int& x)
      {
        ACE_CDR::ULong v;

        if (!cdr_.read_ulong (v))
          return false;

        x = static_cast<unsigned int> (v);
        return true;
      }

      inline bool icdrstream::
      operator>> (long& x)
      {
        ACE_CDR::Long v;

        if (!cdr_.read_long (v))
          return false;

        x = static_cast<long> (v);
        return true;
      }

      inline bool icdrstream::
      operator>> (unsigned long& x)
      {
        ACE_CDR::ULong v;

        if (!cdr_.read_ulong (v))
          return false;

        x = static_cast<unsigned long> (v);
        return true;
      }

#ifdef XSDE_LONGLONG
      inline bool icdrstream::
      operator>> (long long& x)
      {
        ACE_CDR::LongLong v;

        if (!cdr_.read_longlong (v))
          return false;

        x = static_cast<long long> (v);
        return true;
      }

      inline bool icdrstream::
      operator>> (unsigned long long& x)
      {
        ACE_CDR::ULongLong v;

        if (!cdr_.read_ulonglong (v))
          return false;

        x = static_cast<unsigned long long> (v);
        return true;
      }
#endif

      inline bool icdrstream::
      operator>> (as_size& x)
      {
        // Assume size is 32-bit.
        //
        ACE_CDR::ULong v;

        if (!cdr_.read_ulong (v))
          return false;

        x.s_ = static_cast<size_t> (v);
        return true;
      }

      inline bool icdrstream::
      operator>> (float& x)
      {
        ACE_CDR::Float v;

        if (!cdr_.read_float (v))
          return false;

        x = static_cast<float> (v);
        return true;
      }

      inline bool icdrstream::
      operator>> (double& x)
      {
        ACE_CDR::Double v;

        if (!cdr_.read_double (v))
          return false;

        x = static_cast<double> (v);
        return true;
      }

      inline bool
      operator>> (icdrstream&, any_type&)
      {
        return true;
      }

#endif // XSDE_EXCEPTIONS
    }
  }
}
