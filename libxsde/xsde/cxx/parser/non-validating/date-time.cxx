// file      : xsde/cxx/parser/non-validating/date-time.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdlib.h> // strtoul, strtod

#include <xsde/cxx/config.hxx>

#include <xsde/cxx/parser/non-validating/date-time.hxx>
#include <xsde/cxx/parser/non-validating/time-zone.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace non_validating
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

        date_time date_time_pimpl::
        post_date_time ()
        {
          char* s = str_.data ();
          ro_string tmp (s, str_.size ());
          ro_string::size_type n = trim_right (tmp);

          // date_time := [-]CCYY[N]*-MM-DDTHH:MM:SS[.S+][Z|(+|-)HH:MM]
          //

          int year = 0;
          unsigned short month = 0;
          unsigned short day = 0;
          unsigned short hours = 0;
          unsigned short minutes = 0;
          double seconds = 0.0;
          bool zone = false;
          short zh, zm;

          if (n >= 19)
          {
            // Find the end of the year token.
            //
            ro_string::size_type yp = tmp.find ('-', s[0] == '-' ? 5 : 4);

            if (yp != ro_string::npos && (n - yp - 1) >= 14)
            {
              // Find the end of the seconds fragment.
              //
              ro_string::size_type sp = yp + 15;
              for (; sp < n; ++sp)
              {
                char c = s[sp];

                if (c == 'Z' || c == '+' || c == '-')
                  break;
              }

              // Parse it backwards so that we can truncate and reuse
              // the string.
              //

              // zone
              //
              if (sp < n)
              {
                bits::parse_time_zone (s + sp, n - sp, zh, zm);
                zone = true;
              }

              // seconds
              //
              str_.truncate (sp);

              seconds = strtod (s + yp + 13, 0);

              // minutes
              //
              minutes = 10 * (s[yp + 10] - '0') + (s[yp + 11] - '0');

              // hours
              //
              hours = 10 * (s[yp + 7] - '0') + (s[yp + 8] - '0');

              // day
              //
              day = 10 * (s[yp + 4] - '0') + (s[yp + 5] - '0');

              // month
              //
              month = 10 * (s[yp + 1] - '0') + (s[yp + 2] - '0');

              // year
              //
              str_.truncate (yp);

              bool neg = (s[0] == '-');
              unsigned long ul = strtoul (neg ? s + 1 : s, 0, 10);

              year = neg
                ? (ul == 2147483648UL
                   ? (-2147483647 - 1)
                   : -static_cast<int> (ul))
                : static_cast<int> (ul);
            }
          }

          return zone
            ? date_time (year, month, day, hours, minutes, seconds, zh, zm)
            : date_time (year, month, day, hours, minutes, seconds);
        }
      }
    }
  }
}
