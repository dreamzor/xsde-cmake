// file      : xsde/cxx/parser/non-validating/duration.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdlib.h> // strtoul, strtod

#include <xsde/cxx/config.hxx>

#include <xsde/cxx/parser/non-validating/duration.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace non_validating
      {
        void duration_pimpl::
        _pre ()
        {
#ifdef XSDE_EXCEPTIONS
          str_.assign ("", 0);
#else
          if (str_.assign ("", 0))
            _sys_error (sys_error::no_memory);
#endif
        }

        void duration_pimpl::
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

        static ro_string::size_type
        rfind_delim (const char* s, ro_string::size_type pos)
        {
          const char* p = s + pos;
          for (; p >= s; --p)
          {
            if (*p == 'Y' || *p == 'D' || *p == 'M' ||
                *p == 'H' || *p == 'M' || *p == 'S' ||
                *p == 'T' || *p == 'P')
              break;
          }

          return p >= s ? p - s : ro_string::npos;
        }

        duration duration_pimpl::
        post_duration ()
        {
          char* s = str_.data ();
          ro_string tmp (s, str_.size ());
          ro_string::size_type n = trim_right (tmp);

          bool negative = false;
          unsigned int years = 0;
          unsigned int months = 0;
          unsigned int days = 0;
          unsigned int hours = 0;
          unsigned int minutes = 0;
          double seconds = 0.0;

          // duration := [-]P[nY][nM][nD][TnHnMn[.n+]S]
          //

          if (n >= 3 && s[s[0] == '-' ? 1 : 0] == 'P')
          {
            if (s[0] == '-')
              negative = true;

            // Parse it backwards so that we can truncate and reuse
            // the string.
            //
            ro_string::size_type pos = n - 1;
            ro_string::size_type t_pos = tmp.find ('T');

            if (s[pos] == 'S')
            {
              str_.truncate (pos);
              pos = rfind_delim (s, pos - 1);

              seconds = strtod (s + pos + 1, 0);
            }

            if (s[pos] == 'M' && t_pos != ro_string::npos && t_pos < pos)
            {
              str_.truncate (pos);
              pos = rfind_delim (s, pos - 1);

              minutes =
                static_cast<unsigned int> (strtoul (s + pos + 1, 0, 10));
            }

            if (s[pos] == 'H')
            {
              str_.truncate (pos);
              pos = rfind_delim (s, pos - 1);

              hours =
                static_cast<unsigned int> (strtoul (s + pos + 1, 0, 10));
            }

            if (s[pos] == 'T')
              pos = rfind_delim (s, pos - 1);

            if (s[pos] == 'D')
            {
              str_.truncate (pos);
              pos = rfind_delim (s, pos - 1);

              days =
                static_cast<unsigned int> (strtoul (s + pos + 1, 0, 10));
            }

            if (s[pos] == 'M')
            {
              str_.truncate (pos);
              pos = rfind_delim (s, pos - 1);

              months =
                static_cast<unsigned int> (strtoul (s + pos + 1, 0, 10));
            }

            if (s[pos] == 'Y')
            {
              str_.truncate (pos);
              pos = rfind_delim (s, pos - 1);

              years =
                static_cast<unsigned int> (strtoul (s + pos + 1, 0, 10));
            }
          }

          return duration (
            negative, years, months, days, hours, minutes, seconds);
        }
      }
    }
  }
}
