// file      : xsde/cxx/serializer/non-validating/decimal.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdio.h> // sprintf/snprintf

#include <xsde/cxx/serializer/non-validating/decimal.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace non_validating
      {
        void decimal_simpl::
        pre (double value)
        {
          value_ = value;
        }

        void decimal_simpl::
        _serialize_content ()
        {
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
            // Remove trailing '0' and '.' if necessary.
            //
            while (str[n - 1] == '0')
              n--;

            if (str[n - 1] == '.')
              n--;

            _characters (str, static_cast<size_t> (n));
          }
        }
      }
    }
  }
}
