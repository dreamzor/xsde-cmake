// file      : xsde/cxx/serializer/validating/decimal.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdio.h> // sprintf/snprintf

#include <xsde/cxx/serializer/validating/decimal.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
        void decimal_simpl::
        pre (double value)
        {
          value_ = value;
        }

        void decimal_simpl::
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

          // Assume double values cannot be longer than 127 characters.
          //
          char str[128];

#ifdef XSDE_SNPRINTF
          int n = snprintf (str, 128, "%.*f",
                            static_cast<int> (precision_), value_);
#else
          int n = sprintf (str, "%.*f",
                           static_cast<int> (precision_), value_);
#endif
          if (n > 0 && n < 128)
          {
            // For decimal, NaN and INF are not allowed.
            //
            int i = (str[0] == '-' ? 1 : 0);
            if ((str[i] == 'i' && str[i + 1] == 'n' && str[i + 2] == 'f') ||
                (str[i] == 'n' && str[i + 1] == 'a' && str[i + 2] == 'n'))
            {
              _schema_error (schema_error::invalid_decimal_value);
              return;
            }

            // Remove trailing '0' and '.' if necessary.
            //
            while (str[n - 1] == '0')
              n--;

            if (str[n - 1] == '.')
              n--;

            _characters (str, static_cast<size_t> (n));
          }
          else
            _schema_error (schema_error::invalid_decimal_value);
        }
      }
    }
  }
}
