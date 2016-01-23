// file      : xsde/cxx/serializer/validating/date-time.ixx
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
        inline date_time_simpl::
        date_time_simpl ()
            : value_ (1, 0, 0, 0, 0, 0.0)
        {
        }
      }
    }
  }
}
