// file      : xsde/cxx/serializer/substitution-map-load.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_SUBSTITUTION_MAP_LOAD_HXX
#define XSDE_CXX_SERIALIZER_SUBSTITUTION_MAP_LOAD_HXX

#include <stddef.h> // size_t

#include <xsde/cxx/config.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      size_t
      serializer_smap_elements ();

      inline size_t
      serializer_smap_buckets ()
      {
        return XSDE_SERIALIZER_SMAP_BUCKETS;
      }

      size_t
      serializer_smap_bucket_elements ();

      inline size_t
      serializer_smap_bucket_buckets ()
      {
        return XSDE_SERIALIZER_SMAP_BUCKET_BUCKETS;
      }
    }
  }
}

#endif  // XSDE_CXX_SERIALIZER_SUBSTITUTION_MAP_LOAD_HXX
