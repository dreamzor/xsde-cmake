// file      : xsde/cxx/parser/validating/gmonth.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/config.hxx>

#include <xsde/cxx/parser/validating/gmonth.hxx>
#include <xsde/cxx/parser/validating/time-zone.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
      {
        void gmonth_pimpl::
        _pre ()
        {
#ifdef XSDE_EXCEPTIONS
          str_.assign ("", 0);
#else
          if (str_.assign ("", 0))
            _sys_error (sys_error::no_memory);
#endif
        }

        void gmonth_pimpl::
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

        void gmonth_pimpl::
        _post ()
        {
          char* s = str_.data ();
          ro_string tmp (s, str_.size ());
          ro_string::size_type n = trim_right (tmp);

          // gmonth := --MM[Z|(+|-)HH:MM]
          //
          if (n < 4 || s[0] != '-' || s[1] != '-')
          {
            _schema_error (schema_error::invalid_gmonth_value);
            return;
          }

          char d1 = s[2];
          char d2 = s[3];

          if (d1 < '0' || d1 > '9' || d2 < '0' || d2 > '9')
          {
            _schema_error (schema_error::invalid_gmonth_value);
            return;
          }

          month_ = 10 * (d1 - '0') + (d2 - '0');

          if (month_ < 1 || month_ > 12)
          {
            _schema_error (schema_error::invalid_gmonth_value);
            return;
          }

          if (n > 4)
          {
            if (!bits::parse_time_zone (s + 4, n - 4, zh_, zm_))
            {
              _schema_error (schema_error::invalid_gmonth_value);
              return;
            }

            z_ = true;
          }
          else
            z_ = false;
        }

        gmonth gmonth_pimpl::
        post_gmonth ()
        {
          return z_ ? gmonth (month_, zh_, zm_) : gmonth (month_);
        }
      }
    }
  }
}
