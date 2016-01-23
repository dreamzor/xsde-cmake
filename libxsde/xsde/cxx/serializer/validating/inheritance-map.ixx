// file      : xsde/cxx/serializer/validating/inheritance-map.ixx
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
        inline inheritance_map::
        inheritance_map (size_t buckets)
            : hashmap (buckets, sizeof (const char*))
        {
        }

        inline void inheritance_map::
        insert (const char* derived, const char* base)
        {
          hashmap::insert (derived, &base);
        }

        inline inheritance_map&
        inheritance_map_instance ()
        {
          return *inheritance_map_init::map;
        }
      }
    }
  }
}
