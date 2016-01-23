// file      : xsde/cxx/hybrid/parser-map.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_HYBRID_PARSER_MAP_HXX
#define XSDE_CXX_HYBRID_PARSER_MAP_HXX

#include <stddef.h> // size_t

#include <xsde/cxx/parser/map.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace hybrid
    {
      class parser_map_impl: public parser::parser_map
      {
      public:
        struct entry
        {
          const char* type_id;
          parser::parser_base* parser;
        };

        parser_map_impl (entry* entries, size_t size)
            : entries_ (entries), size_ (size), resetting_ (false)
        {
        }

        virtual parser::parser_base*
        find (const char* type_id) const;

        virtual void
        reset () const;

      private:
        parser_map_impl (const parser_map_impl&);
        parser_map_impl& operator= (const parser_map_impl&);

      private:
        entry* entries_;
        size_t size_;
        bool resetting_;
      };
    }
  }
}

#endif // XSDE_CXX_HYBRID_PARSER_MAP_HXX
