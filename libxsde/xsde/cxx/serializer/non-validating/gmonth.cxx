// file      : xsde/cxx/serializer/non-validating/gmonth.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdio.h> // sprintf/snprintf

#include <xsde/cxx/serializer/non-validating/gmonth.hxx>
#include <xsde/cxx/serializer/non-validating/time-zone.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace non_validating
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

          if (value_.month () < 13)
          {
#ifdef XSDE_SNPRINTF
            int n = snprintf (str, 5, "--%.2u", value_.month ());
#else
            int n = sprintf (str, "--%.2u", value_.month ());
#endif
            if (n > 0 && n < 5)
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
