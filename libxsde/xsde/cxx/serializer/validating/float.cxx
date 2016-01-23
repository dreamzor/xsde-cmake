// file      : xsde/cxx/serializer/validating/float.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdio.h> // sprintf/snprintf

#include <xsde/cxx/serializer/validating/float.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
        void float_simpl::
        pre (float value)
        {
          value_ = value;
        }

        void float_simpl::
        _serialize_content ()
        {
          // Check facets.
          //
          const facets& f = _facets ();

          if (f.min_set_ &&
              (value_ < f.min_ || (!f.min_inc_ && value_ == f.min_)))
          {
            _schema_error (schema_error::value_less_than_min);
            return;
          }

          if (f.max_set_ &&
              (value_ > f.max_ || (!f.max_inc_ && value_ == f.max_)))
          {
            _schema_error (schema_error::value_greater_than_max);
            return;
          }

          // Assume float values cannot be longer than 127 characters.
          //
          char str[128];

          const char* fmt = 0;

          switch (notation_)
          {
          case notation_auto:
            {
              fmt = "%.*g";
              break;
            }
          case notation_fixed:
            {
              fmt = "%.*f";
              break;
            }
          case notation_scientific:
            {
              fmt = "%.*e";
              break;
            }
          }

#ifdef XSDE_SNPRINTF
          int n = snprintf (str, 128, fmt, precision_, value_);
#else
          int n = sprintf (str, fmt, precision_, value_);
#endif
          if (n > 0 && n < 128)
          {
            if (str[0] == '-')
            {
              if (str[1] == 'n' && str[2] == 'a' && str[3] == 'n')
              {
                _characters ("NaN", 3);
                return;
              }
              else if (str[1] == 'i' && str[2] == 'n' && str[3] == 'f')
              {
                _characters ("-INF", 4);
                return;
              }
            }
            else
            {
              if (str[0] == 'n' && str[1] == 'a' && str[2] == 'n')
              {
                _characters ("NaN", 3);
                return;
              }
              else if (str[0] == 'i' && str[1] == 'n' && str[2] == 'f')
              {
                _characters ("INF", 3);
                return;
              }
            }

            if (notation_ == notation_fixed)
            {
              // Remove trailing '0' and '.' if necessary.
              //
              while (str[n - 1] == '0')
                n--;

              if (str[n - 1] == '.')
                n--;
            }

            _characters (str, static_cast<size_t> (n));
          }
          else
            _schema_error (schema_error::invalid_float_value);
        }
      }
    }
  }
}
