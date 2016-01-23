// file      : xsde/cxx/parser/validating/time.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdlib.h> // strtod

#include <xsde/cxx/config.hxx>
#include <xsde/cxx/errno.hxx>

#include <xsde/cxx/parser/validating/time.hxx>
#include <xsde/cxx/parser/validating/time-zone.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
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

        void time_pimpl::
        _post ()
        {
          char* s = str_.data ();
          ro_string tmp (s, str_.size ());
          ro_string::size_type n = trim_right (tmp);

          // time := HH:MM:SS[.S+][Z|(+|-)HH:MM]
          //

          if (n < 8 || s[2] != ':' || s[5] != ':')
          {
            _schema_error (schema_error::invalid_time_value);
            return;
          }

          // hours
          //
          char d1 = s[0];
          char d2 = s[1];

          if (d1 < '0' || d1 > '9' || d2 < '0' || d2 > '9')
          {
            _schema_error (schema_error::invalid_time_value);
            return;
          }

          hours_ = 10 * (d1 - '0') + (d2 - '0');

          if (hours_ > 24)
          {
            _schema_error (schema_error::invalid_time_value);
            return;
          }

          // minutes
          //
          d1 = s[3];
          d2 = s[4];

          if (d1 < '0' || d1 > '9' || d2 < '0' || d2 > '9')
          {
            _schema_error (schema_error::invalid_time_value);
            return;
          }

          minutes_ = 10 * (d1 - '0') + (d2 - '0');

          if (minutes_ > 59)
          {
            _schema_error (schema_error::invalid_time_value);
            return;
          }

          // Find the end of the seconds fragment.
          //
          ro_string::size_type pos = 8;
          for (; pos < n; ++pos)
          {
            char c = s[pos];

            if (c == 'Z' || c == '+' || c == '-')
              break;
          }

          // At least one digit should follow the fraction point.
          //
          if ((pos - 6) == 3)
          {
            _schema_error (schema_error::invalid_time_value);
            return;
          }

          // Parse the time zone first so that we can truncate and
          // reuse the string.
          //
          if (pos < n)
          {
            if (!bits::parse_time_zone (s + pos, n - pos, zh_, zm_))
            {
              _schema_error (schema_error::invalid_time_value);
              return;
            }

            z_ = true;
          }
          else
            z_ = false;

          // seconds
          //
          str_.truncate (pos);

          char* p;
          set_errno (0);
          seconds_ = strtod (s + 6, &p);

          if (*p != '\0' || get_errno () != 0 || seconds_ >= 60.0)
          {
            _schema_error (schema_error::invalid_time_value);
            return;
          }

          if (hours_ == 24 && (minutes_ != 0 || seconds_ != 0.0))
          {
            _schema_error (schema_error::invalid_time_value);
            return;
          }
        }

        time time_pimpl::
        post_time ()
        {
          return z_
            ? time (hours_, minutes_, seconds_, zh_, zm_)
            : time (hours_, minutes_, seconds_);
        }
      }
    }
  }
}
