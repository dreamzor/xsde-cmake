// file      : xsde/cxx/serializer/substitution-map-callback.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_SUBSTITUTION_MAP_CALLBACK_HXX
#define XSDE_CXX_SERIALIZER_SUBSTITUTION_MAP_CALLBACK_HXX

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      void
      serializer_smap_callback (
        bool (*callback) (
          const char* type,
          const void* obj,
          const char*& ns,
          const char*& name));
    }
  }
}

#endif  // XSDE_CXX_SERIALIZER_SUBSTITUTION_MAP_CALLBACK_HXX
