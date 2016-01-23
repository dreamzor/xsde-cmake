// file      : xsde/cxx/parser/validating/short.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <stdlib.h> // strtoul

#include <xsde/cxx/parser/validating/short.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
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
          if (!parse (s, str_, 6))
            _schema_error (schema_error::invalid_short_value);
        }

        void short_pimpl::
        _post ()
        {
          ro_string tmp (str_, size_);
          size_t size = trim_right (tmp);

          if (size != 0 && tmp[0] != '-' && tmp[0] != '+')
          {
            str_[size] = '\0';

            // No need to check errno since our string representation
            // can never overflow an unsigned long.
            //
            char* p;
            unsigned long ul = strtoul (str_, &p, 10);

            bool neg = (sign_ == minus);

            if (*p != '\0' || (neg && ul > 32768) || (!neg && ul > 32767))
            {
              _schema_error (schema_error::invalid_short_value);
              return;
            }

            value_ = neg
              ? static_cast<short> (-static_cast<int> (ul))
              : static_cast<short> (ul);

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
            _schema_error (schema_error::invalid_short_value);
        }

        short short_pimpl::
        post_short ()
        {
          return value_;
        }
      }
    }
  }
}
