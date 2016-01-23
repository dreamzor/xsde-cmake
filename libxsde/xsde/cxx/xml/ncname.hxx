// file      : xsde/cxx/xml/ncname.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_XML_NCNAME_HXX
#define XSDE_CXX_XML_NCNAME_HXX

#include <stddef.h> // size_t

namespace xsde
{
  namespace cxx
  {
    namespace xml
    {
      bool
      valid_ncname (const char* s, size_t size);
    }
  }
}

#endif // XSDE_CXX_XML_NCNAME_HXX
