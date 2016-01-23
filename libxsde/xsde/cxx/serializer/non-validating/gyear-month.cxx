// file      : xsde/cxx/serializer/non-validating/gyear-month.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdio.h> // sprintf/snprintf

#include <xsde/cxx/serializer/non-validating/gyear-month.hxx>
#include <xsde/cxx/serializer/non-validating/time-zone.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace non_validating
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

          if (value_.month () < 13)
          {
#ifdef XSDE_SNPRINTF
            int n = snprintf (str, 15, "%.4d-%.2u",
                              value_.year (), value_.month ());
#else
            int n = sprintf (str, "%.4d-%.2u",
                             value_.year (), value_.month ());
#endif
            if (n > 0 && n < 15)
            {
              if (value_.zone_present ())
              {
                if (int z = bits::serialize_time_zone (str + n, value_))
                  n += z;
                else
                  return;
              }

              _characters (str, static_cast<size_t> (n));
            }
          }
        }
      }
    }
  }
}
