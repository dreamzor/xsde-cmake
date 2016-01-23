// file      : xsde/cxx/hybrid/base.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_HYBRID_BASE_HXX
#define XSDE_CXX_HYBRID_BASE_HXX

#include <xsde/cxx/config.hxx>

#ifndef XSDE_STL
#  include <string.h> // strcmp
#  include <xsde/cxx/strdupx.hxx>
#endif

#ifdef XSDE_CUSTOM_ALLOCATOR
#  include <xsde/cxx/allocator.hxx>
#endif

namespace xsde
{
  namespace cxx
  {
    namespace hybrid
    {
      // boolean
      //
      struct boolean_base
      {
        bool base_value () const {return x_;}
        bool& base_value () {return x_;}
        void base_value (bool x) {x_ = x;}

        operator const bool& () const {return x_;}
        operator bool& () {return x_;}

        boolean_base& operator= (bool x) {x_ = x; return *this;}

      protected:
        bool x_;
      };

      inline bool
      operator== (const boolean_base& x, const boolean_base& y)
      {
        return x.base_value () == y.base_value ();
      }

      inline bool
      operator!= (const boolean_base& x, const boolean_base& y)
      {
        return !(x == y);
      }

      // byte
      //
      struct byte_base
      {
        signed char base_value () const {return x_;}
        signed char& base_value () {return x_;}
        void base_value (signed char x) {x_ = x;}

        operator const signed char& () const {return x_;}
        operator signed char& () {return x_;}

        byte_base& operator= (signed char x) {x_ = x; return *this;}

      protected:
        signed char x_;
      };

      inline bool
      operator== (const byte_base& x, const byte_base& y)
      {
        return x.base_value () == y.base_value ();
      }

      inline bool
      operator!= (const byte_base& x, const byte_base& y)
      {
        return !(x == y);
      }

      // unsigned_byte
      //
      struct unsigned_byte_base
      {
        unsigned char base_value () const {return x_;}
        unsigned char& base_value () {return x_;}
        void base_value (unsigned char x) {x_ = x;}

        operator const unsigned char& () const {return x_;}
        operator unsigned char& () {return x_;}

        unsigned_byte_base&
        operator= (unsigned char x) {x_ = x; return *this;}

      protected:
        unsigned char x_;
      };

      inline bool
      operator== (const unsigned_byte_base& x, const unsigned_byte_base& y)
      {
        return x.base_value () == y.base_value ();
      }

      inline bool
      operator!= (const unsigned_byte_base& x, const unsigned_byte_base& y)
      {
        return !(x == y);
      }

      // short
      //
      struct short_base
      {
        short base_value () const {return x_;}
        short& base_value () {return x_;}
        void base_value (short x) {x_ = x;}

        operator const short& () const {return x_;}
        operator short& () {return x_;}

        short_base& operator= (short x) {x_ = x; return *this;}

      protected:
        short x_;
      };

      inline bool
      operator== (const short_base& x, const short_base& y)
      {
        return x.base_value () == y.base_value ();
      }

      inline bool
      operator!= (const short_base& x, const short_base& y)
      {
        return !(x == y);
      }

      // unsigned_short
      //
      struct unsigned_short_base
      {
        unsigned short base_value () const {return x_;}
        unsigned short& base_value () {return x_;}
        void base_value (unsigned short x) {x_ = x;}

        operator const unsigned short& () const {return x_;}
        operator unsigned short& () {return x_;}

        unsigned_short_base&
        operator= (unsigned short x) {x_ = x; return *this;}

      protected:
        unsigned short x_;
      };

      inline bool
      operator== (const unsigned_short_base& x, const unsigned_short_base& y)
      {
        return x.base_value () == y.base_value ();
      }

      inline bool
      operator!= (const unsigned_short_base& x, const unsigned_short_base& y)
      {
        return !(x == y);
      }

      // int
      //
      struct int_base
      {
        int base_value () const {return x_;}
        int& base_value () {return x_;}
        void base_value (int x) {x_ = x;}

        operator const int& () const {return x_;}
        operator int& () {return x_;}

        int_base& operator= (int x) {x_ = x; return *this;}

      protected:
        int x_;
      };

      inline bool
      operator== (const int_base& x, const int_base& y)
      {
        return x.base_value () == y.base_value ();
      }

      inline bool
      operator!= (const int_base& x, const int_base& y)
      {
        return !(x == y);
      }

      // unsigned_int
      //
      struct unsigned_int_base
      {
        unsigned int base_value () const {return x_;}
        unsigned int& base_value () {return x_;}
        void base_value (unsigned int x) {x_ = x;}

        operator const unsigned int& () const {return x_;}
        operator unsigned int& () {return x_;}

        unsigned_int_base& operator= (unsigned int x) {x_ = x; return *this;}

      protected:
        unsigned int x_;
      };

      inline bool
      operator== (const unsigned_int_base& x, const unsigned_int_base& y)
      {
        return x.base_value () == y.base_value ();
      }

      inline bool
      operator!= (const unsigned_int_base& x, const unsigned_int_base& y)
      {
        return !(x == y);
      }

      // long
      //
#ifdef XSDE_LONGLONG
      struct long_base
      {
        long long base_value () const {return x_;}
        long long& base_value () {return x_;}
        void base_value (long long x) {x_ = x;}

        operator const long long& () const {return x_;}
        operator long long& () {return x_;}

        long_base& operator= (long long x) {x_ = x; return *this;}

      protected:
        long long x_;
      };
#else
      struct long_base
      {
        long base_value () const {return x_;}
        long& base_value () {return x_;}
        void base_value (long x) {x_ = x;}

        operator const long& () const {return x_;}
        operator long& () {return x_;}

        long_base& operator= (long x) {x_ = x; return *this;}

      protected:
        long x_;
      };
#endif

      inline bool
      operator== (const long_base& x, const long_base& y)
      {
        return x.base_value () == y.base_value ();
      }

      inline bool
      operator!= (const long_base& x, const long_base& y)
      {
        return !(x == y);
      }


      // unsigned_long
      //
#ifdef XSDE_LONGLONG
      struct unsigned_long_base
      {
        unsigned long long base_value () const {return x_;}
        unsigned long long& base_value () {return x_;}
        void base_value (unsigned long long x) {x_ = x;}

        operator const unsigned long long& () const {return x_;}
        operator unsigned long long& () {return x_;}

        unsigned_long_base&
        operator= (unsigned long long x) {x_ = x; return *this;}

      protected:
        unsigned long long x_;
      };
#else
      struct unsigned_long_base
      {
        unsigned long base_value () const {return x_;}
        unsigned long& base_value () {return x_;}
        void base_value (unsigned long x) {x_ = x;}

        operator const unsigned long& () const {return x_;}
        operator unsigned long& () {return x_;}

        unsigned_long_base&
        operator= (unsigned long x) {x_ = x; return *this;}

      protected:
        unsigned long x_;
      };
#endif

      inline bool
      operator== (const unsigned_long_base& x, const unsigned_long_base& y)
      {
        return x.base_value () == y.base_value ();
      }

      inline bool
      operator!= (const unsigned_long_base& x, const unsigned_long_base& y)
      {
        return !(x == y);
      }

      // integer
      //
      struct integer_base
      {
        long base_value () const {return x_;}
        long& base_value () {return x_;}
        void base_value (long x) {x_ = x;}

        operator const long& () const {return x_;}
        operator long& () {return x_;}

        integer_base& operator= (long x) {x_ = x; return *this;}

      protected:
        long x_;
      };

      inline bool
      operator== (const integer_base& x, const integer_base& y)
      {
        return x.base_value () == y.base_value ();
      }

      inline bool
      operator!= (const integer_base& x, const integer_base& y)
      {
        return !(x == y);
      }

      // negative_integer
      //
      struct negative_integer_base
      {
        long base_value () const {return x_;}
        long& base_value () {return x_;}
        void base_value (long x) {x_ = x;}

        operator const long& () const {return x_;}
        operator long& () {return x_;}

        negative_integer_base& operator= (long x) {x_ = x; return *this;}

      protected:
        long x_;
      };

      inline bool
      operator== (const negative_integer_base& x,
                  const negative_integer_base& y)
      {
        return x.base_value () == y.base_value ();
      }

      inline bool
      operator!= (const negative_integer_base& x,
                  const negative_integer_base& y)
      {
        return !(x == y);
      }

      // non_positive_integer
      //
      struct non_positive_integer_base
      {
        long base_value () const {return x_;}
        long& base_value () {return x_;}
        void base_value (long x) {x_ = x;}

        operator const long& () const {return x_;}
        operator long& () {return x_;}

        non_positive_integer_base& operator= (long x) {x_ = x; return *this;}

      protected:
        long x_;
      };

      inline bool
      operator== (const non_positive_integer_base& x,
                  const non_positive_integer_base& y)
      {
        return x.base_value () == y.base_value ();
      }

      inline bool
      operator!= (const non_positive_integer_base& x,
                  const non_positive_integer_base& y)
      {
        return !(x == y);
      }

      // positive_integer
      //
      struct positive_integer_base
      {
        unsigned long base_value () const {return x_;}
        unsigned long& base_value () {return x_;}
        void base_value (unsigned long x) {x_ = x;}

        operator const unsigned long& () const {return x_;}
        operator unsigned long& () {return x_;}

        positive_integer_base&
        operator= (unsigned long x) {x_ = x; return *this;}

      protected:
        unsigned long x_;
      };

      inline bool
      operator== (const positive_integer_base& x,
                  const positive_integer_base& y)
      {
        return x.base_value () == y.base_value ();
      }

      inline bool
      operator!= (const positive_integer_base& x,
                  const positive_integer_base& y)
      {
        return !(x == y);
      }

      // non_negative_integer
      //
      struct non_negative_integer_base
      {
        unsigned long base_value () const {return x_;}
        unsigned long& base_value () {return x_;}
        void base_value (unsigned long x) {x_ = x;}

        operator const unsigned long& () const {return x_;}
        operator unsigned long& () {return x_;}

        non_negative_integer_base&
        operator= (unsigned long x) {x_ = x; return *this;}

      protected:
        unsigned long x_;
      };

      inline bool
      operator== (const non_negative_integer_base& x,
                  const non_negative_integer_base& y)
      {
        return x.base_value () == y.base_value ();
      }

      inline bool
      operator!= (const non_negative_integer_base& x,
                  const non_negative_integer_base& y)
      {
        return !(x == y);
      }

      // float
      //
      struct float_base
      {
        float base_value () const {return x_;}
        float& base_value () {return x_;}
        void base_value (float x) {x_ = x;}

        operator const float& () const {return x_;}
        operator float& () {return x_;}

        float_base& operator= (float x) {x_ = x; return *this;}

      protected:
        float x_;
      };

      inline bool
      operator== (const float_base& x, const float_base& y)
      {
        return x.base_value () == y.base_value ();
      }

      inline bool
      operator!= (const float_base& x, const float_base& y)
      {
        return !(x == y);
      }

      // double
      //
      struct double_base
      {
        double base_value () const {return x_;}
        double& base_value () {return x_;}
        void base_value (double x) {x_ = x;}

        operator const double& () const {return x_;}
        operator double& () {return x_;}

        double_base& operator= (double x) {x_ = x; return *this;}

      protected:
        double x_;
      };

      inline bool
      operator== (const double_base& x, const double_base& y)
      {
        return x.base_value () == y.base_value ();
      }

      inline bool
      operator!= (const double_base& x, const double_base& y)
      {
        return !(x == y);
      }

      // decimal
      //
      struct decimal_base
      {
        double base_value () const {return x_;}
        double& base_value () {return x_;}
        void base_value (double x) {x_ = x;}

        operator const double& () const {return x_;}
        operator double& () {return x_;}

        decimal_base& operator= (double x) {x_ = x; return *this;}

      protected:
        double x_;
      };

      inline bool
      operator== (const decimal_base& x, const decimal_base& y)
      {
        return x.base_value () == y.base_value ();
      }

      inline bool
      operator!= (const decimal_base& x, const decimal_base& y)
      {
        return !(x == y);
      }

#ifndef XSDE_STL
      // string
      //
      struct string_base
      {
        string_base () : x_ (0) {}
        ~string_base ()
        {
#ifndef XSDE_CUSTOM_ALLOCATOR
          delete[] x_;
#else
          cxx::free (x_);
#endif
        }

        const char* base_value () const {return x_;}
        char* base_value () {return x_;}

        void base_value (char* x)
        {
#ifndef XSDE_CUSTOM_ALLOCATOR
          delete[] x_;
#else
          cxx::free (x_);
#endif
          x_ = x;
        }

        char* base_value_detach () {char* r = x_; x_ = 0; return r;}

        operator const char* () const {return x_;}
        operator char* () {return x_;}

        string_base& operator= (char* x) {base_value (x); return *this;}

#ifndef XSDE_EXCEPTIONS
        bool
#else
        void
#endif
        _copy (string_base& c) const
        {
          char* x = strdupx (x_);

#ifndef XSDE_EXCEPTIONS
          if (x == 0)
            return false;
#endif
          c.base_value (x);

#ifndef XSDE_EXCEPTIONS
          return true;
#endif
        }

      protected:
        char* x_;
      };

      inline bool
      operator== (const string_base& x, const string_base& y)
      {
        return strcmp (x.base_value (), y.base_value ()) == 0;
      }

      inline bool
      operator!= (const string_base& x, const string_base& y)
      {
        return !(x == y);
      }
#endif
    }
  }
}

#endif  // XSDE_CXX_HYBRID_BASE_HXX
