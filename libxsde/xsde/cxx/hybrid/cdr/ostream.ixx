// file      : xsde/cxx/hybrid/cdr/ostream.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsde
{
  namespace cxx
  {
    namespace hybrid
    {
      inline ocdrstream::
      ocdrstream (ACE_OutputCDR& cdr)
          : cdr_ (cdr)
      {
      }

      inline ACE_OutputCDR& ocdrstream::
      impl ()
      {
        return cdr_;
      }

#ifdef XSDE_EXCEPTIONS

      inline void ocdrstream::
      operator<< (bool x)
      {
        if (!cdr_.write_boolean (static_cast<ACE_CDR::Boolean> (x)))
          throw cdr_exception ();
      }

      inline void ocdrstream::
      operator<< (signed char x)
      {
        if (!cdr_.write_octet (static_cast<ACE_CDR::Octet> (x)))
          throw cdr_exception ();
      }


      inline void ocdrstream::
      operator<< (unsigned char x)
      {
        if (!cdr_.write_octet (static_cast<ACE_CDR::Octet> (x)))
          throw cdr_exception ();
      }

      inline void ocdrstream::
      operator<< (short x)
      {
        if (!cdr_.write_short (static_cast<ACE_CDR::Short> (x)))
          throw cdr_exception ();
      }

      inline void ocdrstream::
      operator<< (unsigned short x)
      {
        if (!cdr_.write_ushort (static_cast<ACE_CDR::UShort> (x)))
          throw cdr_exception ();
      }

      inline void ocdrstream::
      operator<< (int x)
      {
        if (!cdr_.write_long (static_cast<ACE_CDR::Long> (x)))
          throw cdr_exception ();
      }

      inline void ocdrstream::
      operator<< (unsigned int x)
      {
        if (!cdr_.write_ulong (static_cast<ACE_CDR::ULong> (x)))
          throw cdr_exception ();
      }

      inline void ocdrstream::
      operator<< (long x)
      {
        if (!cdr_.write_long (static_cast<ACE_CDR::Long> (x)))
          throw cdr_exception ();
      }

      inline void ocdrstream::
      operator<< (unsigned long x)
      {
        if (!cdr_.write_ulong (static_cast<ACE_CDR::ULong> (x)))
          throw cdr_exception ();
      }

#ifdef XSDE_LONGLONG
      inline void ocdrstream::
      operator<< (long long x)
      {
        if (!cdr_.write_longlong (static_cast<ACE_CDR::LongLong> (x)))
          throw cdr_exception ();
      }

      inline void ocdrstream::
      operator<< (unsigned long long x)
      {
        if (!cdr_.write_ulonglong (static_cast<ACE_CDR::ULongLong> (x)))
          throw cdr_exception ();
      }
#endif

      inline void ocdrstream::
      operator<< (as_size x)
      {
        // Assume size is 32-bit.
        //
        if (!cdr_.write_ulong (static_cast<ACE_CDR::ULong> (x.s_)))
          throw cdr_exception ();
      }

      inline void ocdrstream::
      operator<< (float x)
      {
        if (!cdr_.write_float (static_cast<ACE_CDR::Float> (x)))
          throw cdr_exception ();
      }

      inline void ocdrstream::
      operator<< (double x)
      {
        if (!cdr_.write_double (static_cast<ACE_CDR::Double> (x)))
          throw cdr_exception ();
      }

      inline void
      operator<< (ocdrstream&, const any_type&)
      {
      }

#else // XSDE_EXCEPTIONS

      inline bool ocdrstream::
      operator<< (bool x)
      {
        return cdr_.write_boolean (static_cast<ACE_CDR::Boolean> (x));
      }

      inline bool ocdrstream::
      operator<< (signed char x)
      {
        return cdr_.write_octet (static_cast<ACE_CDR::Octet> (x));
      }


      inline bool ocdrstream::
      operator<< (unsigned char x)
      {
        return cdr_.write_octet (static_cast<ACE_CDR::Octet> (x));
      }

      inline bool ocdrstream::
      operator<< (short x)
      {
        return cdr_.write_short (static_cast<ACE_CDR::Short> (x));
      }

      inline bool ocdrstream::
      operator<< (unsigned short x)
      {
        return cdr_.write_ushort (static_cast<ACE_CDR::UShort> (x));
      }

      inline bool ocdrstream::
      operator<< (int x)
      {
        return cdr_.write_long (static_cast<ACE_CDR::Long> (x));
      }

      inline bool ocdrstream::
      operator<< (unsigned int x)
      {
        return cdr_.write_ulong (static_cast<ACE_CDR::ULong> (x));
      }

      inline bool ocdrstream::
      operator<< (long x)
      {
        return cdr_.write_long (static_cast<ACE_CDR::Long> (x));
      }

      inline bool ocdrstream::
      operator<< (unsigned long x)
      {
        return cdr_.write_ulong (static_cast<ACE_CDR::ULong> (x));
      }

#ifdef XSDE_LONGLONG
      inline bool ocdrstream::
      operator<< (long long x)
      {
        return cdr_.write_longlong (static_cast<ACE_CDR::LongLong> (x));
      }

      inline bool ocdrstream::
      operator<< (unsigned long long x)
      {
        return cdr_.write_ulonglong (static_cast<ACE_CDR::ULongLong> (x));
      }
#endif

      inline bool ocdrstream::
      operator<< (as_size x)
      {
        // Assume size is 32-bit.
        //
        return cdr_.write_ulong (static_cast<ACE_CDR::ULong> (x.s_));
      }

      inline bool ocdrstream::
      operator<< (float x)
      {
        return cdr_.write_float (static_cast<ACE_CDR::Float> (x));
      }

      inline bool ocdrstream::
      operator<< (double x)
      {
        return cdr_.write_double (static_cast<ACE_CDR::Double> (x));
      }

      inline bool
      operator<< (ocdrstream&, const any_type&)
      {
        return true;
      }

#endif // XSDE_EXCEPTIONS
    }
  }
}
