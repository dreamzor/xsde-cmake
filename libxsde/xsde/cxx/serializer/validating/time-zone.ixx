// file      : xsde/cxx/serializer/validating/time-zone.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
        namespace bits
        {
          inline bool
          valid_time_zone (const time_zone& z)
          {
            short h = z.zone_hours ();
            short m = z.zone_minutes ();

            unsigned short ah = h < 0 ? -h : h;
            unsigned short am = m < 0 ? -m : m;

            return ((h <= 0 && m <= 0) || (h >= 0 && m >= 0)) &&
              ((ah < 14 && am < 60) || (ah == 14 && am == 0));
          }
        }
      }
    }
  }
}
