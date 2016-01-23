// file      : xsde/cxx/serializer/validating/date.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdio.h> // sprintf/snprintf

#include <xsde/cxx/serializer/validating/date.hxx>
#include <xsde/cxx/serializer/validating/time-zone.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
        void date_simpl::
        pre (const date& value)
        {
          value_ = value;
        }

        void date_simpl::
        _serialize_content ()
        {
          // We only need strlen("-2147483649-MM-DD+hh:mm") + 1 characters to
          // hold all representations of date.
          //
          char str[24];

          int y = value_.year ();
          unsigned short m = value_.month ();
          unsigned short d = value_.day ();

          if (y != 0 && m > 0 && m < 13 && d > 0 && d < 32 &&
              (!value_.zone_present () || bits::valid_time_zone (value_)))
          {
#ifdef XSDE_SNPRINTF
            int n = snprintf (str, 18, "%.4d-%.2u-%.2u",
                              value_.year (), value_.month (), value_.day ());
#else
            int n = sprintf (str, "%.4d-%.2u-%.2u",
                             value_.year (), value_.month (), value_.day ());
#endif
            if (n > 0 && n < 18)
            {
              if (value_.zone_present ())
              {
                if (int z = bits::serialize_time_zone (str + n, value_))
                  n += z;
                else
                {
                  _schema_error (schema_error::invalid_date_value);
                  return;
                }
              }

              _characters (str, static_cast<size_t> (n));
            }
            else
              _schema_error (schema_error::invalid_date_value);
          }
          else
            _schema_error (schema_error::invalid_date_value);
        }
      }
    }
  }
}
