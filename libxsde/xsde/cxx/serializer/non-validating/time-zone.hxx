// file      : xsde/cxx/serializer/non-validating/time-zone.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_NON_VALIDATING_TIME_ZONE_HXX
#define XSDE_CXX_SERIALIZER_NON_VALIDATING_TIME_ZONE_HXX

#include <xsde/cxx/date-time.hxx>

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
          // Returns 0 in case of a failure and the number of
          // characters written otherwise. The buffer should
          // have space for at least 7 characters.
          //
          int
          serialize_time_zone (char* s, const time_zone&);
        }
      }
    }
  }
}

#endif  // XSDE_CXX_SERIALIZER_NON_VALIDATING_TIME_ZONE_HXX
