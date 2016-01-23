// file      : xsde/cxx/serializer/map.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/serializer/map.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      // serializer_map
      //
      serializer_map::
      ~serializer_map ()
      {
      }

      // serializer_map_impl
      //
      void serializer_map_impl::
      reset () const
      {
        if (resetting_)
          return;

        bool& r = const_cast<bool&> (resetting_);
        r = true;

        for (hashmap::const_iterator i (map_.begin ()), e (map_.end ());
             i != e; ++i)
        {
          serializer_base* s = *static_cast<serializer_base* const*> (*i);
          s->_reset ();
        }

        r = false;
      }
    }
  }
}
