// file      : xsde/cxx/iso8859-1.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsde
{
  namespace cxx
  {
    inline bool iso8859_1::
    ascii_utf (const char* s, size_t& rn)
    {
      // NULL string is an ASCII string.
      //
      if (s == 0)
        return true;

      bool r = true;
      size_t l = 0;

      for (; *s != 0; ++s, ++l)
      {
        unsigned char c = *s;

        if (c > 0x7F)
        {
          if ((c >> 5) == 0x06)
            ++s;
          else if ((c >> 4) == 0x0E)
            s += 2;
          else if ((c >> 3) == 0x1E)
            s += 3;

          r = false;
        }
      }

      rn = l + 1;
      return r;
    }

    inline bool iso8859_1::
    ascii_utf (const char* s, size_t n, size_t& rn)
    {
      // NULL string is an ASCII string.
      //
      if (s == 0)
        return true;

      bool r = true;
      size_t l = 0;
      const char* end = s + n;

      for (; s != end; ++s, ++l)
      {
        unsigned char c = *s;

        if (c > 0x7F)
        {
          if ((c >> 5) == 0x06)
            ++s;
          else if ((c >> 4) == 0x0E)
            s += 2;
          else if ((c >> 3) == 0x1E)
            s += 3;

          r = false;
        }
      }

      rn = l + 1;
      return r;
    }

    inline bool iso8859_1::
    ascii_iso (const char* s, size_t& rn)
    {
      // NULL string is an ASCII string.
      //
      if (s == 0)
        return true;

      bool r = true;
      size_t l = 0;

      for (; *s != 0; ++s, ++l)
      {
        unsigned char c = *s;

        if (c > 0x7F)
        {
          ++l; // 2-byte surrogate.
          r = false;
        }
      }

      rn = l + 1;
      return r;
    }

    inline bool iso8859_1::
    ascii_iso (const char* s, size_t n, size_t& rn)
    {
      // NULL string is an ASCII string.
      //
      if (s == 0)
        return true;

      bool r = true;
      size_t l = 0;
      const char* end = s + n;

      for (; s != end; ++s, ++l)
      {
        unsigned char c = *s;

        if (c > 0x7F)
        {
          ++l; // 2-byte surrogate.
          r = false;
        }
      }

      rn = l + 1;
      return r;
    }
  }
}
