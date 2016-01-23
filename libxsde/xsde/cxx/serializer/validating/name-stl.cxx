// file      : xsde/cxx/serializer/validating/name-stl.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/xml/char-table.hxx>

#include <xsde/cxx/serializer/validating/name-stl.hxx>
#include <xsde/cxx/serializer/validating/string-common.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
        void name_simpl::
        pre (const std::string& value)
        {
          value_ = value;
        }

        void name_simpl::
        _serialize_content ()
        {
          // Make sure we don't hold any references to the string.
          //
          std::string tmp;
          tmp.swap (value_);

          const char* s = tmp.c_str ();
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

          if (!ok)
          {
            _schema_error (schema_error::invalid_name_value);
            return;
          }

          if (!string_common::validate_facets (
                tmp.c_str (), tmp.size (), _facets (), _context ()))
            return;

          _characters (tmp.c_str (), tmp.size ());
        }
      }
    }
  }
}
