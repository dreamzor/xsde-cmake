// file      : xsde/cxx/parser/non-validating/decimal.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdlib.h> // strtod

#include <xsde/cxx/parser/non-validating/decimal.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace non_validating
      {
        void decimal_pimpl::
        _pre ()
        {
          size_ = 0;
          sign_ = none;
          state_ = leading_ws;
        }

        void decimal_pimpl::
        _characters (const ro_string& s)
        {
          parse (s, str_, 127);
        }

        double decimal_pimpl::
        post_decimal ()
        {
          ro_string tmp (str_, size_);
          size_t size = trim_right (tmp);
          str_[size] = '\0';

          double r = strtod (str_, 0);

          if (sign_ == minus)
            r = -r;

          return r;
        }
      }
    }
  }
}
