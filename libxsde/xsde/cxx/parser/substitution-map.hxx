// file      : xsde/cxx/parser/substitution-map.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_SUBSTITUTION_MAP_HXX
#define XSDE_CXX_PARSER_SUBSTITUTION_MAP_HXX

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
      struct substitution_map: hashmap
      {
        substitution_map (size_t buckets);

        void
        insert (const char* member,
                const char* root,
                const char* type);

        typedef bool (*callback_func) (
          const ro_string& root_ns,
          const ro_string& root_name,
          const ro_string& member_ns,
          const ro_string& member_name,
          const char*& type);

        void
        callback (callback_func);

        // Check and have the type set if found.
        //
        bool
        check (const ro_string& member_ns,
               const ro_string& member_name,
               const char* root,
               const char*& type) const;

        bool
        check (const ro_string& member_ns,
               const ro_string& member_name,
               const char* root_ns, // 0 if no namespace
               const char* root_name,
               const char*& type) const;

        // Check but don't care about the type.
        //
        bool
        check (const ro_string& member_ns,
               const ro_string& member_name,
               const char* root) const;

      private:
        struct value
        {
          const char* root_;
          const char* type_;
        };

      private:
        bool
        check_ (const ro_string& member_ns,
                const ro_string& member_name,
                const char* root,
                const char** type) const;

        bool
        check_ (const ro_string& member_ns,
                const ro_string& member_name,
                const char* root_ns,
                const char* root_name,
                const char** type) const;

        bool
        check_ (const char* member, const char* root) const;

        bool
        check_ (const char* member,
                const char* root_ns,
                const char* root_name) const;

        const value*
        find_ (const ro_string& member_ns,
               const ro_string& member_name) const;

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
        substitution_map_entry (const char* member,
                                const char* root,
                                const char* type);
      };
    }
  }
}

#include <xsde/cxx/parser/substitution-map.ixx>

#endif  // XSDE_CXX_PARSER_SUBSTITUTION_MAP_HXX
