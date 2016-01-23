// file      : xsde/cxx/serializer/non-validating/gyear.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdio.h> // sprintf/snprintf

#include <xsde/cxx/serializer/non-validating/gyear.hxx>
#include <xsde/cxx/serializer/non-validating/time-zone.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace non_validating
      {
        void gyear_simpl::
        pre (const gyear& value)
        {
          value_ = value;
        }

        void gyear_simpl::
        _serialize_content ()
        {
          // We only need strlen("-2147483649+hh:mm") + 1 characters to
          // hold all representations of gYear.
          //
          char str[18];

#ifdef XSDE_SNPRINTF
          int n = snprintf (str, 12, "%.4d", value_.year ());
#else
          int n = sprintf (str, "%.4d", value_.year ());
#endif
          if (n > 0 && n < 12)
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
