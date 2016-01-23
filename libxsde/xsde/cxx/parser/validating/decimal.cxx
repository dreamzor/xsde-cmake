// file      : xsde/cxx/parser/validating/decimal.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdlib.h> // strtod

#include <xsde/cxx/errno.hxx>

#include <xsde/cxx/parser/validating/decimal.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
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
          if (!parse (s, str_, 127))
            _schema_error (schema_error::invalid_decimal_value);
        }

        void decimal_pimpl::
        _post ()
        {
          ro_string tmp (str_, size_);
          size_t size = trim_right (tmp);

          if (size != 0 && tmp[0] != '-' && tmp[0] != '+')
          {
            str_[size] = '\0';

            if (tmp == "INF" || tmp == "NaN" || tmp == "NAN")
            {
              _schema_error (schema_error::invalid_decimal_value);
            }
            else
            {
              char* p;
              set_errno (0);
              value_ = strtod (str_, &p);

              if (*p != '\0' || get_errno () != 0)
                _schema_error (schema_error::invalid_decimal_value);

              if (sign_ == minus)
                value_ = -value_;
            }

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
            _schema_error (schema_error::invalid_decimal_value);
        }

        double decimal_pimpl::
        post_decimal ()
        {
          return value_;
        }
      }
    }
  }
}
