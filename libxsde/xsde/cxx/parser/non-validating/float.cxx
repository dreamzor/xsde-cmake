// file      : xsde/cxx/parser/non-validating/float.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdlib.h> // strtof, strtod

#include <xsde/cxx/config.hxx>

#include <xsde/cxx/parser/non-validating/float.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace non_validating
      {
        void float_pimpl::
        _pre ()
        {
          size_ = 0;
          sign_ = none;
          state_ = leading_ws;
        }

        void float_pimpl::
        _characters (const ro_string& s)
        {
          parse (s, str_, 127);
        }

        float float_pimpl::
        post_float ()
        {
          ro_string tmp (str_, size_);
          size_t size = trim_right (tmp);
          str_[size] = '\0';

          float r;

          if (tmp == "INF")
          {
#ifdef XSDE_STRTOF
            r = strtof (sign_ == minus ? "-INF" : "INF", 0);
#else
            r = static_cast<float> (strtod (sign_ == minus ? "-INF" : "INF", 0));
#endif
          }
          else if (tmp == "NaN")
          {
#ifdef XSDE_STRTOF
            r = strtof ("NAN", 0);
#else
            r = static_cast<float> (strtod ("NAN", 0));
#endif
          }
          else
          {
#ifdef XSDE_STRTOF
            r = strtof (str_, 0);
#else
            r = static_cast<float> (strtod (str_, 0));
#endif

            if (sign_ == minus)
              r = -r;
          }

          return r;
        }
      }
    }
  }
}
