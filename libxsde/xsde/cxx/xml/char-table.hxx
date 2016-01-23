// file      : xsde/cxx/xml/char-table.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_XML_CHAR_TABLE_HXX
#define XSDE_CXX_XML_CHAR_TABLE_HXX

namespace xsde
{
  namespace cxx
  {
    namespace xml
    {
      const unsigned char ncname_char_mask     = 0x1;
      const unsigned char name_first_char_mask = 0x2;
      const unsigned char name_char_mask       = 0x4;

      extern unsigned char char_table[0x80];
    }
  }
}

#endif  // XSDE_CXX_XML_CHAR_TABLE_HXX
