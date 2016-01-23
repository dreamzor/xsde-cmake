// file      : xsde/cxx/allocator.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/config.hxx>
#include <xsde/cxx/allocator.hxx>

namespace xsde
{
  namespace cxx
  {
#ifdef XSDE_EXCEPTIONS
    void*
    alloc (size_t n)
    {
      void* p = xsde_alloc (n);

      if (p == 0)
        throw std::bad_alloc ();

      return p;
    }
#endif
  }
}
