// file      : xsde/cxx/errno.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_ERRNO_HXX
#define XSDE_CXX_ERRNO_HXX

namespace xsde
{
  namespace cxx
  {
    int
    get_errno ();

    void
    set_errno (int);
  }
}

#include <xsde/cxx/errno.ixx>

#endif // XSDE_CXX_ERRNO_HXX
