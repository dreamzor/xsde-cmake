// file      : xsde/cxx/parser/non-validating/long-long.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdlib.h> // strtoull

#include <xsde/cxx/parser/non-validating/long-long.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace non_validating
      {
        void long_pimpl::
        _pre ()
        {
          size_ = 0;
          sign_ = none;
          state_ = leading_ws;
        }

        void long_pimpl::
        _characters (const ro_string& s)
        {
          parse (s, str_, 20);
        }

        long long long_pimpl::
        post_long ()
        {
          ro_string tmp (str_, size_);
          size_t size = trim_right (tmp);
          str_[size] = '\0';

          unsigned long long ull = strtoull (str_, 0, 10);

          return  (sign_ == minus)
            ? (ull == 9223372036854775808ULL
               ? (-9223372036854775807LL - 1)
               : -static_cast<long long> (ull))
            : static_cast<long long> (ull);
        }
      }
    }
  }
}
