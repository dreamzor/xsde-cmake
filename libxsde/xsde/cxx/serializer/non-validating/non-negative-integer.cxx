// file      : xsde/cxx/serializer/non-validating/non-negative-integer.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdio.h> // sprintf/snprintf

#include <xsde/cxx/serializer/non-validating/non-negative-integer.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace non_validating
      {
        void non_negative_integer_simpl::
        pre (unsigned long value)
        {
          value_ = value;
        }

        void non_negative_integer_simpl::
        _serialize_content ()
        {
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
        }
      }
    }
  }
}
