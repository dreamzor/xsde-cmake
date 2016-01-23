// file      : xsde/cxx/parser/non-validating/short.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdlib.h> // strtoul

#include <xsde/cxx/parser/non-validating/short.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace non_validating
      {
        void short_pimpl::
        _pre ()
        {
          size_ = 0;
          sign_ = none;
          state_ = leading_ws;
        }

        void short_pimpl::
        _characters (const ro_string& s)
        {
          parse (s, str_, 6);
        }

        short short_pimpl::
        post_short ()
        {
          ro_string tmp (str_, size_);
          size_t size = trim_right (tmp);

          str_[size] = '\0';
          unsigned long ul = strtoul (str_, 0, 10);

          return (sign_ == minus)
            ? static_cast<short> (-static_cast<int> (ul))
            : static_cast<short> (ul);
        }
      }
    }
  }
}
