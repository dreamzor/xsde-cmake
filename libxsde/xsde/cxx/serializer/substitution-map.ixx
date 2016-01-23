// file      : xsde/cxx/serializer/substitution-map.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      inline substitution_map::
      substitution_map (size_t buckets)
          : hashmap (buckets, sizeof (hashmap*)), callback_ (0)
      {
      }

      inline void substitution_map::
      callback (callback_func c)
      {
        callback_ = c;
      }

      inline bool substitution_map::
      check (const char*& ns,
             const char*& name,
             const char* type,
             const void* obj) const
      {
        return !empty () || callback_ != 0
          ? check_ (ns, name, type, obj, true)
          : false;
      }

      inline substitution_map&
      substitution_map_instance ()
      {
        return *substitution_map_init::map;
      }
    }
  }
}
