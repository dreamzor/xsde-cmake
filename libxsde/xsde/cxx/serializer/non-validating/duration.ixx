// file      : xsde/cxx/serializer/non-validating/duration.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace non_validating
      {
        inline duration_simpl::
        duration_simpl ()
            : value_ (false, 1, 0, 0, 0, 0, 0.0)
        {
        }
      }
    }
  }
}
