// file      : xsde/cxx/serializer/validating/time-zone.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_VALIDATING_TIME_ZONE_HXX
#define XSDE_CXX_SERIALIZER_VALIDATING_TIME_ZONE_HXX

#include <xsde/cxx/date-time.hxx>

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
          // Returns 0 in case of a failure and the number of
          // characters written otherwise. The buffer should
          // have space for at least 7 characters. Note that
          // this function expects that the time zone was
          // verified by valid_time_zone() above.
          //
          int
          serialize_time_zone (char* s, const time_zone&);

          bool
          valid_time_zone (const time_zone&);
        }
      }
    }
  }
}

#include <xsde/cxx/serializer/validating/time-zone.ixx>

#endif  // XSDE_CXX_SERIALIZER_VALIDATING_TIME_ZONE_HXX
