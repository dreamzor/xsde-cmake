// file      : xsde/cxx/serializer/validating/string-stl.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/serializer/validating/string-stl.hxx>
#include <xsde/cxx/serializer/validating/string-common.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
        void string_simpl::
        pre (const std::string& value)
        {
          value_ = value;
        }

        void string_simpl::
        _serialize_content ()
        {
          // Make sure we don't hold any references to the string.
          //
          std::string tmp;
          tmp.swap (value_);

          if (string_common::validate_facets (
                tmp.c_str (), tmp.size (), _facets (), _context ()))
          {
            _characters (tmp.c_str (), tmp.size ());
          }
        }
      }
    }
  }
}
