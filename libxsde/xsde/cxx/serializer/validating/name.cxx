// file      : xsde/cxx/serializer/validating/name.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/xml/char-table.hxx>

#include <xsde/cxx/serializer/validating/name.hxx>
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
        name_simpl::
        ~name_simpl ()
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

        void name_simpl::
        pre (const char* value)
        {
          value_ = value;
        }

        void name_simpl::
        _serialize_content ()
        {
          const char* s = value_;
          bool ok = (*s != '\0');

          // For now we are only checking the US-ASCII characters.
          //
          if (ok)
          {
            // First character.
            //
            unsigned char c = static_cast<unsigned char> (*s);

            ok = c >= 0x80 || (xml::char_table[c] & xml::name_first_char_mask);

            for (++s; ok && *s != '\0'; ++s)
            {
              c = static_cast<unsigned char> (*s);

              if (c < 0x80 && !(xml::char_table[c] & xml::name_char_mask))
                ok = false;
            }
          }

          if (ok)
          {
            if (string_common::validate_facets (
                  value_, _facets (), _context ()))
            {
              _characters (value_);
            }
          }
          else
            _schema_error (schema_error::invalid_name_value);

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
