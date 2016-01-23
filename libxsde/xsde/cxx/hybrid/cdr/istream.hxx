// file      : xsde/cxx/hybrid/cdr/istream.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_HYBRID_CDR_ISTREAM_HXX
#define XSDE_CXX_HYBRID_CDR_ISTREAM_HXX

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
      class icdrstream
      {
      public:
        explicit
        icdrstream (ACE_InputCDR& cdr);

        ACE_InputCDR&
        impl ();

      public:
        struct as_size
        {
          explicit as_size (size_t& s) : s_ (s) {}
          size_t& s_;
        };

      public:
#ifdef XSDE_EXCEPTIONS

        void operator>> (bool&);
        void operator>> (signed char&);
        void operator>> (unsigned char&);
        void operator>> (short&);
        void operator>> (unsigned short&);
        void operator>> (int&);
        void operator>> (unsigned int&);
        void operator>> (long&);
        void operator>> (unsigned long&);

#ifdef XSDE_LONGLONG
        void operator>> (long long&);
        void operator>> (unsigned long long&);
#endif
        void operator>> (as_size&);
        void operator>> (float&);
        void operator>> (double&);

#ifdef XSDE_STL
        void operator>> (std::string&);
#else
        void operator>> (char*&);
#endif
        void operator>> (buffer&);

#else // XSDE_EXCEPTIONS

        bool operator>> (bool&);
        bool operator>> (signed char&);
        bool operator>> (unsigned char&);
        bool operator>> (short&);
        bool operator>> (unsigned short&);
        bool operator>> (int&);
        bool operator>> (unsigned int&);
        bool operator>> (long&);
        bool operator>> (unsigned long&);

#ifdef XSDE_LONGLONG
        bool operator>> (long long&);
        bool operator>> (unsigned long long&);
#endif
        bool operator>> (as_size&);
        bool operator>> (float&);
        bool operator>> (double&);

#ifdef XSDE_STL
        bool operator>> (std::string&);
#else
        bool operator>> (char*&);
#endif
        bool operator>> (buffer&);

#endif // XSDE_EXCEPTIONS

      private:
        icdrstream (const icdrstream&);
        icdrstream& operator= (const icdrstream&);

      private:
        ACE_InputCDR& cdr_;
      };

#ifdef XSDE_EXCEPTIONS
      void operator>> (icdrstream&, any_type&);
      void operator>> (icdrstream&, qname&);
      void operator>> (icdrstream&, string_sequence&);
      void operator>> (icdrstream&, time_zone&);
      void operator>> (icdrstream&, date&);
      void operator>> (icdrstream&, date_time&);
      void operator>> (icdrstream&, duration&);
      void operator>> (icdrstream&, gday&);
      void operator>> (icdrstream&, gmonth&);
      void operator>> (icdrstream&, gmonth_day&);
      void operator>> (icdrstream&, gyear&);
      void operator>> (icdrstream&, gyear_month&);
      void operator>> (icdrstream&, time&);
#else
      bool operator>> (icdrstream&, any_type&);
      bool operator>> (icdrstream&, qname&);
      bool operator>> (icdrstream&, string_sequence&);
      bool operator>> (icdrstream&, time_zone&);
      bool operator>> (icdrstream&, date&);
      bool operator>> (icdrstream&, date_time&);
      bool operator>> (icdrstream&, duration&);
      bool operator>> (icdrstream&, gday&);
      bool operator>> (icdrstream&, gmonth&);
      bool operator>> (icdrstream&, gmonth_day&);
      bool operator>> (icdrstream&, gyear&);
      bool operator>> (icdrstream&, gyear_month&);
      bool operator>> (icdrstream&, time&);
#endif

#ifdef XSDE_EXCEPTIONS
      template <typename T>
      void operator>> (icdrstream&, pod_sequence<T>&);

      template <typename T>
      void operator>> (icdrstream&, fix_sequence<T>&);

      template <typename T>
      void operator>> (icdrstream&, var_sequence<T>&);
#else
      template <typename T>
      bool operator>> (icdrstream&, pod_sequence<T>&);

      template <typename T>
      bool operator>> (icdrstream&, fix_sequence<T>&);

      template <typename T>
      bool operator>> (icdrstream&, var_sequence<T>&);
#endif
    }
  }
}

#include <xsde/cxx/hybrid/cdr/istream.ixx>
#include <xsde/cxx/hybrid/cdr/istream.txx>

#endif  // XSDE_CXX_HYBRID_CDR_ISTREAM_HXX
