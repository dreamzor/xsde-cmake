// file      : xsde/cxx/sys-error.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/sys-error.hxx>

namespace xsde
{
  namespace cxx
  {
    static const char* const text_[] =
    {
      "no error",
      "no memory",
      "open failed",
      "read failed",
      "write failed"
    };

    const char* sys_error::
    text (value v)
    {
      return text_[v];
    }
  }
}
