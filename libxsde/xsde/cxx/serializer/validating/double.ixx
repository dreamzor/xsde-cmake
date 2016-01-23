// file      : xsde/cxx/serializer/validating/double.ixx
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
        inline double_simpl::
        double_simpl (notation n, unsigned int p)
            : notation_ (n), precision_ (p)
        {
        }
      }
    }
  }
}
