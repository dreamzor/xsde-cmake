// file      : xsde/cxx/serializer/validating/any-simple-type-stl.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/serializer/validating/any-simple-type-stl.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
        void any_simple_type_simpl::
        pre (const std::string& value)
        {
          value_ = value;
        }

        void any_simple_type_simpl::
        _serialize_content ()
        {
          // Make sure we don't hold any references to the string.
          //
          std::string tmp;
          tmp.swap (value_);
          _characters (tmp.c_str (), tmp.size ());
        }
      }
    }
  }
}
