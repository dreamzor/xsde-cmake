// file      : xsde/cxx/parser/validating/unsigned-long-long.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdlib.h> // strtoull

#include <xsde/cxx/errno.hxx>

#include <xsde/cxx/parser/validating/unsigned-long-long.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
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
          if (!parse (s, str_, 21))
            _schema_error (schema_error::invalid_unsigned_long_value);
        }

        void unsigned_long_pimpl::
        _post ()
        {
          ro_string tmp (str_, size_);
          size_t size = trim_right (tmp);

          if (size != 0 && sign_ != minus && tmp[0] != '-' && tmp[0] != '+')
          {
            str_[size] = '\0';

            char* p;
            set_errno (0);
            value_ = strtoull (str_, &p, 10);

            if (*p != '\0' || get_errno () != 0)
              _schema_error (schema_error::invalid_unsigned_long_value);

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
            _schema_error (schema_error::invalid_unsigned_long_value);
        }

        unsigned long long unsigned_long_pimpl::
        post_unsigned_long ()
        {
          return value_;
        }
      }
    }
  }
}
