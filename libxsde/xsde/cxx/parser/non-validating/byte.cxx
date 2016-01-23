// file      : xsde/cxx/parser/non-validating/byte.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdlib.h> // strtoul

#include <xsde/cxx/parser/non-validating/byte.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace non_validating
      {
        void byte_pimpl::
        _pre ()
        {
          size_ = 0;
          sign_ = none;
          state_ = leading_ws;
        }

        void byte_pimpl::
        _characters (const ro_string& s)
        {
          parse (s, str_, 4);
        }

        signed char byte_pimpl::
        post_byte ()
        {
          ro_string tmp (str_, size_);
          size_t size = trim_right (tmp);

          str_[size] = '\0';
          unsigned long ul = strtoul (str_, 0, 10);

          return (sign_ == minus)
            ? static_cast<signed char> (-static_cast<short> (ul))
            : static_cast<signed char> (ul);
        }
      }
    }
  }
}
