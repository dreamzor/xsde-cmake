// file      : xsde/cxx/serializer/validating/nmtokens.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
        inline nmtokens_simpl::
        nmtokens_simpl (bool free)
            : free_ (free), value_ (0), serializer_ (false)
        {
        }
      }
    }
  }
}
