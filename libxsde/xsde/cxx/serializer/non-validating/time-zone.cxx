// file      : xsde/cxx/serializer/non-validating/time-zone.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdio.h> // sprintf/snprintf

#include <xsde/cxx/config.hxx>

#include <xsde/cxx/serializer/non-validating/time-zone.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace non_validating
      {
        namespace bits
        {
          int
          serialize_time_zone (char* s, const time_zone& z)
          {
            // time-zone := Z|(+|-)HH:MM
            //

            short h = z.zone_hours ();
            short m = z.zone_minutes ();

            if (h == 0 && m == 0)
            {
              *s = 'Z';
              return 1;
            }
            else
            {
              const char* fmt = "+%.2u:%.2u";

              if (h < 0 || m < 0)
              {
                fmt = "-%.2u:%.2u";
                h = -h;
                m = -m;
              }

              if (h >= 0 && h <= 14 && m >= 0 && m <= 59)
              {
#ifdef XSDE_SNPRINTF
                int n = snprintf (s, 7, fmt, h, m);
#else
                int n = sprintf (s, fmt, h, m);
#endif
                if (n > 0 && n < 7)
                  return n;
              }

              return 0;
            }
          }
        }
      }
    }
  }
}
