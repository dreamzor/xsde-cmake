// file      : xsde/cxx/serializer/non-validating/unsigned-byte.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdio.h> // sprintf/snprintf

#include <xsde/cxx/serializer/non-validating/unsigned-byte.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace non_validating
      {
        void unsigned_byte_simpl::
        pre (unsigned char value)
        {
          value_ = value;
        }

        void unsigned_byte_simpl::
        _serialize_content ()
        {
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
        }
      }
    }
  }
}
