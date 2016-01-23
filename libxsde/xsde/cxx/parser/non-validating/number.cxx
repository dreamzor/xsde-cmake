// file      : xsde/cxx/parser/non-validating/number.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <string.h> // memcpy

#include <xsde/cxx/parser/non-validating/number.hxx>

using xsde::cxx::ro_string;

static bool
trim_leading_zeros (ro_string& s)
{
  ro_string::size_type size = s.size ();

  if (size != 0)
  {
    const char* f = s.data ();
    const char* l = f + size;
    const char* of = f;

    while (f < l && *f == '0')
      ++f;

    if (f != of)
    {
      s.assign ((f <= l ? f : 0), (f <= l ? l - f : 0));
      return true;
    }
  }

  return false;
}

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace non_validating
      {
        void number::
        parse (const ro_string& s, char* str, size_t max)
        {
          ro_string tmp (s.data (), s.size ());
          size_t size = tmp.size ();

          switch (state_)
          {
          case leading_ws:
            {
              size = trim_left (tmp);

              if (size != 0)
                state_ = sign;
              else
                break;
              // Fall through.
            }
          case sign:
            {
              if (tmp[0] == '-')
                sign_ = minus;
              else if (tmp[0] == '+')
                sign_ = plus;

              if (sign_ != none)
                tmp.assign (tmp.data () + 1, --size);

              if (size != 0)
                state_ = leading_zeros;
              else
                break;

              // Fall through.
            }
          case leading_zeros:
            {
              if (trim_leading_zeros (tmp))
              {
                if (size_ == 0)
                {
                  str[0] = '0';
                  size_ = 1;
                }

                size = tmp.size ();
              }

              if (size != 0)
                state_ = literal;
              else
                break;
              // Fall through.
            }
          case literal:
            {
              // If this chunk is too long then it has to be the last so trim
              // trailing ws.
              //
              if ((max - size_) < size)
              {
                size = trim_right (tmp);
                state_ = trailing_ws; // It either had ws or is too large.
              }

              if ((max - size_) >= size)
              {
                memcpy (str + size_, tmp.data (), size);
                size_ += size;
              }

              break;
            }
          case trailing_ws:
            {
              // We don't really care if it is not.
              break;
            }
          }
        }
      }
    }
  }
}
