// file      : xsde/cxx/serializer/validating/gday.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdio.h> // sprintf/snprintf

#include <xsde/cxx/serializer/validating/gday.hxx>
#include <xsde/cxx/serializer/validating/time-zone.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
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

          unsigned short d = value_.day ();

          if (d > 0 && d < 32 &&
              (!value_.zone_present () || bits::valid_time_zone (value_)))
          {
#ifdef XSDE_SNPRINTF
            int n = snprintf (str, 6, "---%.2u", d);
#else
            int n = sprintf (str, "---%.2u", d);
#endif
            if (n > 0 && n < 6)
            {
              if (value_.zone_present ())
              {
                if (int z = bits::serialize_time_zone (str + n, value_))
                  n += z;
                else
                {
                  _schema_error (schema_error::invalid_gday_value);
                  return;
                }
              }

              _characters (str, static_cast<size_t> (n));
            }
            else
              _schema_error (schema_error::invalid_gday_value);
          }
          else
            _schema_error (schema_error::invalid_gday_value);
        }
      }
    }
  }
}
