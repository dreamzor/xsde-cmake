// file      : xsde/cxx/serializer/non-validating/time.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdio.h> // sprintf/snprintf

#include <xsde/cxx/serializer/non-validating/time.hxx>
#include <xsde/cxx/serializer/non-validating/time-zone.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace non_validating
      {
        void time_simpl::
        pre (const time& value)
        {
          value_ = value;
        }

        void time_simpl::
        _serialize_content ()
        {
          // We only need strlen("hh:mm:ss.ssssss-hh:mm") + 1 characters to
          // hold all representations of time. We know that the seconds
          // part (represented as double) has default precision of 6.
          //
          char str[22];

          if (value_.hours () <= 24 &&
              value_.minutes () <= 59 &&
              value_.seconds () >= 0.0 &&
              value_.seconds () < 60.0)
          {
#ifdef XSDE_SNPRINTF
            int n = snprintf (str, 16, "%.2u:%.2u:%09f",
                              value_.hours (), value_.minutes (),
                              value_.seconds ());
#else
            int n = sprintf (str, "%.2u:%.2u:%09f",
                             value_.hours (), value_.minutes (),
                             value_.seconds ());
#endif
            if (n > 0 && n < 16)
            {
              // Remove trailing '0' and '.' if necessary.
              //
              while (str[n - 1] == '0')
                n--;

              if (str[n - 1] == '.')
                n--;

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
