// file      : xsde/cxx/parser/validating/non-positive-integer.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdlib.h> // strtoul
#include <limits.h> // LONG_MIN

#include <xsde/cxx/errno.hxx>

#include <xsde/cxx/parser/validating/non-positive-integer.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
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
          if (!parse (s, str_, 20))
            _schema_error (schema_error::invalid_non_positive_integer_value);
        }

        void non_positive_integer_pimpl::
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

            if (*p != '\0' ||
                get_errno () != 0 ||
                (sign_ != minus && ul != 0) ||
                ul > static_cast<unsigned long> (LONG_MIN))
              _schema_error (schema_error::invalid_non_positive_integer_value);

            value_ = ul == static_cast<unsigned long> (LONG_MIN)
              ? LONG_MIN : -static_cast<long> (ul);

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
            _schema_error (schema_error::invalid_non_positive_integer_value);
        }

        long non_positive_integer_pimpl::
        post_non_positive_integer ()
        {
          return value_;
        }
      }
    }
  }
}
