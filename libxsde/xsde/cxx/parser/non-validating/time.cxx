// file      : xsde/cxx/parser/non-validating/time.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdlib.h> // strtod

#include <xsde/cxx/config.hxx>

#include <xsde/cxx/parser/non-validating/time.hxx>
#include <xsde/cxx/parser/non-validating/time-zone.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace non_validating
      {
        void time_pimpl::
        _pre ()
        {
#ifdef XSDE_EXCEPTIONS
          str_.assign ("", 0);
#else
          if (str_.assign ("", 0))
            _sys_error (sys_error::no_memory);
#endif
        }

        void time_pimpl::
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

        time time_pimpl::
        post_time ()
        {
          char* s = str_.data ();
          ro_string tmp (s, str_.size ());
          ro_string::size_type n = trim_right (tmp);

          // time := HH:MM:SS[.S+][Z|(+|-)HH:MM]
          //
          unsigned short hours = 0;
          unsigned short minutes = 0;
          double seconds = 0.0;
          bool zone = false;
          short zh, zm;

          if (n >= 8)
          {
            // hours
            //
            hours = 10 * (s[0] - '0') + (s[1] - '0');

            // minutes
            //
            minutes = 10 * (s[3] - '0') + (s[4] - '0');

            // Find the end of the seconds fragment.
            //
            ro_string::size_type pos = 8;
            for (; pos < n; ++pos)
            {
              char c = s[pos];

              if (c == 'Z' || c == '+' || c == '-')
                break;
            }

            // Parse the time zone first so that we can truncate and
            // reuse the string.
            //
            if (pos < n)
            {
              bits::parse_time_zone (s + pos, n - pos, zh, zm);
              zone = true;
            }

            // seconds
            //
            str_.truncate (pos);
            seconds = strtod (s + 6, 0);
          }

          return zone
            ? time (hours, minutes, seconds, zh, zm)
            : time (hours, minutes, seconds);
        }
      }
    }
  }
}
