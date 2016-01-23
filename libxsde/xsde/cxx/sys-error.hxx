// file      : xsde/cxx/sys-error.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SYS_ERROR_HXX
#define XSDE_CXX_SYS_ERROR_HXX

namespace xsde
{
  namespace cxx
  {
    struct sys_error
    {
      enum value
      {
        none,
        no_memory,
        open_failed,
        read_failed,
        write_failed
      };

      sys_error (value);

      operator value () const
      {
        return v_;
      }

      static const char*
      text (value);

    private:
        value v_;
    };
  }
}

#include <xsde/cxx/sys-error.ixx>

#endif  // XSDE_CXX_SYS_ERROR_HXX
