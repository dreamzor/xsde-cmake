// file      : xsde/cxx/parser/validating/long.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdlib.h> // strtoul

#include <xsde/cxx/errno.hxx>

#include <xsde/cxx/parser/validating/long.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
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
          if (!parse (s, str_, 20))
            _schema_error (schema_error::invalid_long_value);
        }

        void long_pimpl::
        _post ()
        {
          ro_string tmp (str_, size_);
          size_t size = trim_right (tmp);

          if (size != 0 && tmp[0] != '-' && tmp[0] != '+')
          {
            str_[size] = '\0';

            char* p;
            set_errno (0);
            unsigned long ul = strtoul (str_, &p, 10);

            bool neg = (sign_ == minus);

            if (*p != '\0' ||
                get_errno () != 0 ||
                (neg && ul > 2147483648UL) ||
                (!neg && ul > 2147483647UL))
              _schema_error (schema_error::invalid_long_value);

            value_ = neg
              ? (ul == 2147483648UL
                 ? (-2147483647 - 1)
                 : -static_cast<long> (ul))
              : static_cast<long> (ul);

            // Check facets.
            //
            const facets& f = _facets ();

            if (f.min_set_ &&
                (value_ < f.min_ || (!f.min_inc_ && value_ == f.min_)))
            {
              _schema_error (schema_error::value_less_than_min);
              return;
            }

            if (f.max_set_ &&
                (value_ > f.max_ || (!f.max_inc_ && value_ == f.max_)))
            {
              _schema_error (schema_error::value_greater_than_max);
              return;
            }
          }
          else
            _schema_error (schema_error::invalid_long_value);
        }

        long long_pimpl::
        post_long ()
        {
          return value_;
        }
      }
    }
  }
}
