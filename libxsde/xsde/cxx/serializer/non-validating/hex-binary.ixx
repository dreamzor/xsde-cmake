// file      : xsde/cxx/serializer/non-validating/hex-binary.ixx
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
        inline hex_binary_simpl::
        hex_binary_simpl (bool free)
            : free_ (free), value_ (0)
        {
        }
      }
    }
  }
}
