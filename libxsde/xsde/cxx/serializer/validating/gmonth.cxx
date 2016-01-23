// file      : xsde/cxx/serializer/validating/gmonth.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdio.h> // sprintf/snprintf

#include <xsde/cxx/serializer/validating/gmonth.hxx>
#include <xsde/cxx/serializer/validating/time-zone.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
        void gmonth_simpl::
        pre (const gmonth& value)
        {
          value_ = value;
        }

        void gmonth_simpl::
        _serialize_content ()
        {
          // We only need strlen("--MM+hh:mm") + 1 characters to hold all
          // representations of gMonth.
          //
          char str[11];

          unsigned short m = value_.month ();

          if (m > 0 && m < 13 &&
              (!value_.zone_present () || bits::valid_time_zone (value_)))
          {
#ifdef XSDE_SNPRINTF
            int n = snprintf (str, 5, "--%.2u", m);
#else
            int n = sprintf (str, "--%.2u", m);
#endif
            if (n > 0 && n < 5)
            {
              if (value_.zone_present ())
              {
                if (int z = bits::serialize_time_zone (str + n, value_))
                  n += z;
                else
                {
                  _schema_error (schema_error::invalid_gmonth_value);
                  return;
                }
              }

              _characters (str, static_cast<size_t> (n));
            }
            else
              _schema_error (schema_error::invalid_gmonth_value);
          }
          else
            _schema_error (schema_error::invalid_gmonth_value);
        }
      }
    }
  }
}
