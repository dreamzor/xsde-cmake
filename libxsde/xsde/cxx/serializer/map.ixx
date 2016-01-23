// file      : xsde/cxx/serializer/map.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
#ifndef XSDE_EXCEPTIONS
      inline serializer_map_impl::error serializer_map_impl::
      _error () const
      {
        return map_._error () ? error_no_memory : error_none;
      }
#endif

      inline serializer_map_impl::
      serializer_map_impl (size_t buckets)
          : map_ (buckets, sizeof (serializer_base*)), resetting_ (false)
      {
      }

      inline void serializer_map_impl::
      insert (const char* type_id, serializer_base& s)
      {
        serializer_base* tmp = &s;
        map_.insert (type_id, &tmp);
      }

      inline void serializer_map_impl::
      insert (serializer_base& s)
      {
        insert (s._dynamic_type (), s);
      }

      inline serializer_base* serializer_map_impl::
      find (const void* type_id) const
      {
        if (type_id)
        {
          const void* p = map_.find (static_cast<const char*> (type_id));
          return p ? *static_cast<serializer_base* const*> (p) : 0;
        }
        return 0;
      }
    }
  }
}
