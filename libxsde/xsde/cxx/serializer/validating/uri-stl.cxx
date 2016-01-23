// file      : xsde/cxx/serializer/validating/uri-stl.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/serializer/validating/uri-stl.hxx>
#include <xsde/cxx/serializer/validating/string-common.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
        void uri_simpl::
        pre (const std::string& value)
        {
          value_ = value;
        }

        void uri_simpl::
        _serialize_content ()
        {
          // Make sure we don't hold any references to the string.
          //
          std::string tmp;
          tmp.swap (value_);

          // According to Datatypes 3.2.17 and RFC2396 pretty much anything
          // can be a URI and conforming processors do not need to figure
          // out and verify particular URI schemes.
          //
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
