// file      : xsde/cxx/parser/non-validating/time-zone.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_NON_VALIDATING_TIME_ZONE_HXX
#define XSDE_CXX_PARSER_NON_VALIDATING_TIME_ZONE_HXX

#include <stddef.h> // size_t

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace non_validating
      {
        namespace bits
        {
          void
          parse_time_zone (const char* s,
                           size_t size,
                           short& hours,
                           short& minutes);
        }
      }
    }
  }
}

#endif  // XSDE_CXX_PARSER_NON_VALIDATING_TIME_ZONE_HXX
