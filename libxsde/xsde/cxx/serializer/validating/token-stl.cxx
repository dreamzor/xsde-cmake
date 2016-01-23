// file      : xsde/cxx/serializer/validating/token-stl.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/serializer/validating/token-stl.hxx>
#include <xsde/cxx/serializer/validating/string-common.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
        void token_simpl::
        pre (const std::string& value)
        {
          value_ = value;
        }

        void token_simpl::
        _serialize_content ()
        {
          // Make sure we don't hold any references to the string.
          //
          std::string tmp;
          tmp.swap (value_);

          bool ok = true;
          const char* s = tmp.c_str ();

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
          if (ok && s != tmp.c_str () && *(s - 1) == 0x20)
            ok = false;

          if (!ok)
          {
            _schema_error (schema_error::invalid_token_value);
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
