// file      : xsde/cxx/parser/validating/gmonth-day.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/config.hxx>

#include <xsde/cxx/parser/validating/gmonth-day.hxx>
#include <xsde/cxx/parser/validating/time-zone.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
      {
        void gmonth_day_pimpl::
        _pre ()
        {
#ifdef XSDE_EXCEPTIONS
          str_.assign ("", 0);
#else
          if (str_.assign ("", 0))
            _sys_error (sys_error::no_memory);
#endif
        }

        void gmonth_day_pimpl::
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

        void gmonth_day_pimpl::
        _post ()
        {
          char* s = str_.data ();
          ro_string tmp (s, str_.size ());
          ro_string::size_type n = trim_right (tmp);

          // gmonth_day := --MM-DD[Z|(+|-)HH:MM]
          //
          if (n < 7 || s[0] != '-' || s[1] != '-' || s[4] != '-')
          {
            _schema_error (schema_error::invalid_gmonth_day_value);
            return;
          }

          // month
          //
          char d1 = s[2];
          char d2 = s[3];

          if (d1 < '0' || d1 > '9' || d2 < '0' || d2 > '9')
          {
            _schema_error (schema_error::invalid_gmonth_day_value);
            return;
          }

          month_ = 10 * (d1 - '0') + (d2 - '0');

          if (month_ < 1 || month_ > 12)
          {
            _schema_error (schema_error::invalid_gmonth_day_value);
            return;
          }

          // day
          //
          d1 = s[5];
          d2 = s[6];

          if (d1 < '0' || d1 > '9' || d2 < '0' || d2 > '9')
          {
            _schema_error (schema_error::invalid_gmonth_day_value);
            return;
          }

          day_ = 10 * (d1 - '0') + (d2 - '0');

          if (day_ < 1 || day_ > 31)
          {
            _schema_error (schema_error::invalid_gmonth_day_value);
            return;
          }

          // zone
          //
          if (n > 7)
          {
            if (!bits::parse_time_zone (s + 7, n - 7, zh_, zm_))
            {
              _schema_error (schema_error::invalid_gmonth_day_value);
              return;
            }

            z_ = true;
          }
          else
            z_ = false;
        }

        gmonth_day gmonth_day_pimpl::
        post_gmonth_day ()
        {
          return z_
            ? gmonth_day (month_, day_, zh_, zm_)
            : gmonth_day (month_, day_);
        }
      }
    }
  }
}
