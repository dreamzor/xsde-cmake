// file      : xsde/cxx/serializer/validating/unsigned-byte.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdio.h> // sprintf/snprintf

#include <xsde/cxx/serializer/validating/unsigned-byte.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
        void unsigned_byte_simpl::
        pre (unsigned char value)
        {
          value_ = value;
        }

        void unsigned_byte_simpl::
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

          // We only need strlen("256") + 1 characters to hold all
          // representations of unsigned byte.
          //
          char str[4];

#ifdef XSDE_SNPRINTF
          int n = snprintf (str, 4, "%u", value_);
#else
          int n = sprintf (str, "%u", value_);
#endif
          if (n > 0 && n < 4)
            _characters (str, static_cast<size_t> (n));
          else
            _schema_error (schema_error::invalid_unsigned_byte_value);
        }
      }
    }
  }
}
