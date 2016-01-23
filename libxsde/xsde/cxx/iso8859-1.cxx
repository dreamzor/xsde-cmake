// file      : xsde/cxx/iso8859-1.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/iso8859-1.hxx>

namespace xsde
{
  namespace cxx
  {
    char iso8859_1::unrep_char_ = '\0';

    bool iso8859_1::
    to (const char* s, char* r)
    {
      for (; *s != 0; ++s)
      {
        unsigned char c = *s;

        if (c < 0x80)
        {
          // Fast path.
          //
          *r++ = c;
          continue;
        }
        else if ((c >> 5) == 0x06)
        {
          // UTF-8:   110yyyyy 10zzzzzz
          // Unicode: 00000yyy yyzzzzzz
          //
          unsigned int u = (c & 0x1F) << 6;
          c = *++s;
          u |= c & 0x3F;

          if (u < 0x100)
          {
            *r++ = static_cast<char> (u);
            continue;
          }
        }
        else if ((c >> 4) == 0x0E)
        {
          // UTF-8:   1110xxxx 10yyyyyy 10zzzzzz
          // Unicode: xxxxyyyy yyzzzzzz
          //
          s += 2;
        }
        else if ((c >> 3) == 0x1E)
        {
          // UTF-8:   000wwwxx xxxxyyyy yyzzzzzz
          // Unicode: 11110www 10xxxxxx 10yyyyyy 10zzzzzz
          //
          s += 3;
        }

        if (unrep_char_ != '\0')
          *r++ = unrep_char_;
        else
          return false;
      }

      *r = '\0';

      return true;
    }

    bool iso8859_1::
    to (const char* s, size_t n, char* r)
    {
      const char* end = s + n;

      for (; s != end; ++s)
      {
        unsigned char c = *s;

        if (c < 0x80)
        {
          // Fast path.
          //
          *r++ = c;
          continue;
        }
        else if ((c >> 5) == 0x06)
        {
          // UTF-8:   110yyyyy 10zzzzzz
          // Unicode: 00000yyy yyzzzzzz
          //
          unsigned int u = (c & 0x1F) << 6;
          c = *++s;
          u |= c & 0x3F;

          if (u < 0x100)
          {
            *r++ = static_cast<char> (u);
            continue;
          }
        }
        else if ((c >> 4) == 0x0E)
        {
          // UTF-8:   1110xxxx 10yyyyyy 10zzzzzz
          // Unicode: xxxxyyyy yyzzzzzz
          //
          s += 2;
        }
        else if ((c >> 3) == 0x1E)
        {
          // UTF-8:   000wwwxx xxxxyyyy yyzzzzzz
          // Unicode: 11110www 10xxxxxx 10yyyyyy 10zzzzzz
          //
          s += 3;
        }

        if (unrep_char_ != '\0')
          *r++ = unrep_char_;
        else
          return false;
      }

      *r = '\0';

      return true;
    }

    void iso8859_1::
    from (const char* s, char* r)
    {
      for (; *s != 0; ++s)
      {
        unsigned char c = *s;

        if (c < 0x80)
          *r++ = c;
        else
        {
          // 2-byte sequence.
          //
          *r++ = (c >> 6) | 0xC0;
          *r++ = (c | 0x80) & 0xBF;
        }
      }

      *r = '\0';
    }

    void iso8859_1::
    from (const char* s, size_t n, char* r)
    {
      const char* end = s + n;

      for (; s != end; ++s)
      {
        unsigned char c = *s;

        if (c < 0x80)
          *r++ = c;
        else
        {
          // 2-byte sequence.
          //
          *r++ = (c >> 6) | 0xC0;
          *r++ = (c | 0x80) & 0xBF;
        }
      }

      *r = '\0';
    }
  }
}
