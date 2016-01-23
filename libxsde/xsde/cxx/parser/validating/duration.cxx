// file      : xsde/cxx/parser/validating/duration.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdlib.h> // strtoul, strtod

#include <xsde/cxx/config.hxx>
#include <xsde/cxx/errno.hxx>

#include <xsde/cxx/parser/validating/duration.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
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


        void duration_pimpl::
        _post ()
        {
          typedef ro_string::size_type size_type;

          char* s = str_.data ();
          ro_string tmp (s, str_.size ());
          size_type n = trim_right (tmp);

          negative_ = false;
          years_ = 0;
          months_ = 0;
          days_ = 0;
          hours_ = 0;
          minutes_ = 0;
          seconds_ = 0.0;

          // duration := [-]P[nY][nM][nD][TnHnMn[.n+]S]
          //

          if (n < 3 || (s[0] == '-' && n < 4))
          {
            _schema_error (schema_error::invalid_duration_value);
            return;
          }

          if (s[0] == '-')
            negative_ = true;

          if (s[negative_ ? 1 : 0] != 'P')
          {
            _schema_error (schema_error::invalid_duration_value);
            return;
          }

          // Parse it backwards so that we can truncate and reuse
          // the string.
          //

          bool need_t = false;
          size_type pos = n - 1;
          size_type t_pos = tmp.find ('T');

          char* p;
          char c;
          unsigned long ul;

          if (s[pos] == 'S')
          {
            need_t = true;
            str_.truncate (pos);
            pos = rfind_delim (s, pos - 1);
            c = s[pos + 1];

            if (c < '0' || c > '9')
            {
              _schema_error (schema_error::invalid_duration_value);
              return;
            }

            set_errno (0);
            seconds_ = strtod (s + pos + 1, &p);

            if (*p != '\0' || get_errno () != 0 || seconds_ < 0.0)
            {
              _schema_error (schema_error::invalid_duration_value);
              return;
            }
          }

          if (s[pos] == 'M' && t_pos != ro_string::npos && t_pos < pos)
          {
            need_t = true;
            str_.truncate (pos);
            pos = rfind_delim (s, pos - 1);
            c = s[pos + 1];

            if (c < '0' || c > '9')
            {
              _schema_error (schema_error::invalid_duration_value);
              return;
            }

            set_errno (0);
            ul = strtoul (s + pos + 1, &p, 10);

            if (*p != '\0' || get_errno () != 0 || ul > 4294967295UL)
            {
              _schema_error (schema_error::invalid_duration_value);
              return;
            }

            minutes_ = static_cast<unsigned int> (ul);
          }

          if (s[pos] == 'H')
          {
            need_t = true;
            str_.truncate (pos);
            pos = rfind_delim (s, pos - 1);
            c = s[pos + 1];

            if (c < '0' || c > '9')
            {
              _schema_error (schema_error::invalid_duration_value);
              return;
            }

            set_errno (0);
            ul = strtoul (s + pos + 1, &p, 10);

            if (*p != '\0' || get_errno () != 0 || ul > 4294967295UL)
            {
              _schema_error (schema_error::invalid_duration_value);
              return;
            }

            hours_ = static_cast<unsigned int> (ul);
          }

          if (need_t)
          {
            if (s[pos] == 'T')
              pos = rfind_delim (s, pos - 1);
            else
            {
              _schema_error (schema_error::invalid_duration_value);
              return;
            }
          }
          else
          {
            if (s[pos] == 'T')
            {
              _schema_error (schema_error::invalid_duration_value);
              return;
            }
          }

          if (s[pos] == 'D')
          {
            str_.truncate (pos);
            pos = rfind_delim (s, pos - 1);
            c = s[pos + 1];

            if (c < '0' || c > '9')
            {
              _schema_error (schema_error::invalid_duration_value);
              return;
            }

            set_errno (0);
            ul = strtoul (s + pos + 1, &p, 10);

            if (*p != '\0' || get_errno () != 0 || ul > 4294967295UL)
            {
              _schema_error (schema_error::invalid_duration_value);
              return;
            }

            days_ = static_cast<unsigned int> (ul);
          }

          if (s[pos] == 'M')
          {
            str_.truncate (pos);
            pos = rfind_delim (s, pos - 1);
            c = s[pos + 1];

            if (c < '0' || c > '9')
            {
              _schema_error (schema_error::invalid_duration_value);
              return;
            }

            set_errno (0);
            ul = strtoul (s + pos + 1, &p, 10);

            if (*p != '\0' || get_errno () != 0 || ul > 4294967295UL)
            {
              _schema_error (schema_error::invalid_duration_value);
              return;
            }

            months_ = static_cast<unsigned int> (ul);
          }

          if (s[pos] == 'Y')
          {
            str_.truncate (pos);
            pos = rfind_delim (s, pos - 1);
            c = s[pos + 1];

            if (c < '0' || c > '9')
            {
              _schema_error (schema_error::invalid_duration_value);
              return;
            }

            set_errno (0);
            ul = strtoul (s + pos + 1, &p, 10);

            if (*p != '\0' || get_errno () != 0 || ul > 4294967295UL)
            {
              _schema_error (schema_error::invalid_duration_value);
              return;
            }

            years_ = static_cast<unsigned int> (ul);
          }

          // Something did not match or appeared in the wrong order.
          //
          if (pos != static_cast<size_type> (negative_ ? 1 : 0))
          {
            _schema_error (schema_error::invalid_duration_value);
            return;
          }
        }

        duration duration_pimpl::
        post_duration ()
        {
          return duration (
            negative_, years_, months_, days_, hours_, minutes_, seconds_);
        }
      }
    }
  }
}
