// file      : xsde/cxx/parser/non-validating/integer.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdlib.h> // strtoul
#include <limits.h> // LONG_MIN, LONG_MAX

#include <xsde/cxx/parser/non-validating/integer.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace non_validating
      {
        void integer_pimpl::
        _pre ()
        {
          size_ = 0;
          sign_ = none;
          state_ = leading_ws;
        }

        void integer_pimpl::
        _characters (const ro_string& s)
        {
          parse (s, str_, 20);
        }

        long integer_pimpl::
        post_integer ()
        {
          ro_string tmp (str_, size_);
          size_t size = trim_right (tmp);
          str_[size] = '\0';

          unsigned long ul = strtoul (str_, 0, 10);

          return (sign_ == minus)
            ? (ul == static_cast<unsigned long> (LONG_MIN)
               ? LONG_MIN : -static_cast<long> (ul))
            : static_cast<long> (ul);
        }
      }
    }
  }
}
