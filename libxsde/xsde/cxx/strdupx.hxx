// file      : xsde/cxx/strdupx.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_STRDUPX_HXX
#define XSDE_CXX_STRDUPX_HXX

#include <stddef.h> // size_t

namespace xsde
{
  namespace cxx
  {
    // C++ versions of strdup and strndup. They allocate the string
    // using new char[] (or custom allocator, if enabled). When
    // exceptions are disabled these functions return 0 if allocation
    // fails.
    //
    char*
    strdupx (const char*);

    char*
    strndupx (const char*, size_t);
  }
}

#endif  // XSDE_CXX_STRDUPX_HXX
