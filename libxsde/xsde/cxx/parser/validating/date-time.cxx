// file      : xsde/cxx/parser/validating/date-time.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdlib.h> // strtoul, strtod

#include <xsde/cxx/config.hxx>
#include <xsde/cxx/errno.hxx>

#include <xsde/cxx/parser/validating/date-time.hxx>
#include <xsde/cxx/parser/validating/time-zone.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
      {
        void date_time_pimpl::
        _pre ()
        {
#ifdef XSDE_EXCEPTIONS
          str_.assign ("", 0);
#else
          if (str_.assign ("", 0))
            _sys_error (sys_error::no_memory);
#endif
        }

        void date_time_pimpl::
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

        void date_time_pimpl::
        _post ()
        {
          char* s = str_.data ();
          ro_string tmp (s, str_.size ());
          ro_string::size_type n = trim_right (tmp);

          // date_time := [-]CCYY[N]*-MM-DDTHH:MM:SS[.S+][Z|(+|-)HH:MM]
          //

          if (n < 19 || (s[0] == '-' && n < 20))
          {
            _schema_error (schema_error::invalid_date_time_value);
            return;
          }

          // Find the end of the year token.
          //
          ro_string::size_type yp = tmp.find ('-', s[0] == '-' ? 5 : 4);

          if (yp == ro_string::npos || (n - yp - 1) < 14
              || s[yp + 3] != '-' || s[yp + 6] != 'T'
              || s[yp + 9] != ':' || s[yp + 12] != ':')
          {
            _schema_error (schema_error::invalid_date_time_value);
            return;
          }

          // Find the end of the seconds fragment.
          //
          ro_string::size_type sp = yp + 15;
          for (; sp < n; ++sp)
          {
            char c = s[sp];

            if (c == 'Z' || c == '+' || c == '-')
              break;
          }

          // At least one digit should follow the fraction point.
          //
          if ((sp - yp - 13) == 3)
          {
            _schema_error (schema_error::invalid_date_time_value);
            return;
          }

          // Parse it backwards so that we can truncate and reuse
          // the string.
          //

          // zone
          //
          if (sp < n)
          {
            if (!bits::parse_time_zone (s + sp, n - sp, zh_, zm_))
            {
              _schema_error (schema_error::invalid_date_time_value);
              return;
            }

            z_ = true;
          }
          else
            z_ = false;

          // seconds
          //
          str_.truncate (sp);

          char* p;
          set_errno (0);
          seconds_ = strtod (s + yp + 13, &p);

          if (*p != '\0' || get_errno () != 0 || seconds_ >= 60.0)
          {
            _schema_error (schema_error::invalid_date_time_value);
            return;
          }

          // minutes
          //
          char d1 = s[yp + 10];
          char d2 = s[yp + 11];

          if (d1 < '0' || d1 > '9' || d2 < '0' || d2 > '9')
          {
            _schema_error (schema_error::invalid_date_time_value);
            return;
          }

          minutes_ = 10 * (d1 - '0') + (d2 - '0');

          if (minutes_ > 59)
          {
            _schema_error (schema_error::invalid_date_time_value);
            return;
          }

          // hours
          //
          d1 = s[yp + 7];
          d2 = s[yp + 8];

          if (d1 < '0' || d1 > '9' || d2 < '0' || d2 > '9')
          {
            _schema_error (schema_error::invalid_date_time_value);
            return;
          }

          hours_ = 10 * (d1 - '0') + (d2 - '0');

          if (hours_ > 24)
          {
            _schema_error (schema_error::invalid_date_time_value);
            return;
          }

          if (hours_ == 24 && (minutes_ != 0 || seconds_ != 0.0))
          {
            _schema_error (schema_error::invalid_date_time_value);
            return;
          }

          // day
          //
          d1 = s[yp + 4];
          d2 = s[yp + 5];

          if (d1 < '0' || d1 > '9' || d2 < '0' || d2 > '9')
          {
            _schema_error (schema_error::invalid_date_time_value);
            return;
          }

          day_ = 10 * (d1 - '0') + (d2 - '0');

          if (day_ < 1 || day_ > 31)
          {
            _schema_error (schema_error::invalid_date_time_value);
            return;
          }

          // month
          //
          d1 = s[yp + 1];
          d2 = s[yp + 2];

          if (d1 < '0' || d1 > '9' || d2 < '0' || d2 > '9')
          {
            _schema_error (schema_error::invalid_date_time_value);
            return;
          }

          month_ = 10 * (d1 - '0') + (d2 - '0');

          if (month_ < 1 || month_ > 12)
          {
            _schema_error (schema_error::invalid_date_time_value);
            return;
          }

          // year
          //
          str_.truncate (yp);

          set_errno (0);
          bool neg = (s[0] == '-');
          unsigned long ul = strtoul (neg ? s + 1 : s, &p, 10);

          if (*p != '\0' ||
              get_errno () != 0 ||
              (neg && ul > 2147483648UL) ||
              (!neg && ul > 2147483647UL) ||
              ul == 0)
          {
            _schema_error (schema_error::invalid_date_time_value);
            return;
          }

          year_ = neg
            ? (ul == 2147483648UL
               ? (-2147483647 - 1)
               : -static_cast<int> (ul))
            : static_cast<int> (ul);
        }

        date_time date_time_pimpl::
        post_date_time ()
        {
          return z_
            ? date_time (year_, month_, day_, hours_,
                         minutes_, seconds_, zh_, zm_)
            : date_time (year_, month_, day_, hours_, minutes_, seconds_);
        }
      }
    }
  }
}
