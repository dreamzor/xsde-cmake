// file      : xsde/cxx/xml/ncname.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/xml/char-table.hxx>
#include <xsde/cxx/xml/ncname.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace xml
    {
      bool
      valid_ncname (const char* s, size_t size)
      {
        // For now we are only checking the US-ASCII characters.
        //

        bool ok = (size != 0);

        if (ok)
        {
          unsigned char c = static_cast<unsigned char> (s[0]);

          ok = c >= 0x80 ||
            ((char_table[c] & name_first_char_mask) && c != ':');

          for (size_t i = 1; ok && i < size; ++i)
          {
            c = static_cast<unsigned char> (s[i]);

            if (c < 0x80 && !(xml::char_table[c] & xml::ncname_char_mask))
              ok = false;
          }
        }

        return ok;
      }
    }
  }
}
