// file      : xsde/cxx/iso8859-1.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_ISO8859_1_HXX
#define XSDE_CXX_ISO8859_1_HXX

#include <stddef.h> // size_t

#include <xsde/cxx/config.hxx>

namespace xsde
{
  namespace cxx
  {
    class iso8859_1
    {
    public:
      // Get/set a replacement for unrepresentable characters. If set to
      // 0 (the default value), the conversion fails if such a character
      // is encountered.
      //
      static char
      unrep_char ()
      {
        return unrep_char_;
      }

      static void
      unrep_char (char c)
      {
        unrep_char_ = c;
      }

    public:
      // Test whether a UTF-8 string is an ASCII string. If these
      // functions return false, the iso_size argument contains
      // the size of the buffer needed to convert this string to
      // ISO-8859-1.
      //
      static bool
      ascii_utf (const char* utf_str, size_t& iso_size);

      static bool
      ascii_utf (const char* utf_str, size_t utf_size, size_t& iso_size);

      // Test whether an ISO-8859-1 string is an ASCII string. If
      // these functions return false, the utf_size argument contains
      // the size of the buffer needed to convert this string to UTF-8.
      //
      static bool
      ascii_iso (const char* iso_str, size_t& utf_size);

      static bool
      ascii_iso (const char* iso_str, size_t iso_size, size_t& utf_size);

      // Convert from UTF-8 to ISO-8859-1. Return false if an
      // unrepresentable character was encountered and no replacement
      // was specified.
      //
      //
      static bool
      to (const char* utf_str, char* iso_str);

      static bool
      to (const char* utf_str, size_t utf_size, char* iso_str);

      // Convert from ISO-8859-1 to UTF-8.
      //
      static void
      from (const char* iso_str, char* utf_str);

      static void
      from (const char* iso_str, size_t iso_size, char* utf_str);

    private:
      static char unrep_char_;
    };
  }
}

#include <xsde/cxx/iso8859-1.ixx>

#endif  // XSDE_CXX_ISO8859_1_HXX
