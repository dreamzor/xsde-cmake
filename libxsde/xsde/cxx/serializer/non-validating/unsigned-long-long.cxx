// file      : xsde/cxx/serializer/non-validating/unsigned-long-long.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdio.h> // sprintf/snprintf

#include <xsde/cxx/serializer/non-validating/unsigned-long-long.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace non_validating
      {
        void unsigned_long_simpl::
        pre (unsigned long long value)
        {
          value_ = value;
        }

        void unsigned_long_simpl::
        _serialize_content ()
        {
          // We only need strlen("18446744073709551615") + 1 characters to
          // hold all representations of unsigned long long.
          //
          char str[21];

#ifdef XSDE_SNPRINTF
          int n = snprintf (str, 21, "%llu", value_);
#else
          int n = sprintf (str, "%llu", value_);
#endif
          if (n > 0 && n < 21)
            _characters (str, static_cast<size_t> (n));
        }
      }
    }
  }
}
