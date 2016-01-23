// file      : xsde/cxx/parser/validating/gyear-month.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdlib.h> // strtoul

#include <xsde/cxx/config.hxx>
#include <xsde/cxx/errno.hxx>

#include <xsde/cxx/parser/validating/gyear-month.hxx>
#include <xsde/cxx/parser/validating/time-zone.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
      {
        void gyear_month_pimpl::
        _pre ()
        {
#ifdef XSDE_EXCEPTIONS
          str_.assign ("", 0);
#else
          if (str_.assign ("", 0))
            _sys_error (sys_error::no_memory);
#endif
        }

        void gyear_month_pimpl::
        _characters (const ro_string& s)
        {
          if (str_.size () == 0)
          {
            ro_string tmp (s.data (), s.size ());

            if (trim_left (tmp) != 0)
            {
#ifdef XSDE_EXCEPTIONS
              str_.append (tmp.data (), tmp.size ());
#else
              if (str_.append (tmp.data (), tmp.size ()))
                _sys_error (sys_error::no_memory);
#endif
            }
          }
          else
          {
#ifdef XSDE_EXCEPTIONS
            str_.append (s.data (), s.size ());
#else
            if (str_.append (s.data (), s.size ()))
              _sys_error (sys_error::no_memory);
#endif
          }
        }

        void gyear_month_pimpl::
        _post ()
        {
          char* s = str_.data ();
          ro_string tmp (s, str_.size ());
          ro_string::size_type n = trim_right (tmp);

          // gyear_month := [-]CCYY[N]*-MM[Z|(+|-)HH:MM]
          //

          if (n < 7 || (s[0] == '-' && n < 8))
          {
            _schema_error (schema_error::invalid_gyear_month_value);
            return;
          }

          // Find the end of the year token.
          //
          ro_string::size_type pos = tmp.find ('-', s[0] == '-' ? 5 : 4);

          if (pos == ro_string::npos || (n - pos - 1) < 2)
          {
            _schema_error (schema_error::invalid_gyear_month_value);
            return;
          }

          // Parse the month value and time zone first so that we can
          // truncate and reuse the string.
          //

          // month
          //
          char d1 = s[pos + 1];
          char d2 = s[pos + 2];

          if (d1 < '0' || d1 > '9' || d2 < '0' || d2 > '9')
          {
            _schema_error (schema_error::invalid_gyear_month_value);
            return;
          }

          month_ = 10 * (d1 - '0') + (d2 - '0');

          if (month_ < 1 || month_ > 12)
          {
            _schema_error (schema_error::invalid_gyear_month_value);
            return;
          }

          // zone
          //
          if ((pos + 3) < n)
          {
            if (!bits::parse_time_zone (s + pos + 3, n - pos - 3, zh_, zm_))
            {
              _schema_error (schema_error::invalid_gyear_month_value);
              return;
            }

            z_ = true;
          }
          else
            z_ = false;

          // year
          //
          str_.truncate (pos);

          char* p;
          set_errno (0);
          bool neg = (s[0] == '-');
          unsigned long ul = strtoul (neg ? s + 1 : s, &p, 10);

          if (*p != '\0' ||
              get_errno () != 0 ||
              (neg && ul > 2147483648UL) ||
              (!neg && ul > 2147483647UL) ||
              ul == 0)
          {
            _schema_error (schema_error::invalid_gyear_month_value);
            return;
          }

          year_ = neg
            ? (ul == 2147483648UL
               ? (-2147483647 - 1)
               : -static_cast<int> (ul))
            : static_cast<int> (ul);
        }

        gyear_month gyear_month_pimpl::
        post_gyear_month ()
        {
          return z_
            ? gyear_month (year_, month_, zh_, zm_)
            : gyear_month (year_, month_);
        }
      }
    }
  }
}
