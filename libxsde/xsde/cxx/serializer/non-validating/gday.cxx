// file      : xsde/cxx/serializer/non-validating/gday.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdio.h> // sprintf/snprintf

#include <xsde/cxx/serializer/non-validating/gday.hxx>
#include <xsde/cxx/serializer/non-validating/time-zone.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace non_validating
      {
        void gday_simpl::
        pre (const gday& value)
        {
          value_ = value;
        }

        void gday_simpl::
        _serialize_content ()
        {
          // We only need strlen("---DD+hh:mm") + 1 characters to hold all
          // representations of gDay.
          //
          char str[12];

          if (value_.day () < 32)
          {
#ifdef XSDE_SNPRINTF
            int n = snprintf (str, 6, "---%.2u", value_.day ());
#else
            int n = sprintf (str, "---%.2u", value_.day ());
#endif
            if (n > 0 && n < 6)
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
