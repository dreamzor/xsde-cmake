// file      : xsde/cxx/serializer/validating/gyear-month.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdio.h> // sprintf/snprintf

#include <xsde/cxx/serializer/validating/gyear-month.hxx>
#include <xsde/cxx/serializer/validating/time-zone.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
        void gyear_month_simpl::
        pre (const gyear_month& value)
        {
          value_ = value;
        }

        void gyear_month_simpl::
        _serialize_content ()
        {
          // We only need strlen("-2147483649-MM+hh:mm") + 1 characters to
          // hold all representations of gYearMonth.
          //
          char str[21];

          int y = value_.year ();
          unsigned short m = value_.month ();

          if (y != 0 && m > 0 && m < 13 &&
              (!value_.zone_present () || bits::valid_time_zone (value_)))
          {
#ifdef XSDE_SNPRINTF
            int n = snprintf (str, 15, "%.4d-%.2u", y, m);
#else
            int n = sprintf (str, "%.4d-%.2u", y, m);
#endif
            if (n > 0 && n < 15)
            {
              if (value_.zone_present ())
              {
                if (int z = bits::serialize_time_zone (str + n, value_))
                  n += z;
                else
                {
                  _schema_error (schema_error::invalid_gyear_month_value);
                  return;
                }
              }

              _characters (str, static_cast<size_t> (n));
            }
            else
              _schema_error (schema_error::invalid_gyear_month_value);
          }
          else
            _schema_error (schema_error::invalid_gyear_month_value);
        }
      }
    }
  }
}
