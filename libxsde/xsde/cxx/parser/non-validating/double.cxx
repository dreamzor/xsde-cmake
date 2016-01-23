// file      : xsde/cxx/parser/non-validating/double.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdlib.h> // strtod

#include <xsde/cxx/parser/non-validating/double.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace non_validating
      {
        void double_pimpl::
        _pre ()
        {
          size_ = 0;
          sign_ = none;
          state_ = leading_ws;
        }

        void double_pimpl::
        _characters (const ro_string& s)
        {
          parse (s, str_, 127);
        }

        double double_pimpl::
        post_double ()
        {
          ro_string tmp (str_, size_);
          size_t size = trim_right (tmp);
          str_[size] = '\0';

          double r;

          if (tmp == "INF")
          {
            r = strtod (sign_ == minus ? "-INF" : "INF", 0);
          }
          else if (tmp == "NaN")
          {
            r = strtod ("NAN", 0);
          }
          else
          {
            r = strtod (str_, 0);

            if (sign_ == minus)
              r = -r;
          }

          return r;
        }
      }
    }
  }
}
