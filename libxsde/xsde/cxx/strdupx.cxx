// file      : xsde/cxx/strdupx.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <string.h> // strlen, memcpy

#include <xsde/cxx/config.hxx>
#include <xsde/cxx/strdupx.hxx>

#ifdef XSDE_CUSTOM_ALLOCATOR
#  include <xsde/cxx/allocator.hxx>
#endif

namespace xsde
{
  namespace cxx
  {
    char*
    strdupx (const char* s)
    {
      size_t n = strlen (s);

#ifndef XSDE_CUSTOM_ALLOCATOR
      char* r = new char[n + 1];
#else
      char* r = static_cast<char*> (alloc (n + 1));
#endif

#ifndef XSDE_EXCEPTIONS
      if (r)
#endif
        memcpy (r, s, n + 1);

      return r;
    }

    char*
    strndupx (const char* s, size_t n)
    {
#ifndef XSDE_CUSTOM_ALLOCATOR
      char* r = new char[n + 1];
#else
      char* r = static_cast<char*> (alloc (n + 1));
#endif

#ifndef XSDE_EXCEPTIONS
      if (r)
      {
#endif
        memcpy (r, s, n);
        r[n] = '\0';

#ifndef XSDE_EXCEPTIONS
      }
#endif

      return r;
    }
  }
}
