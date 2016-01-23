// file      : xsde/cxx/serializer/validating/language-stl.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/serializer/validating/language-stl.hxx>
#include <xsde/cxx/serializer/validating/string-common.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
        void language_simpl::
        pre (const std::string& value)
        {
          value_ = value;
        }

        void language_simpl::
        _serialize_content ()
        {
          // Make sure we don't hold any references to the string.
          //
          std::string tmp;
          tmp.swap (value_);

          bool ok = true;
          const char* s = tmp.c_str ();

          // language := ALPHA{1,8} *(-(ALPHA | DIGIT){1,8})
          //
          for (size_t tag = 0; ; ++tag)
          {
            size_t n = 0;

            for (; *s != '\0' && n < 8; ++n, ++s)
            {
              char c = *s;

              if (!((c >= 'a' && c <= 'z') ||
                    (c >= 'A' && c <= 'Z') ||
                    (tag != 0 && c >= '0' && c <= '9')))
                break;
            }

            if (n == 0)
            {
              ok = false;
              break;
            }

            if (*s == '\0')
              break;

            if (*s++ != '-')
            {
              ok = false;
              break;
            }
          }

          if (!ok)
          {
            _schema_error (schema_error::invalid_language_value);
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
