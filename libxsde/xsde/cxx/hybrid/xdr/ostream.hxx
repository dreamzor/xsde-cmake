// file      : xsde/cxx/hybrid/xdr/ostream.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_HYBRID_XDR_OSTREAM_HXX
#define XSDE_CXX_HYBRID_XDR_OSTREAM_HXX

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
      class oxdrstream
      {
      public:
        explicit
        oxdrstream (XDR& xdr);

        XDR&
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
        oxdrstream (const oxdrstream&);
        oxdrstream& operator= (const oxdrstream&);

      private:
        XDR& xdr_;
      };

#ifdef XSDE_EXCEPTIONS
      void operator<< (oxdrstream&, const any_type&);
      void operator<< (oxdrstream&, const qname&);
      void operator<< (oxdrstream&, const string_sequence&);
      void operator<< (oxdrstream&, const time_zone&);
      void operator<< (oxdrstream&, const date&);
      void operator<< (oxdrstream&, const date_time&);
      void operator<< (oxdrstream&, const duration&);
      void operator<< (oxdrstream&, const gday&);
      void operator<< (oxdrstream&, const gmonth&);
      void operator<< (oxdrstream&, const gmonth_day&);
      void operator<< (oxdrstream&, const gyear&);
      void operator<< (oxdrstream&, const gyear_month&);
      void operator<< (oxdrstream&, const time&);
#else
      bool operator<< (oxdrstream&, const any_type&);
      bool operator<< (oxdrstream&, const qname&);
      bool operator<< (oxdrstream&, const string_sequence&);
      bool operator<< (oxdrstream&, const time_zone&);
      bool operator<< (oxdrstream&, const date&);
      bool operator<< (oxdrstream&, const date_time&);
      bool operator<< (oxdrstream&, const duration&);
      bool operator<< (oxdrstream&, const gday&);
      bool operator<< (oxdrstream&, const gmonth&);
      bool operator<< (oxdrstream&, const gmonth_day&);
      bool operator<< (oxdrstream&, const gyear&);
      bool operator<< (oxdrstream&, const gyear_month&);
      bool operator<< (oxdrstream&, const time&);
#endif

#ifdef XSDE_EXCEPTIONS
      template <typename T>
      void operator<< (oxdrstream&, const pod_sequence<T>&);

      template <typename T>
      void operator<< (oxdrstream&, const fix_sequence<T>&);

      template <typename T>
      void operator<< (oxdrstream&, const var_sequence<T>&);
#else
      template <typename T>
      bool operator<< (oxdrstream&, const pod_sequence<T>&);

      template <typename T>
      bool operator<< (oxdrstream&, const fix_sequence<T>&);

      template <typename T>
      bool operator<< (oxdrstream&, const var_sequence<T>&);
#endif
    }
  }
}

#include <xsde/cxx/hybrid/xdr/ostream.ixx>
#include <xsde/cxx/hybrid/xdr/ostream.txx>

#endif  // XSDE_CXX_HYBRID_XDR_OSTREAM_HXX
