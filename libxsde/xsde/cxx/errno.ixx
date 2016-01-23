// file      : xsde/cxx/errno.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/config.hxx>

#ifdef XSDE_PLATFORM_WINCE
#  include <winbase.h> // Get/SetLastError
#else
#  include <errno.h>
#endif

namespace xsde
{
  namespace cxx
  {
#ifdef XSDE_PLATFORM_WINCE
    inline int
    get_errno ()
    {
      return static_cast<int> (GetLastError ());
    }

    inline void
    set_errno (int e)
    {
      SetLastError (static_cast<DWORD> (e));
    }
#else
    inline int
    get_errno ()
    {
      return errno;
    }

    inline void
    set_errno (int e)
    {
      errno = e;
    }
#endif
  }
}
