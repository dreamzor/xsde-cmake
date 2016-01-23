// file      : xsde/cxx/parser/map.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
#ifndef XSDE_EXCEPTIONS
      inline parser_map_impl::error parser_map_impl::
      _error () const
      {
        return map_._error () ? error_no_memory : error_none;
      }
#endif

      inline parser_map_impl::
      parser_map_impl (size_t buckets)
          : map_ (buckets, sizeof (parser_base*)), resetting_ (false)
      {
      }

      inline void parser_map_impl::
      insert (parser_base& p)
      {
        parser_base* tmp = &p;
        map_.insert (p._dynamic_type (), &tmp);
      }

      inline parser_base* parser_map_impl::
      find (const char* type) const
      {
        const void* p = map_.find (type);
        return p ? *static_cast<parser_base* const*> (p) : 0;
      }
    }
  }
}
