// file      : xsde/cxx/parser/substitution-map-load.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_SUBSTITUTION_MAP_LOAD_HXX
#define XSDE_CXX_PARSER_SUBSTITUTION_MAP_LOAD_HXX

#include <stddef.h> // size_t

#include <xsde/cxx/config.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      size_t
      parser_smap_elements ();

      inline size_t
      parser_smap_buckets ()
      {
        return XSDE_PARSER_SMAP_BUCKETS;
      }
    }
  }
}

#endif  // XSDE_CXX_PARSER_SUBSTITUTION_MAP_LOAD_HXX
