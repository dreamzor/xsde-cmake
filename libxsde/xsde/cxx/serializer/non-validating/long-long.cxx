// file      : xsde/cxx/serializer/non-validating/long-long.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdio.h> // sprintf/snprintf

#include <xsde/cxx/serializer/non-validating/long-long.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace non_validating
      {
        void long_simpl::
        pre (long long value)
        {
          value_ = value;
        }

        void long_simpl::
        _serialize_content ()
        {
          // We only need strlen("-9223372036854775808") + 1 characters to
          // hold all representations of long long.
          //
          char str[21];

#ifdef XSDE_SNPRINTF
          int n = snprintf (str, 21, "%lld", value_);
#else
          int n = sprintf (str, "%lld", value_);
#endif
          if (n > 0 && n < 21)
            _characters (str, static_cast<size_t> (n));
        }
      }
    }
  }
}
