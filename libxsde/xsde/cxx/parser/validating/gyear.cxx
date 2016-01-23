// file      : xsde/cxx/parser/validating/gyear.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdlib.h> // strtoul

#include <xsde/cxx/config.hxx>
#include <xsde/cxx/errno.hxx>

#include <xsde/cxx/parser/validating/gyear.hxx>
#include <xsde/cxx/parser/validating/time-zone.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
      {
        void gyear_pimpl::
        _pre ()
        {
#ifdef XSDE_EXCEPTIONS
          str_.assign ("", 0);
#else
          if (str_.assign ("", 0))
            _sys_error (sys_error::no_memory);
#endif
        }

        void gyear_pimpl::
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

        void gyear_pimpl::
        _post ()
        {
          char* s = str_.data ();
          ro_string tmp (s, str_.size ());
          ro_string::size_type n = trim_right (tmp);

          // gyear := [-]CCYY[N]*[Z|(+|-)HH:MM]
          //

          if (n < 4 || (s[0] == '-' && n < 5))
          {
            _schema_error (schema_error::invalid_gyear_value);
            return;
          }

          // Find the end of the year token.
          //
          ro_string::size_type pos = (s[0] == '-' ? 5 : 4);
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
            if (!bits::parse_time_zone (s + pos, n - pos, zh_, zm_))
            {
              _schema_error (schema_error::invalid_gyear_value);
              return;
            }

            z_ = true;
          }
          else
            z_ = false;

          // Parse the year value.
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
            _schema_error (schema_error::invalid_gyear_value);
            return;
          }

          year_ = neg
            ? (ul == 2147483648UL
               ? (-2147483647 - 1)
               : -static_cast<int> (ul))
            : static_cast<int> (ul);
        }

        gyear gyear_pimpl::
        post_gyear ()
        {
          return z_ ? gyear (year_, zh_, zm_) : gyear (year_);
        }
      }
    }
  }
}
