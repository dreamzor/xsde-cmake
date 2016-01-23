// file      : xsde/cxx/parser/validating/base64-binary.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/config.hxx>

#ifdef XSDE_CUSTOM_ALLOCATOR
#  include <xsde/cxx/allocator.hxx>
#endif

#include <xsde/cxx/parser/validating/base64-binary.hxx>

static unsigned char
base64_decode (char c)
{
  unsigned char r = 0xFF;

  if (c >= 'A' && c <= 'Z')
    r = static_cast<unsigned char> (c - 'A');
  else if (c >= 'a' && c <= 'z')
    r = static_cast<unsigned char> (c - 'a' + 26);
  else if (c >= '0' && c <= '9')
    r = static_cast<unsigned char> (c - '0' + 52);
  else if (c == '+')
    r = 62;
  else if (c == '/')
    r = 63;

  return r;
}

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
      {
        base64_binary_pimpl::
        ~base64_binary_pimpl ()
        {
          if (!base_ && buf_)
          {
#ifndef XSDE_CUSTOM_ALLOCATOR
            delete buf_;
#else
            buf_->~buffer ();
            cxx::free (buf_);
#endif
          }
        }

        void base64_binary_pimpl::
        _reset ()
        {
          base64_binary_pskel::_reset ();

          if (!base_ && buf_)
          {
#ifndef XSDE_CUSTOM_ALLOCATOR
            delete buf_;
#else
            buf_->~buffer ();
            cxx::free (buf_);
#endif
            buf_ = 0;
          }
        }

        base64_binary_pimpl::
        base64_binary_pimpl (bool base)
            : base_ (base), buf_ (0)
        {
        }

        void base64_binary_pimpl::
        pre_impl (buffer* b)
        {
          buf_ = b;
        }

        void base64_binary_pimpl::
        _pre ()
        {
          if (buf_ == 0)
          {
#ifndef XSDE_CUSTOM_ALLOCATOR
            buf_ = new buffer ();
#else
            buf_ = static_cast<buffer*> (alloc (sizeof (buffer)));

#ifdef XSDE_EXCEPTIONS
            alloc_guard ag (buf_);
            new (buf_) buffer ();
            ag.release ();
#else
            if (buf_)
              new (buf_) buffer ();
#endif
#endif

#ifndef XSDE_EXCEPTIONS
            if (buf_ == 0)
            {
              _sys_error (sys_error::no_memory);
              return;
            }
#endif
          }

#ifdef XSDE_EXCEPTIONS
          str_.assign ("", 0);
#else
          if (str_.assign ("", 0))
            _sys_error (sys_error::no_memory);
#endif
        }

        void base64_binary_pimpl::
        _characters (const ro_string& s)
        {
          if (str_.size () == 0)
          {
            ro_string tmp (s.data (), s.size ());

            if (trim_left (tmp) != 0)
            {
#ifdef XSDE_EXCEPTIONS
              str_.append (tmp.data (), tmp.size ());
#else
              if (str_.append (tmp.data (), tmp.size ()))
                _sys_error (sys_error::no_memory);
#endif
            }
          }
          else
          {
#ifdef XSDE_EXCEPTIONS
            str_.append (s.data (), s.size ());
#else
            if (str_.append (s.data (), s.size ()))
              _sys_error (sys_error::no_memory);
#endif
          }
        }

        void base64_binary_pimpl::
        _post ()
        {
          typedef string::size_type size_type;

          size_type size = str_.size ();
          const char* src = str_.data ();

          // Remove all whitespaces.
          //
          {
            size_type j = 0;
            bool subs = false;

            for (size_type i = 0; i < size; ++i)
            {
              char c = str_[i];

              if (c == 0x20 || c == 0x0A || c == 0x0D || c == 0x09)
              {
                subs = true;
              }
              else
              {
                if (subs)
                  subs = false;

                str_[j++] = c;
              }
            }

            size = j;
            str_.truncate (size);
          }

          // Our length should be a multiple of four.
          //
          if (size == 0 || size % 4 != 0)
          {
            _schema_error (schema_error::invalid_base64_binary_value);
            return;
          }

          size_type quad_count = size / 4;
          size_type capacity = quad_count * 3 + 1;

#ifdef XSDE_EXCEPTIONS
          buf_->size (capacity);
#else
          if (buf_->size (capacity))
          {
            _sys_error (sys_error::no_memory);
            return;
          }
#endif
          char* dst = buf_->data ();

          // Source and destination indexes.
          //
          size_type si = 0;
          size_type di = 0;

          // Process all quads except the last one.
          //
          unsigned char b1, b2, b3, b4;

          for (size_type q = 0; q < quad_count - 1; ++q)
          {
            b1 = base64_decode (src[si++]);
            b2 = base64_decode (src[si++]);
            b3 = base64_decode (src[si++]);
            b4 = base64_decode (src[si++]);

            if (b1 == 0xFF || b2 == 0xFF || b3 == 0xFF || b4 == 0xFF)
            {
              _schema_error (schema_error::invalid_base64_binary_value);
              return;
            }

            dst[di++] = (b1 << 2) | (b2 >> 4);
            dst[di++] = (b2 << 4) | (b3 >> 2);
            dst[di++] = (b3 << 6) | b4;
          }

          // Process the last quad. The first two octets are always there.
          //
          b1 = base64_decode (src[si++]);
          b2 = base64_decode (src[si++]);

          if (b1 == 0xFF || b2 == 0xFF)
          {
            _schema_error (schema_error::invalid_base64_binary_value);
            return;
          }

          char e3 = src[si++];
          char e4 = src[si++];

          if (e4 == '=')
          {
            if (e3 == '=')
            {
              // Two pads. Last 4 bits in b2 should be zero.
              //
              if ((b2 & 0x0F) != 0)
              {
                _schema_error (schema_error::invalid_base64_binary_value);
                return;
              }

              dst[di++] = (b1 << 2) | (b2 >> 4);
            }
            else
            {
              // One pad. Last 2 bits in b3 should be zero.
              //
              b3 = base64_decode (e3);

              if (b3 == 0xFF || (b3 & 0x03) != 0)
              {
                _schema_error (schema_error::invalid_base64_binary_value);
                return;
              }

              dst[di++] = (b1 << 2) | (b2 >> 4);
              dst[di++] = (b2 << 4) | (b3 >> 2);
            }
          }
          else
          {
            // No pads.
            //
            b3 = base64_decode (e3);
            b4 = base64_decode (e4);

            if (b3 == 0xFF || b4 == 0xFF)
            {
              _schema_error (schema_error::invalid_base64_binary_value);
              return;
            }

            dst[di++] = (b1 << 2) | (b2 >> 4);
            dst[di++] = (b2 << 4) | (b3 >> 2);
            dst[di++] = (b3 << 6) | b4;
          }

          // Set the real size.
          //
          buf_->size (di);
        }

        buffer* base64_binary_pimpl::
        post_base64_binary ()
        {
          buffer* r = buf_;
          buf_ = 0;
          return r;
        }
      }
    }
  }
}
