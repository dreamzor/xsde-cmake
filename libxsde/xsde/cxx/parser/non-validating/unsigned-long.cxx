// file      : xsde/cxx/parser/non-validating/unsigned-long.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdlib.h> // strtoul

#include <xsde/cxx/parser/non-validating/unsigned-long.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace non_validating
      {
        void unsigned_long_pimpl::
        _pre ()
        {
          size_ = 0;
          sign_ = none;
          state_ = leading_ws;
        }

        void unsigned_long_pimpl::
        _characters (const ro_string& s)
        {
          parse (s, str_, 21);
        }

        unsigned long unsigned_long_pimpl::
        post_unsigned_long ()
        {
          ro_string tmp (str_, size_);
          size_t size = trim_right (tmp);
          str_[size] = '\0';

          return strtoul (str_, 0, 10);
        }
      }
    }
  }
}
