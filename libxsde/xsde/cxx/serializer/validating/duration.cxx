// file      : xsde/cxx/serializer/validating/duration.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdio.h> // sprintf/snprintf

#include <xsde/cxx/serializer/validating/duration.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
        void duration_simpl::
        pre (const duration& value)
        {
          value_ = value;
        }

        void duration_simpl::
        _serialize_content ()
        {
          if (value_.seconds () < 0.0)
          {
            _schema_error (schema_error::invalid_duration_value);
            return;
          }

          // duration := -PnYnMnDTnHnMnS
          //
          // The years, months, days, hours, and minutes components are
          // represented as 32 unsigned integers with maximum string
          // representation being strlen ("4294967295") = 10.
          //
          // We assume that the seconds part (double) cannot be longer
          // than 128 chars.
          //
          // The total representation thus cannot exceed 10*5 + 128 +
          // 9 + 1 = 188 characters.
          //
          char str[188];
          char* p = str;

          if (value_.negative ())
            *p++ = '-';

          *p++ = 'P';

          // years
          //
          // In case it is 0-duration, use the years field to handle
          // this case.
          //
          if (value_.years () != 0 ||
              (value_.months () == 0 &&
               value_.days () == 0 &&
               value_.hours () == 0 &&
               value_.minutes () == 0 &&
               value_.seconds () == 0.0))
          {
#ifdef XSDE_SNPRINTF
            int n = snprintf (p, 11, "%u", value_.years ());
#else
            int n = sprintf (p, "%u", value_.years ());
#endif
            if (n < 0 || n >= 11)
            {
              _schema_error (schema_error::invalid_duration_value);
              return;
            }

            p += n;
            *p++ = 'Y';
          }

          // months
          //
          if (value_.months () != 0)
          {
#ifdef XSDE_SNPRINTF
            int n = snprintf (p, 11, "%u", value_.months ());
#else
            int n = sprintf (p, "%u", value_.months ());
#endif
            if (n < 0 || n >= 11)
            {
              _schema_error (schema_error::invalid_duration_value);
              return;
            }

            p += n;
            *p++ = 'M';
          }

          // days
          //
          if (value_.days () != 0)
          {
#ifdef XSDE_SNPRINTF
            int n = snprintf (p, 11, "%u", value_.days ());
#else
            int n = sprintf (p, "%u", value_.days ());
#endif
            if (n < 0 || n >= 11)
            {
              _schema_error (schema_error::invalid_duration_value);
              return;
            }

            p += n;
            *p++ = 'D';
          }

          // Figure out if we need the 'T' delimiter.
          //
          if (value_.hours () != 0 ||
              value_.minutes () != 0 ||
              value_.seconds () != 0.0)
            *p++ = 'T';

          // hours
          //
          if (value_.hours () != 0)
          {
#ifdef XSDE_SNPRINTF
            int n = snprintf (p, 11, "%u", value_.hours ());
#else
            int n = sprintf (p, "%u", value_.hours ());
#endif
            if (n < 0 || n >= 11)
            {
              _schema_error (schema_error::invalid_duration_value);
              return;
            }

            p += n;
            *p++ = 'H';
          }

          // minutes
          //
          if (value_.minutes () != 0)
          {
#ifdef XSDE_SNPRINTF
            int n = snprintf (p, 11, "%u", value_.minutes ());
#else
            int n = sprintf (p, "%u", value_.minutes ());
#endif
            if (n < 0 || n >= 11)
            {
              _schema_error (schema_error::invalid_duration_value);
              return;
            }

            p += n;
            *p++ = 'M';
          }

          // seconds
          //
          if (value_.seconds () > 0.0)
          {
#ifdef XSDE_SNPRINTF
            int n = snprintf (p, 128, "%f", value_.seconds ());
#else
            int n = sprintf (p, "%f", value_.seconds ());
#endif
            if (n < 0 || n >= 128)
            {
              _schema_error (schema_error::invalid_duration_value);
              return;
            }

            // Remove trailing '0' and '.' if necessary.
            //
            while (p[n - 1] == '0')
              n--;

            if (p[n - 1] == '.')
              n--;

            p += n;
            *p++ = 'S';
          }

          _characters (str, static_cast<size_t> (p - str));
        }
      }
    }
  }
}
