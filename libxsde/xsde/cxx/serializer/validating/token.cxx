// file      : xsde/cxx/serializer/validating/token.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/serializer/validating/token.hxx>
#include <xsde/cxx/serializer/validating/string-common.hxx>

#ifdef XSDE_CUSTOM_ALLOCATOR
#  include <xsde/cxx/allocator.hxx>
#endif

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
        token_simpl::
        ~token_simpl ()
        {
          if (free_ && value_)
          {
            char* v = const_cast<char*> (value_);
#ifndef XSDE_CUSTOM_ALLOCATOR
            delete[] v;
#else
            cxx::free (v);
#endif
          }
        }

        void token_simpl::
        pre (const char* value)
        {
          value_ = value;
        }

        void token_simpl::
        _serialize_content ()
        {
          bool ok = true;
          const char* s = value_;

          // No leading whitespaces.
          //
          if (*s == 0x20)
            ok = false;

          for (; ok && *s != '\0'; ++s)
          {
            if (*s == 0x0A || *s == 0x0D || *s == 0x09 ||
                (*s == 0x20 && *(s + 1) == 0x20))
              ok = false;
          }

          // No trailing whitespaces.
          //
          if (ok && s != value_ && *(s - 1) == 0x20)
            ok = false;

          if (ok)
          {
            if (string_common::validate_facets (
                  value_, _facets (), _context ()))
            {
              _characters (value_);
            }
          }
          else
            _schema_error (schema_error::invalid_token_value);

          if (free_)
          {
            char* v = const_cast<char*> (value_);
#ifndef XSDE_CUSTOM_ALLOCATOR
            delete[] v;
#else
            cxx::free (v);
#endif
            value_ = 0;
          }
        }
      }
    }
  }
}
