// file      : xsde/cxx/serializer/non-validating/byte.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdio.h> // sprintf/snprintf

#include <xsde/cxx/serializer/non-validating/byte.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace non_validating
      {
        void byte_simpl::
        pre (signed char value)
        {
          value_ = value;
        }

        void byte_simpl::
        _serialize_content ()
        {
          // We only need strlen("-128") + 1 characters to hold all
          // representations of signed byte.
          //
          char str[5];

#ifdef XSDE_SNPRINTF
          int n = snprintf (str, 5, "%d", value_);
#else
          int n = sprintf (str, "%d", value_);
#endif
          if (n > 0 && n < 5)
            _characters (str, static_cast<size_t> (n));
        }
      }
    }
  }
}
