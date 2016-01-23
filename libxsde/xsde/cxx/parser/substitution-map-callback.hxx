// file      : xsde/cxx/parser/substitution-map-callback.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_SUBSTITUTION_MAP_CALLBACK_HXX
#define XSDE_CXX_PARSER_SUBSTITUTION_MAP_CALLBACK_HXX

#include <xsde/cxx/ro-string.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      void
      parser_smap_callback (
        bool (*callback) (
          const ro_string& root_ns,
          const ro_string& root_name,
          const ro_string& member_ns,
          const ro_string& member_name,
          const char*& type));
    }
  }
}

#endif  // XSDE_CXX_PARSER_SUBSTITUTION_MAP_CALLBACK_HXX
