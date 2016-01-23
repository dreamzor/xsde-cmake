// file      : xsde/cxx/serializer/validating/normalized-string.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/serializer/validating/normalized-string.hxx>
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
        normalized_string_simpl::
        ~normalized_string_simpl ()
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

        void normalized_string_simpl::
        pre (const char* value)
        {
          value_ = value;
        }

        void normalized_string_simpl::
        _serialize_content ()
        {
          const char* s = value_;

          for (; *s != '\0'; ++s)
          {
            if (*s == 0x0A || *s == 0x0D || *s == 0x09)
              break;
          }

          if (*s == '\0')
          {
            if (string_common::validate_facets (
                  value_, _facets (), _context ()))
            {
              _characters (value_);
            }
          }
          else
            _schema_error (schema_error::invalid_normalized_string_value);

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
