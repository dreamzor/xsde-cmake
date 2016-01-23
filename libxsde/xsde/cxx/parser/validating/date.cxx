// file      : xsde/cxx/parser/validating/date.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdlib.h> // strtoul

#include <xsde/cxx/config.hxx>
#include <xsde/cxx/errno.hxx>

#include <xsde/cxx/parser/validating/date.hxx>
#include <xsde/cxx/parser/validating/time-zone.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
      {
        void date_pimpl::
        _pre ()
        {
#ifdef XSDE_EXCEPTIONS
          str_.assign ("", 0);
#else
          if (str_.assign ("", 0))
            _sys_error (sys_error::no_memory);
#endif
        }

        void date_pimpl::
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

        void date_pimpl::
        _post ()
        {
          char* s = str_.data ();
          ro_string tmp (s, str_.size ());
          ro_string::size_type n = trim_right (tmp);

          // date := [-]CCYY[N]*-MM-DD[Z|(+|-)HH:MM]
          //

          if (n < 10 || (s[0] == '-' && n < 11))
          {
            _schema_error (schema_error::invalid_date_value);
            return;
          }

          // Find the end of the year token.
          //
          ro_string::size_type pos = tmp.find ('-', s[0] == '-' ? 5 : 4);

          if (pos == ro_string::npos ||
              (n - pos - 1) < 5 ||
              s[pos + 3] != '-')
          {
            _schema_error (schema_error::invalid_date_value);
            return;
          }

          // Parse the month, day values and time zone first so that we
          // can truncate and reuse the string.
          //

          // month
          //
          char d1 = s[pos + 1];
          char d2 = s[pos + 2];

          if (d1 < '0' || d1 > '9' || d2 < '0' || d2 > '9')
          {
            _schema_error (schema_error::invalid_date_value);
            return;
          }

          month_ = 10 * (d1 - '0') + (d2 - '0');

          if (month_ < 1 || month_ > 12)
          {
            _schema_error (schema_error::invalid_date_value);
            return;
          }

          // day
          //
          d1 = s[pos + 4];
          d2 = s[pos + 5];

          if (d1 < '0' || d1 > '9' || d2 < '0' || d2 > '9')
          {
            _schema_error (schema_error::invalid_date_value);
            return;
          }

          day_ = 10 * (d1 - '0') + (d2 - '0');

          if (day_ < 1 || day_ > 31)
          {
            _schema_error (schema_error::invalid_date_value);
            return;
          }

          // zone
          //
          if ((pos + 6) < n)
          {
            if (!bits::parse_time_zone (s + pos + 6, n - pos - 6, zh_, zm_))
            {
              _schema_error (schema_error::invalid_date_value);
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
            _schema_error (schema_error::invalid_date_value);
            return;
          }

          year_ = neg
            ? (ul == 2147483648UL
               ? (-2147483647 - 1)
               : -static_cast<int> (ul))
            : static_cast<int> (ul);
        }

        date date_pimpl::
        post_date ()
        {
          return z_
            ? date (year_, month_, day_, zh_, zm_)
            : date (year_, month_, day_);
        }
      }
    }
  }
}
