// file      : xsde/cxx/parser/non-validating/boolean.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/parser/non-validating/boolean.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace non_validating
      {
        void boolean_pimpl::
        _pre ()
        {
          size_ = 0;
          state_ = leading_ws;
        }

        void boolean_pimpl::
        _characters (const ro_string& s)
        {
          ro_string tmp (s.data (), s.size ());

          size_t size = tmp.size ();

          switch (state_)
          {
          case leading_ws:
            {
              size = trim_left (tmp);

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
              if ((5 - size_) < size)
              {
                size = trim_right (tmp);
                state_ = trailing_ws; // It either had ws or is too large.
              }

              if ((5 - size_) >= size)
              {
                memcpy (str_ + size_, tmp.data (), size);
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

        bool boolean_pimpl::
        post_boolean ()
        {
          ro_string tmp (str_, size_);
          trim_right (tmp);

          return (tmp == "1" || tmp == "true");
        }
      }
    }
  }
}
