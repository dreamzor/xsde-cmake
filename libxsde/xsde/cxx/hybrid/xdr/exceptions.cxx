// file      : xsde/cxx/hybrid/xdr/exceptions.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/hybrid/xdr/exceptions.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace hybrid
    {
      const char* xdr_exception::
      what () const throw ()
      {
        return "XDR stream operation failed";
      }
    }
  }
}
