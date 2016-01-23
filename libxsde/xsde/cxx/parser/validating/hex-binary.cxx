// file      : xsde/cxx/parser/validating/hex-binary.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/config.hxx>

#ifdef XSDE_CUSTOM_ALLOCATOR
#  include <xsde/cxx/allocator.hxx>
#endif

#include <xsde/cxx/parser/validating/hex-binary.hxx>

static unsigned char
hex_decode (char c)
{
  unsigned char r = 0xFF;

  if (c >= '0' && c <= '9')
    r = static_cast<unsigned char> (c - '0');
  else if (c >= 'A' && c <= 'F')
    r = static_cast<unsigned char> (10 + (c - 'A'));
  else if (c >= 'a' && c <= 'f')
    r = static_cast<unsigned char> (10 + (c - 'a'));

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
        hex_binary_pimpl::
        ~hex_binary_pimpl ()
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

        void hex_binary_pimpl::
        _reset ()
        {
          hex_binary_pskel::_reset ();

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

        hex_binary_pimpl::
        hex_binary_pimpl (bool base)
            : base_ (base), buf_ (0)
        {
        }

        void hex_binary_pimpl::
        pre_impl (buffer* b)
        {
          buf_ = b;
        }

        void hex_binary_pimpl::
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

        void hex_binary_pimpl::
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

        void hex_binary_pimpl::
        _post ()
        {
          ro_string tmp (str_);
          ro_string::size_type size = trim_right (tmp);

          if (size % 2 != 0)
          {
            _schema_error (schema_error::invalid_hex_binary_value);
            return;
          }

          size_t n = size / 2;

#ifdef XSDE_EXCEPTIONS
          buf_->size (n);
#else
          if (buf_->size (n))
          {
            _sys_error (sys_error::no_memory);
            return;
          }
#endif

          if (n != 0)
          {
            const char* src = tmp.data ();
            char* dst = buf_->data ();
            size_t i = 0;

            for (; i < n; ++i)
            {
              unsigned char h = hex_decode (src[2 * i]);
              unsigned char l = hex_decode (src[2 * i + 1]);

              if (h == 0xFF || l == 0xFF)
                break;

              dst[i] = (h << 4) | l;
            }

            if (i != n)
              _schema_error (schema_error::invalid_hex_binary_value);
          }
        }

        buffer* hex_binary_pimpl::
        post_hex_binary ()
        {
          buffer* r = buf_;
          buf_ = 0;
          return r;
        }
      }
    }
  }
}
