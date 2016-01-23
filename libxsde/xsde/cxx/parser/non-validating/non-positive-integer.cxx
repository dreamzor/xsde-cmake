// file      : xsde/cxx/parser/non-validating/non-positive-integer.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdlib.h> // strtoul
#include <limits.h> // LONG_MIN

#include <xsde/cxx/parser/non-validating/non-positive-integer.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace non_validating
      {
        void non_positive_integer_pimpl::
        _pre ()
        {
          size_ = 0;
          sign_ = none;
          state_ = leading_ws;
        }

        void non_positive_integer_pimpl::
        _characters (const ro_string& s)
        {
          parse (s, str_, 20);
        }

        long non_positive_integer_pimpl::
        post_non_positive_integer ()
        {
          ro_string tmp (str_, size_);
          size_t size = trim_right (tmp);
          str_[size] = '\0';

          unsigned long ul = strtoul (str_, 0, 10);

          return (ul == static_cast<unsigned long> (LONG_MIN))
            ? LONG_MIN : -static_cast<long> (ul);
        }
      }
    }
  }
}
