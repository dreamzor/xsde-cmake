// file      : xsde/cxx/parser/map.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_MAP_HXX
#define XSDE_CXX_PARSER_MAP_HXX

#include <stddef.h> // size_t

#include <xsde/cxx/config.hxx>
#include <xsde/cxx/hashmap.hxx>

#include <xsde/cxx/parser/elements.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      // Parser map. Used in the polymorphic document parsing.
      //
      class parser_map
      {
      public:
        // The type argument is the type name and namespace from the
        // xsi:type attribute or substitution group map in the form
        // "<name> <namespace>" with the space and namespace part
        // absent if the type does not have a namespace.
        //
        virtual parser_base*
        find (const char* type) const = 0;

        // Reset the parsers this map contains.
        //
        virtual void
        reset () const = 0;

        virtual
        ~parser_map ();
      };

      // Default parser map implementation.
      //
      class parser_map_impl: public parser_map
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
        parser_map_impl (size_t buckets);

        void
        insert (parser_base&);

        virtual parser_base*
        find (const char* type) const;

        virtual void
        reset () const;

      private:
        parser_map_impl (const parser_map_impl&);

        parser_map_impl&
        operator= (const parser_map_impl&);

      private:
        hashmap map_;
        bool resetting_;
      };
    }
  }
}

#include <xsde/cxx/parser/map.ixx>

#endif  // XSDE_CXX_PARSER_MAP_HXX
