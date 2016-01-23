// file      : xsde/cxx/serializer/non-validating/gmonth-day.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdio.h> // sprintf/snprintf

#include <xsde/cxx/serializer/non-validating/gmonth-day.hxx>
#include <xsde/cxx/serializer/non-validating/time-zone.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace non_validating
      {
        void gmonth_day_simpl::
        pre (const gmonth_day& value)
        {
          value_ = value;
        }

        void gmonth_day_simpl::
        _serialize_content ()
        {
          // We only need strlen("--MM-DD+hh:mm") + 1 characters to hold all
          // representations of gMonthDay.
          //
          char str[14];

          if (value_.month () < 13 && value_.day () < 32)
          {
#ifdef XSDE_SNPRINTF
            int n = snprintf (str, 8, "--%.2u-%.2u",
                              value_.month (), value_.day ());
#else
            int n = sprintf (str, "--%.2u-%.2u",
                             value_.month (), value_.day ());
#endif
            if (n > 0 && n < 8)
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
