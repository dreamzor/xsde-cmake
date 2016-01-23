// file      : xsde/cxx/serializer/substitution-map.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_SUBSTITUTION_MAP_HXX
#define XSDE_CXX_SERIALIZER_SUBSTITUTION_MAP_HXX

#include <stddef.h> // size_t

#include <xsde/cxx/config.hxx>
#include <xsde/cxx/ro-string.hxx>
#include <xsde/cxx/hashmap.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      struct substitution_map: hashmap
      {
        ~substitution_map ();

        substitution_map (size_t buckets);

        void
        insert (const char* root,
                const char* member_ns,
                const char* member_name,
                const char* member_type);

        typedef bool (*callback_func) (
          const char* type,
          const void* obj,
          const char*& ns,
          const char*& name);

        void
        callback (callback_func);

        // Check whether there is a substitution available for this
        // root element with the specified type. If so, return true
        // and override namespace and name (ns is 0 if there is no
        // namespace). The obj argument is an opaque pointer to the
        // instance being serialized or 0 if there is none.
        //
        bool
        check (const char*& ns,
               const char*& name,
               const char* type,
               const void* obj) const;

      private:
        bool
        check_ (const char*& ns,
                const char*& name,
                const char* type,
                const void* obj,
                bool top) const;

      private:
        struct value
        {
          const char* ns_;
          const char* name_;
        };

      private:
        callback_func callback_;
      };


      // Translation unit initializer.
      //
      struct substitution_map_init
      {
        static substitution_map* map;
        static size_t count;

        substitution_map_init ();
        ~substitution_map_init ();
      };

      substitution_map&
      substitution_map_instance ();

      // Map entry initializer.
      //
      struct substitution_map_entry
      {
        substitution_map_entry (const char* root,
                                const char* member_ns,
                                const char* member_name,
                                const char* member_type);
      };
    }
  }
}

#include <xsde/cxx/serializer/substitution-map.ixx>

#endif  // XSDE_CXX_SERIALIZER_SUBSTITUTION_MAP_HXX
