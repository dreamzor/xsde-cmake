// file      : xsde/cxx/hybrid/serializer-map.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_HYBRID_SERIALIZER_MAP_HXX
#define XSDE_CXX_HYBRID_SERIALIZER_MAP_HXX

#include <stddef.h> // size_t

#include <xsde/cxx/serializer/map.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace hybrid
    {
      class serializer_map_impl: public serializer::serializer_map
      {
      public:
        struct entry
        {
          const char* type_id;
          serializer::serializer_base* serializer;
        };

        serializer_map_impl (entry* entries, size_t size)
            : entries_ (entries), size_ (size), resetting_ (true)
        {
        }

        virtual serializer::serializer_base*
        find (const void* type_id) const;

        virtual void
        reset () const;

      private:
        serializer_map_impl (const serializer_map_impl&);
        serializer_map_impl& operator= (const serializer_map_impl&);

      private:
        entry* entries_;
        size_t size_;
        bool resetting_;
      };
    }
  }
}

#endif // XSDE_CXX_HYBRID_SERIALIZER_MAP_HXX
