// file      : xsde/cxx/parser/non-validating/time-zone.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/parser/non-validating/time-zone.hxx>

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
          parse_time_zone (const char* s, size_t n, short& h, short& m)
          {
            // time_zone := Z|(+|-)HH:MM
            //
            if (n == 0)
            {
              return;
            }
            else if (s[0] == 'Z')
            {
              h = 0;
              m = 0;
            }
            else if (n == 6)
            {
              // Parse hours.
              //
              h = 10 * (s[1] - '0') + (s[2] - '0');

              // Parse minutes.
              //
              m = 10 * (s[4] - '0') + (s[5] - '0');

              if (s[0] == '-')
              {
                h = -h;
                m = -m;
              }
            }
          }
        }
      }
    }
  }
}
