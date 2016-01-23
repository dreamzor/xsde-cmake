// file      : xsde/cxx/serializer/non-validating/boolean.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/serializer/non-validating/boolean.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace non_validating
      {
        void boolean_simpl::
        pre (bool value)
        {
          value_ = value;
        }

        void boolean_simpl::
        _serialize_content ()
        {
          _characters ((value_ ? "true" : "false"), (value_ ? 4 : 5));
        }
      }
    }
  }
}
