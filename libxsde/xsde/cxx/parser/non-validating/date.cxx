// file      : xsde/cxx/parser/non-validating/date.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdlib.h> // strtoul

#include <xsde/cxx/config.hxx>

#include <xsde/cxx/parser/non-validating/date.hxx>
#include <xsde/cxx/parser/non-validating/time-zone.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace non_validating
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

        date date_pimpl::
        post_date ()
        {
          char* s = str_.data ();
          ro_string tmp (s, str_.size ());
          ro_string::size_type n = trim_right (tmp);

          // date := [-]CCYY[N]*-MM-DD[Z|(+|-)HH:MM]
          //

          int year = 0;
          unsigned short month = 0;
          unsigned short day = 0;
          bool zone = false;
          short zh, zm;

          if (n >= 10)
          {
            // Find the end of the year token.
            //
            ro_string::size_type pos = tmp.find ('-', s[0] == '-' ? 5 : 4);

            if (pos != ro_string::npos && (n - pos - 1) >= 5)
            {
              // Parse the month, day values and time zone first so that we
              // can truncate and reuse the string.
              //

              // month
              //
              month = 10 * (s[pos + 1] - '0') + (s[pos + 2] - '0');

              // day
              //
              day = 10 * (s[pos + 4] - '0') + (s[pos + 5] - '0');

              // zone
              //
              if ((pos + 6) < n)
              {
                bits::parse_time_zone (s + pos + 6, n - pos - 6, zh, zm);
                zone = true;
              }

              // year
              //
              str_.truncate (pos);

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
            ? date (year, month, day, zh, zm)
            : date (year, month, day);
        }
      }
    }
  }
}
