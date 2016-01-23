// file      : xsde/cxx/hybrid/xdr/istream.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_HYBRID_XDR_ISTREAM_HXX
#define XSDE_CXX_HYBRID_XDR_ISTREAM_HXX

#include <xsde/cxx/config.hxx>

#include <stddef.h>  // size_t

#include <rpc/types.h>
#include <rpc/xdr.h>

#ifdef XSDE_STL
#  include <string>
#endif

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
#  include <xsde/cxx/hybrid/xdr/exceptions.hxx>
#endif

namespace xsde
{
  namespace cxx
  {
    namespace hybrid
    {
      class ixdrstream
      {
      public:
        explicit
        ixdrstream (XDR& xdr);

        XDR&
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
        ixdrstream (const ixdrstream&);
        ixdrstream& operator= (const ixdrstream&);

      private:
        XDR& xdr_;
      };

#ifdef XSDE_EXCEPTIONS
      void operator>> (ixdrstream&, any_type&);
      void operator>> (ixdrstream&, qname&);
      void operator>> (ixdrstream&, string_sequence&);
      void operator>> (ixdrstream&, time_zone&);
      void operator>> (ixdrstream&, date&);
      void operator>> (ixdrstream&, date_time&);
      void operator>> (ixdrstream&, duration&);
      void operator>> (ixdrstream&, gday&);
      void operator>> (ixdrstream&, gmonth&);
      void operator>> (ixdrstream&, gmonth_day&);
      void operator>> (ixdrstream&, gyear&);
      void operator>> (ixdrstream&, gyear_month&);
      void operator>> (ixdrstream&, time&);
#else
      bool operator>> (ixdrstream&, any_type&);
      bool operator>> (ixdrstream&, qname&);
      bool operator>> (ixdrstream&, string_sequence&);
      bool operator>> (ixdrstream&, time_zone&);
      bool operator>> (ixdrstream&, date&);
      bool operator>> (ixdrstream&, date_time&);
      bool operator>> (ixdrstream&, duration&);
      bool operator>> (ixdrstream&, gday&);
      bool operator>> (ixdrstream&, gmonth&);
      bool operator>> (ixdrstream&, gmonth_day&);
      bool operator>> (ixdrstream&, gyear&);
      bool operator>> (ixdrstream&, gyear_month&);
      bool operator>> (ixdrstream&, time&);
#endif

#ifdef XSDE_EXCEPTIONS
      template <typename T>
      void operator>> (ixdrstream&, pod_sequence<T>&);

      template <typename T>
      void operator>> (ixdrstream&, fix_sequence<T>&);

      template <typename T>
      void operator>> (ixdrstream&, var_sequence<T>&);
#else
      template <typename T>
      bool operator>> (ixdrstream&, pod_sequence<T>&);

      template <typename T>
      bool operator>> (ixdrstream&, fix_sequence<T>&);

      template <typename T>
      bool operator>> (ixdrstream&, var_sequence<T>&);
#endif
    }
  }
}

#include <xsde/cxx/hybrid/xdr/istream.ixx>
#include <xsde/cxx/hybrid/xdr/istream.txx>

#endif  // XSDE_CXX_HYBRID_XDR_ISTREAM_HXX
