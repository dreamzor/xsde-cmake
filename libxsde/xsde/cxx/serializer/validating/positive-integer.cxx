// file      : xsde/cxx/serializer/validating/positive-integer.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdio.h> // sprintf/snprintf

#include <xsde/cxx/serializer/validating/positive-integer.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
        void positive_integer_simpl::
        pre (unsigned long value)
        {
          value_ = value;
        }

        void positive_integer_simpl::
        _serialize_content ()
        {
          if (value_ == 0)
          {
            _schema_error (schema_error::invalid_positive_integer_value);
            return;
          }

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

          // We only need strlen("18446744073709551615") + 1 characters to
          // hold all representations of (possibly 64-bit) unsigned long.
          //
          char str[21];

#ifdef XSDE_SNPRINTF
          int n = snprintf (str, 21, "%lu", value_);
#else
          int n = sprintf (str, "%lu", value_);
#endif
          if (n > 0 && n < 21)
            _characters (str, static_cast<size_t> (n));
          else
            _schema_error (schema_error::invalid_positive_integer_value);
        }
      }
    }
  }
}
