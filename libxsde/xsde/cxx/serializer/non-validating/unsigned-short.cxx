// file      : xsde/cxx/serializer/non-validating/unsigned-short.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdio.h> // sprintf/snprintf

#include <xsde/cxx/serializer/non-validating/unsigned-short.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace non_validating
      {
        void unsigned_short_simpl::
        pre (unsigned short value)
        {
          value_ = value;
        }

        void unsigned_short_simpl::
        _serialize_content ()
        {
          // We only need strlen("65535") + 1 characters to hold all
          // representations of short.
          //
          char str[6];

#ifdef XSDE_SNPRINTF
          int n = snprintf (str, 6, "%u", value_);
#else
          int n = sprintf (str, "%u", value_);
#endif
          if (n > 0 && n < 6)
            _characters (str, static_cast<size_t> (n));
        }
      }
    }
  }
}
