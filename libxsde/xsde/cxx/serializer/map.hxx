// file      : xsde/cxx/serializer/map.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_MAP_HXX
#define XSDE_CXX_SERIALIZER_MAP_HXX

#include <stddef.h> // size_t

#include <xsde/cxx/config.hxx>
#include <xsde/cxx/hashmap.hxx>

#include <xsde/cxx/serializer/elements.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      // Serializer map. Used in the polymorphic document parsing.
      //
      class serializer_map
      {
      public:
        // The type_id argument is the application-specific type id
        // object (passed as opaque const void*) that was set by the
        // callback in the context or 0 if no type id was provided.
        //
        virtual serializer_base*
        find (const void* type_id) const = 0;

        // Reset the serializers this map contains.
        //
        virtual void
        reset () const = 0;

        virtual
        ~serializer_map ();
      };

      // Default serializer map implementation. It assumes that the
      // type id is a C string (const char*).
      //
      class serializer_map_impl: public serializer_map
      {
      public:
#ifndef XSDE_EXCEPTIONS
        enum error
        {
          error_none,
          error_no_memory
        };

        error
        _error () const;
#endif

      public:
        serializer_map_impl (size_t buckets);

        // Note that the type_id string is not copied so it should
        // be valid for the lifetime of the map.
        //
        void
        insert (const char* type_id, serializer_base&);

        // This version of insert is a shortcut that uses the string
        // returned by the serializer's _dynamic_type() function.
        //
        void
        insert (serializer_base&);

        virtual serializer_base*
        find (const void* type_id) const;

        virtual void
        reset () const;

      private:
        serializer_map_impl (const serializer_map_impl&);

        serializer_map_impl&
        operator= (const serializer_map_impl&);

      private:
        hashmap map_;
        bool resetting_;
      };
    }
  }
}

#include <xsde/cxx/serializer/map.ixx>

#endif  // XSDE_CXX_SERIALIZER_MAP_HXX
