// file      : xsde/cxx/hybrid/cdr/ostream.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_HYBRID_CDR_OSTREAM_HXX
#define XSDE_CXX_HYBRID_CDR_OSTREAM_HXX

#include <xsde/cxx/config.hxx>

#include <stddef.h>  // size_t

#ifdef XSDE_STL
#  include <string>
#endif

#include <ace/CDR_Stream.h>

#include <xsde/cxx/buffer.hxx>
#include <xsde/cxx/date-time.hxx>

#ifdef XSDE_STL
#  include <xsde/cxx/qname-stl.hxx>
#  include <xsde/cxx/string-sequence-stl.hxx>
#else
#  include <xsde/cxx/qname.hxx>
#  include <xsde/cxx/string-sequence.hxx>
#endif

#include <xsde/cxx/hybrid/any-type.hxx>
#include <xsde/cxx/hybrid/sequence.hxx>

#ifdef XSDE_EXCEPTIONS
#  include <xsde/cxx/hybrid/cdr/exceptions.hxx>
#endif

namespace xsde
{
  namespace cxx
  {
    namespace hybrid
    {
      class ocdrstream
      {
      public:
        explicit
        ocdrstream (ACE_OutputCDR& cdr);

        ACE_OutputCDR&
        impl ();

      public:
        struct as_size
        {
          explicit as_size (size_t s) : s_ (s) {}
          size_t s_;
        };

      public:
#ifdef XSDE_EXCEPTIONS

        void operator<< (bool);
        void operator<< (signed char);
        void operator<< (unsigned char);
        void operator<< (short);
        void operator<< (unsigned short);
        void operator<< (int);
        void operator<< (unsigned int);
        void operator<< (long);
        void operator<< (unsigned long);

#ifdef XSDE_LONGLONG
        void operator<< (long long);
        void operator<< (unsigned long long);
#endif
        void operator<< (as_size);
        void operator<< (float);
        void operator<< (double);

#ifdef XSDE_STL
        void operator<< (const std::string&);
#else
        void operator<< (const char*);
#endif
        void operator<< (const buffer&);

#else // XSDE_EXCEPTIONS

        bool operator<< (bool);
        bool operator<< (signed char);
        bool operator<< (unsigned char);
        bool operator<< (short);
        bool operator<< (unsigned short);
        bool operator<< (int);
        bool operator<< (unsigned int);
        bool operator<< (long);
        bool operator<< (unsigned long);

#ifdef XSDE_LONGLONG
        bool operator<< (long long);
        bool operator<< (unsigned long long);
#endif
        bool operator<< (as_size);
        bool operator<< (float);
        bool operator<< (double);

#ifdef XSDE_STL
        bool operator<< (const std::string&);
#else
        bool operator<< (const char*);
#endif
        bool operator<< (const buffer&);

#endif // XSDE_EXCEPTIONS

      private:
        ocdrstream (const ocdrstream&);
        ocdrstream& operator= (const ocdrstream&);

      private:
        ACE_OutputCDR& cdr_;
      };

#ifdef XSDE_EXCEPTIONS
      void operator<< (ocdrstream&, const any_type&);
      void operator<< (ocdrstream&, const qname&);
      void operator<< (ocdrstream&, const string_sequence&);
      void operator<< (ocdrstream&, const time_zone&);
      void operator<< (ocdrstream&, const date&);
      void operator<< (ocdrstream&, const date_time&);
      void operator<< (ocdrstream&, const duration&);
      void operator<< (ocdrstream&, const gday&);
      void operator<< (ocdrstream&, const gmonth&);
      void operator<< (ocdrstream&, const gmonth_day&);
      void operator<< (ocdrstream&, const gyear&);
      void operator<< (ocdrstream&, const gyear_month&);
      void operator<< (ocdrstream&, const time&);
#else
      bool operator<< (ocdrstream&, const any_type&);
      bool operator<< (ocdrstream&, const qname&);
      bool operator<< (ocdrstream&, const string_sequence&);
      bool operator<< (ocdrstream&, const time_zone&);
      bool operator<< (ocdrstream&, const date&);
      bool operator<< (ocdrstream&, const date_time&);
      bool operator<< (ocdrstream&, const duration&);
      bool operator<< (ocdrstream&, const gday&);
      bool operator<< (ocdrstream&, const gmonth&);
      bool operator<< (ocdrstream&, const gmonth_day&);
      bool operator<< (ocdrstream&, const gyear&);
      bool operator<< (ocdrstream&, const gyear_month&);
      bool operator<< (ocdrstream&, const time&);
#endif

#ifdef XSDE_EXCEPTIONS
      template <typename T>
      void operator<< (ocdrstream&, const pod_sequence<T>&);

      template <typename T>
      void operator<< (ocdrstream&, const fix_sequence<T>&);

      template <typename T>
      void operator<< (ocdrstream&, const var_sequence<T>&);
#else
      template <typename T>
      bool operator<< (ocdrstream&, const pod_sequence<T>&);

      template <typename T>
      bool operator<< (ocdrstream&, const fix_sequence<T>&);

      template <typename T>
      bool operator<< (ocdrstream&, const var_sequence<T>&);
#endif
    }
  }
}

#include <xsde/cxx/hybrid/cdr/ostream.ixx>
#include <xsde/cxx/hybrid/cdr/ostream.txx>

#endif  // XSDE_CXX_HYBRID_CDR_OSTREAM_HXX
