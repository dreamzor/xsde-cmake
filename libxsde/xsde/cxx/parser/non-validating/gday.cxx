// file      : xsde/cxx/parser/non-validating/gday.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/config.hxx>

#include <xsde/cxx/parser/non-validating/gday.hxx>
#include <xsde/cxx/parser/non-validating/time-zone.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace non_validating
      {
        void gday_pimpl::
        _pre ()
        {
#ifdef XSDE_EXCEPTIONS
          str_.assign ("", 0);
#else
          if (str_.assign ("", 0))
            _sys_error (sys_error::no_memory);
#endif
        }

        void gday_pimpl::
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

        gday gday_pimpl::
        post_gday ()
        {
          char* s = str_.data ();
          ro_string tmp (s, str_.size ());
          ro_string::size_type n = trim_right (tmp);

          // gday := ---DD[Z|(+|-)HH:MM]
          //

          unsigned short day = 0;
          bool zone = false;
          short zh, zm;

          if (n >= 5)
          {
            day = 10 * (s[3] - '0') + (s[4] - '0');

            if (n > 5)
            {
              bits::parse_time_zone (s + 5, n - 5, zh, zm);
              zone = true;
            }
          }

          return zone ? gday (day, zh, zm) : gday (day);
        }
      }
    }
  }
}
