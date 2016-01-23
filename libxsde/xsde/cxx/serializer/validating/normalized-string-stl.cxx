// file      : xsde/cxx/serializer/validating/normalized-string-stl.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/serializer/validating/normalized-string-stl.hxx>
#include <xsde/cxx/serializer/validating/string-common.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
        void normalized_string_simpl::
        pre (const std::string& value)
        {
          value_ = value;
        }

        void normalized_string_simpl::
        _serialize_content ()
        {
          // Make sure we don't hold any references to the string.
          //
          std::string tmp;
          tmp.swap (value_);

          const char* s = tmp.c_str ();

          for (; *s != '\0'; ++s)
          {
            if (*s == 0x0A || *s == 0x0D || *s == 0x09)
              break;
          }

          if (*s != '\0')
          {
            _schema_error (schema_error::invalid_normalized_string_value);
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
