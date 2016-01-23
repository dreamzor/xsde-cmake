// file      : xsde/cxx/string-search.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_STRING_SEARCH_HXX
#define XSDE_CXX_STRING_SEARCH_HXX

#include <stddef.h> // size_t

namespace xsde
{
  namespace cxx
  {
    // Binary search in a sorted string array. Return size if no
    // element found.
    //
    size_t
    search (const char* const* array, size_t size, const char* s);
  }
}

#endif // XSDE_CXX_STRING_SEARCH_HXX
