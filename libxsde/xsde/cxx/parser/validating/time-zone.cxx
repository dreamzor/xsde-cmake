// file      : xsde/cxx/parser/validating/time-zone.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/parser/validating/time-zone.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
      {
        namespace bits
        {
          bool
          parse_time_zone (const char* s, size_t n, short& h, short& m)
          {
            // time_zone := Z|(+|-)HH:MM
            //
            if (n == 0)
            {
              return false;
            }
            else if (s[0] == 'Z')
            {
              if (n != 1)
                return false;

              h = 0;
              m = 0;
            }
            else
            {
              if (n != 6 || (s[0] != '-' && s[0] != '+') || s[3] != ':')
                return false;

              // Parse hours.
              //
              char d1 = s[1];
              char d2 = s[2];

              if (d1 < '0' || d1 > '9' || d2 < '0' || d2 > '9')
                return false;

              h = 10 * (d1 - '0') + (d2 - '0');

              if (h > 14)
                return false;

              // Parse minutes.
              //
              d1 = s[4];
              d2 = s[5];

              if (d1 < '0' || d1 > '9' || d2 < '0' || d2 > '9')
                return false;

              m = 10 * (d1 - '0') + (d2 - '0');

              if (m > 59 || (h == 14 && m != 0))
                return false;

              if (s[0] == '-')
              {
                h = -h;
                m = -m;
              }
            }

            return true;
          }
        }
      }
    }
  }
}
