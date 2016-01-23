// file      : xsde/cxx/serializer/non-validating/date-time.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdio.h> // sprintf/snprintf

#include <xsde/cxx/serializer/non-validating/date-time.hxx>
#include <xsde/cxx/serializer/non-validating/time-zone.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace non_validating
      {
        void date_time_simpl::
        pre (const date_time& value)
        {
          value_ = value;
        }

        void date_time_simpl::
        _serialize_content ()
        {
          // We only need strlen("-2147483649-MM-DDThh:mm:ss.ssssss-hh:mm")
          // + 1 characters to hold all representations of date_time. We
          // know that the seconds part (represented as double) has
          // default precision of 6.
          //
          char str[40];

          if (value_.month () <= 12 &&
              value_.day () <= 31 &&
              value_.hours () <= 24 &&
              value_.minutes () <= 59 &&
              value_.seconds () >= 0.0 &&
              value_.seconds () < 60.0)
          {
#ifdef XSDE_SNPRINTF
            int n = snprintf (str, 34, "%.4d-%.2u-%.2uT%.2u:%.2u:%09f",
                              value_.year (), value_.month (), value_.day (),
                              value_.hours (), value_.minutes (),
                              value_.seconds ());
#else
            int n = sprintf (str, "%.4d-%.2u-%.2uT%.2u:%.2u:%09f",
                             value_.year (), value_.month (), value_.day (),
                             value_.hours (), value_.minutes (),
                             value_.seconds ());
#endif
            if (n > 0 && n < 34)
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
