// file      : xsde/cxx/string-search.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <string.h> // strcmp
#include <xsde/cxx/string-search.hxx>

namespace xsde
{
  namespace cxx
  {
    size_t
    search (const char* const* array, size_t size, const char* s)
    {
      if (size == 0)
        return 0;

      int r = 1;
      size_t m = 0;
      size_t l = 0;
      size_t h = size - 1;

      while (l <= h)
      {
        m = l + (h - l) / 2;

        r = strcmp (array[m], s);

        if (r == 0 || l == h)
          break;

        if (r < 0)
          l = m + 1;
        else
          h = (m == 0 ? 0 : m - 1);
      }

      return r == 0 ? m : size;
    }
  }
}
