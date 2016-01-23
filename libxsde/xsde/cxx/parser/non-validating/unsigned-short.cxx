// file      : xsde/cxx/parser/non-validating/unsigned-short.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdlib.h> // strtoul

#include <xsde/cxx/parser/non-validating/unsigned-short.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace non_validating
      {
        void unsigned_short_pimpl::
        _pre ()
        {
          size_ = 0;
          sign_ = none;
          state_ = leading_ws;
        }

        void unsigned_short_pimpl::
        _characters (const ro_string& s)
        {
          parse (s, str_, 6);
        }

        unsigned short unsigned_short_pimpl::
        post_unsigned_short ()
        {
          ro_string tmp (str_, size_);
          size_t size = trim_right (tmp);

          str_[size] = '\0';
          return static_cast<unsigned short> (strtoul (str_, 0, 10));
        }
      }
    }
  }
}
