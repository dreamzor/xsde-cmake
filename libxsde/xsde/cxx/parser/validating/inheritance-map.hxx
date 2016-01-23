// file      : xsde/cxx/parser/validating/inheritance-map.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_VALIDATING_INHERITANCE_MAP_HXX
#define XSDE_CXX_PARSER_VALIDATING_INHERITANCE_MAP_HXX

#include <stddef.h> // size_t

#include <xsde/cxx/config.hxx>
#include <xsde/cxx/ro-string.hxx>
#include <xsde/cxx/hashmap.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
      {
        struct inheritance_map: hashmap
        {
          inheritance_map (size_t buckets);

          void
          insert (const char* derived, const char* base);

          bool
          check (const char* derived, const char* base) const;
        };


        // Translation unit initializer.
        //
        struct inheritance_map_init
        {
          static inheritance_map* map;
          static size_t count;

          inheritance_map_init ();
          ~inheritance_map_init ();
        };

        inline inheritance_map&
        inheritance_map_instance ();

        // Map entry initializer.
        //
        struct inheritance_map_entry
        {
          inheritance_map_entry (const char* derived, const char* base);
        };
      }
    }
  }
}

#include <xsde/cxx/parser/validating/inheritance-map.ixx>

#endif  // XSDE_CXX_PARSER_VALIDATING_INHERITANCE_MAP_HXX
