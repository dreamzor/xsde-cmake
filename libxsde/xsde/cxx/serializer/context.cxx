// file      : xsde/cxx/serializer/context.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <assert.h>

#include <xsde/cxx/config.hxx>
#include <xsde/cxx/ro-string.hxx>

#ifdef XSDE_EXCEPTIONS
#  include <new> // std::bad_alloc
#  include <xsde/cxx/serializer/exceptions.hxx>
#endif

#ifdef XSDE_CUSTOM_ALLOCATOR
#  include <xsde/cxx/allocator.hxx>
#endif

#ifdef XSDE_ENCODING_ISO8859_1
#  include <xsde/cxx/iso8859-1.hxx>
#endif

#include <xsde/cxx/serializer/context.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      //
      //
#ifdef XSDE_EXCEPTIONS
      void context::
#else
      bool context::
#endif
      start_element (const char* name)
      {
        // Convert from application encoding.
        //
#ifdef XSDE_ENCODING_UTF8
        const char* uname = name;
#elif defined(XSDE_ENCODING_ISO8859_1)
        const char* uname;
        size_t un;
        string buf;

        if (iso8859_1::ascii_iso (name, un))
          uname = name;
        else
        {
          uname = conv_name (name, un, name_buf1_, buf);

#ifndef XSDE_EXCEPTIONS
          if (uname == 0)
            return false;
#endif
        }
#endif // XSDE_ENCODING_*

        genxStatus e = genxStartElementLiteral (
          xml_serializer_,
          0,
          reinterpret_cast<constUtf8> (uname));

#ifdef XSDE_EXCEPTIONS
        if (e != GENX_SUCCESS)
          throw_xml_error (e);
#else
        if (e != GENX_SUCCESS)
          xml_error (e);

        return e == GENX_SUCCESS;
#endif
      }

      //
      //
#ifdef XSDE_EXCEPTIONS
      void context::
#else
      bool context::
#endif
      start_element (const char* ns, const char* name)
      {
        // Convert from application encoding.
        //
#ifdef XSDE_ENCODING_UTF8
        const char* uns = ns;
        const char* uname = name;
#elif defined(XSDE_ENCODING_ISO8859_1)
        const char* uns;
        const char* uname;
        size_t un;
        string buf1, buf2;

        if (iso8859_1::ascii_iso (ns, un))
          uns = ns;
        else
        {
          uns = conv_name (ns, un, name_buf1_, buf1);

#ifndef XSDE_EXCEPTIONS
          if (uns == 0)
            return false;
#endif
        }

        if (iso8859_1::ascii_iso (name, un))
          uname = name;
        else
        {
          uname = conv_name (name, un, name_buf2_, buf2);

#ifndef XSDE_EXCEPTIONS
          if (uname == 0)
            return false;
#endif
        }
#endif // XSDE_ENCODING_*

        genxStatus e = genxStartElementLiteral (
          xml_serializer_,
          reinterpret_cast<constUtf8> (uns),
          reinterpret_cast<constUtf8> (uname));

#ifdef XSDE_EXCEPTIONS
        if (e != GENX_SUCCESS)
          throw_xml_error (e);
#else
        if (e != GENX_SUCCESS)
          xml_error (e);

        return e == GENX_SUCCESS;
#endif
      }

      //
      //
#ifdef XSDE_EXCEPTIONS
      void context::
#else
      bool context::
#endif
      start_attribute (const char* name)
      {
        // Convert from application encoding.
        //
#ifdef XSDE_ENCODING_UTF8
        const char* uname = name;
#elif defined(XSDE_ENCODING_ISO8859_1)
        const char* uname;
        size_t un;
        string buf;

        if (iso8859_1::ascii_iso (name, un))
          uname = name;
        else
        {
          uname = conv_name (name, un, name_buf1_, buf);

#ifndef XSDE_EXCEPTIONS
          if (uname == 0)
            return false;
#endif
        }
#endif // XSDE_ENCODING_*

        genxStatus e = genxStartAttributeLiteral (
          xml_serializer_,
          0,
          reinterpret_cast<constUtf8> (uname));

#ifdef XSDE_EXCEPTIONS
        if (e != GENX_SUCCESS)
          throw_xml_error (e);
#else
        if (e != GENX_SUCCESS)
          xml_error (e);

        return e == GENX_SUCCESS;
#endif
      }

      //
      //
#ifdef XSDE_EXCEPTIONS
      void context::
#else
      bool context::
#endif
      start_attribute (const char* ns, const char* name)
      {
        // Convert from application encoding.
        //
#ifdef XSDE_ENCODING_UTF8
        const char* uns = ns;
        const char* uname = name;
#elif defined(XSDE_ENCODING_ISO8859_1)
        const char* uns;
        const char* uname;
        size_t un;
        string buf1, buf2;

        if (iso8859_1::ascii_iso (ns, un))
          uns = ns;
        else
        {
          uns = conv_name (ns, un, name_buf1_, buf1);

#ifndef XSDE_EXCEPTIONS
          if (uns == 0)
            return false;
#endif
        }

        if (iso8859_1::ascii_iso (name, un))
          uname = name;
        else
        {
          uname = conv_name (name, un, name_buf2_, buf2);

#ifndef XSDE_EXCEPTIONS
          if (uname == 0)
            return false;
#endif
        }
#endif // XSDE_ENCODING_*

        genxStatus e = genxStartAttributeLiteral (
          xml_serializer_,
          reinterpret_cast<constUtf8> (uns),
          reinterpret_cast<constUtf8> (uname));

#ifdef XSDE_EXCEPTIONS
        if (e != GENX_SUCCESS)
          throw_xml_error (e);
#else
        if (e != GENX_SUCCESS)
          xml_error (e);

        return e == GENX_SUCCESS;
#endif
      }

      //
      //
#ifdef XSDE_EXCEPTIONS
      void context::
#else
      bool context::
#endif
      attribute (const char* name, const char* value)
      {
        // Convert from application encoding.
        //
#ifdef XSDE_ENCODING_UTF8
        const char* uname = name;
        const char* uvalue = value;
#elif defined(XSDE_ENCODING_ISO8859_1)
        const char* uname;
        const char* uvalue;
        size_t un;
        string buf1, buf2;

        if (iso8859_1::ascii_iso (name, un))
          uname = name;
        else
        {
          uname = conv_name (name, un, name_buf1_, buf1);

#ifndef XSDE_EXCEPTIONS
          if (uname == 0)
            return false;
#endif
        }

        if (iso8859_1::ascii_iso (value, un))
          uvalue = value;
        else
        {
          uvalue = conv_data (value, un, buf2);

#ifndef XSDE_EXCEPTIONS
          if (uvalue == 0)
            return false;
#endif
        }
#endif // XSDE_ENCODING_*

        genxStatus e = genxAddAttributeLiteral (
          xml_serializer_,
          0,
          reinterpret_cast<constUtf8> (uname),
          reinterpret_cast<constUtf8> (uvalue));

#ifdef XSDE_EXCEPTIONS
        if (e != GENX_SUCCESS)
          throw_xml_error (e);
#else
        if (e != GENX_SUCCESS)
          xml_error (e);

        return e == GENX_SUCCESS;
#endif
      }

      //
      //
#ifdef XSDE_EXCEPTIONS
      void context::
#else
      bool context::
#endif
      attribute (const char* ns, const char* name, const char* value)
      {
        // Convert from application encoding.
        //
#ifdef XSDE_ENCODING_UTF8
        const char* uns = ns;
        const char* uname = name;
        const char* uvalue = value;
#elif defined(XSDE_ENCODING_ISO8859_1)
        const char* uns;
        const char* uname;
        const char* uvalue;
        size_t un;
        string buf1, buf2, buf3;

        if (iso8859_1::ascii_iso (ns, un))
          uns = ns;
        else
        {
          uns = conv_name (ns, un, name_buf1_, buf1);

#ifndef XSDE_EXCEPTIONS
          if (uns == 0)
            return false;
#endif
        }

        if (iso8859_1::ascii_iso (name, un))
          uname = name;
        else
        {
          uname = conv_name (name, un, name_buf2_, buf2);

#ifndef XSDE_EXCEPTIONS
          if (uname == 0)
            return false;
#endif
        }

        if (iso8859_1::ascii_iso (value, un))
          uvalue = value;
        else
        {
          uvalue = conv_data (value, un, buf3);

#ifndef XSDE_EXCEPTIONS
          if (uvalue == 0)
            return false;
#endif
        }
#endif // XSDE_ENCODING_*

        genxStatus e = genxAddAttributeLiteral (
          xml_serializer_,
          reinterpret_cast<constUtf8> (uns),
          reinterpret_cast<constUtf8> (uname),
          reinterpret_cast<constUtf8> (uvalue));

#ifdef XSDE_EXCEPTIONS
        if (e != GENX_SUCCESS)
          throw_xml_error (e);
#else
        if (e != GENX_SUCCESS)
          xml_error (e);

        return e == GENX_SUCCESS;
#endif
      }

      //
      //
#ifdef XSDE_EXCEPTIONS
      void context::
#else
      bool context::
#endif
      characters (const char* s)
      {
        // Convert from application encoding.
        //
#ifdef XSDE_ENCODING_UTF8
        const char* us = s;
#elif defined(XSDE_ENCODING_ISO8859_1)
        const char* us;
        size_t un;
        string buf;

        if (iso8859_1::ascii_iso (s, un))
          us = s;
        else
        {
          us = conv_data (s, un, buf);

#ifndef XSDE_EXCEPTIONS
          if (us == 0)
            return false;
#endif
        }
#endif // XSDE_ENCODING_*

        genxStatus e = genxAddText (
          xml_serializer_,
          reinterpret_cast<constUtf8> (us));

#ifdef XSDE_EXCEPTIONS
        if (e != GENX_SUCCESS)
          throw_xml_error (e);
#else
        if (e != GENX_SUCCESS)
          xml_error (e);

        return e == GENX_SUCCESS;
#endif
      }

      //
      //
#ifdef XSDE_EXCEPTIONS
      void context::
#else
      bool context::
#endif
      characters (const char* s, size_t n)
      {
        // Convert from application encoding.
        //
#ifdef XSDE_ENCODING_UTF8
        const char* us = s;
        size_t un = n;
#elif defined(XSDE_ENCODING_ISO8859_1)
        const char* us;
        size_t un;
        string buf;

        if (iso8859_1::ascii_iso (s, n, un))
        {
          us = s;
          un = n;
        }
        else
        {
          us = conv_data (s, n, un, buf);

#ifndef XSDE_EXCEPTIONS
          if (us == 0)
            return false;
#endif
          --un; // Discount trailing zero.
        }
#endif // XSDE_ENCODING_*

        genxStatus e = genxAddCountedText (
          xml_serializer_,
          reinterpret_cast<constUtf8> (us),
          static_cast<int> (un));

#ifdef XSDE_EXCEPTIONS
        if (e != GENX_SUCCESS)
          throw_xml_error (e);
#else
        if (e != GENX_SUCCESS)
          xml_error (e);

        return e == GENX_SUCCESS;
#endif
      }

      //
      //
#ifdef XSDE_EXCEPTIONS
      void context::
#else
      bool context::
#endif
      declare_namespace (const char* ns, const char* prefix)
      {
        // Convert from application encoding.
        //
#ifdef XSDE_ENCODING_UTF8
        const char* uns = ns;
        const char* uprefix = prefix;
#elif defined(XSDE_ENCODING_ISO8859_1)
        const char* uns;
        const char* uprefix;
        size_t un;
        string buf1, buf2;

        if (iso8859_1::ascii_iso (ns, un))
          uns = ns;
        else
        {
          uns = conv_name (ns, un, name_buf1_, buf1);

#ifndef XSDE_EXCEPTIONS
          if (uns == 0)
            return false;
#endif
        }

        if (iso8859_1::ascii_iso (prefix, un))
          uprefix = prefix;
        else
        {
          uprefix = conv_name (prefix, un, name_buf2_, buf2);

#ifndef XSDE_EXCEPTIONS
          if (uprefix == 0)
            return false;
#endif
        }
#endif // XSDE_ENCODING_*

        genxStatus e = genxAddNamespaceLiteral (
          xml_serializer_,
          reinterpret_cast<constUtf8> (uns),
          reinterpret_cast<constUtf8> (uprefix));

#ifdef XSDE_EXCEPTIONS
        if (e != GENX_SUCCESS)
          throw_xml_error (e);
#else
        if (e != GENX_SUCCESS)
          xml_error (e);

        return e == GENX_SUCCESS;
#endif
      }

      //
      //
#ifdef XSDE_EXCEPTIONS
      void context::
#else
      bool context::
#endif
      declare_default_namespace (const char* ns)
      {
        // Convert from application encoding.
        //
#ifdef XSDE_ENCODING_UTF8
        const char* uns = ns;
#elif defined(XSDE_ENCODING_ISO8859_1)
        const char* uns;
        size_t un;
        string buf;

        if (iso8859_1::ascii_iso (ns, un))
          uns = ns;
        else
        {
          uns = conv_name (ns, un, name_buf1_, buf);

#ifndef XSDE_EXCEPTIONS
          if (uns == 0)
            return false;
#endif
        }
#endif // XSDE_ENCODING_*

        genxStatus e = genxAddNamespaceLiteral (
          xml_serializer_,
          reinterpret_cast<constUtf8> (uns),
          reinterpret_cast<constUtf8> (""));

#ifdef XSDE_EXCEPTIONS
        if (e != GENX_SUCCESS)
          throw_xml_error (e);
#else
        if (e != GENX_SUCCESS)
          xml_error (e);

        return e == GENX_SUCCESS;
#endif
      }

      //
      //
      const char* context::
      lookup_namespace_prefix (const char* ns)
      {
        // Convert from application encoding.
        //
#ifdef XSDE_ENCODING_UTF8
        const char* uns = ns;
#elif defined(XSDE_ENCODING_ISO8859_1)
        const char* uns;
        size_t un;
        string buf;

        if (iso8859_1::ascii_iso (ns, un))
          uns = ns;
        else
        {
          uns = conv_name (ns, un, name_buf1_, buf);

#ifndef XSDE_EXCEPTIONS
          if (uns == 0)
            return false;
#endif
        }
#endif // XSDE_ENCODING_*

        genxStatus e;
        genxNamespace gns = genxDeclareNamespace (
          xml_serializer_, reinterpret_cast<constUtf8> (uns), 0, &e);

        if (e != GENX_SUCCESS)
        {
#ifdef XSDE_EXCEPTIONS
          throw_xml_error (e);
#else
          xml_error (e);
#endif
          return 0;
        }

        const char* p = reinterpret_cast<const char*> (
          genxGetNamespacePrefix (gns));

        // Convert to application encoding.
        //
#ifdef XSDE_ENCODING_UTF8
        return p;
#elif defined(XSDE_ENCODING_ISO8859_1)
        // At the moment we can only support ASCII prefixes since there is
        // no good way to store the converted string.
        //
        assert (iso8859_1::ascii_utf (p, un));
        return p;
#endif // XSDE_ENCODING_*
      }

      //
      //
#ifdef XSDE_POLYMORPHIC
#ifdef XSDE_EXCEPTIONS
      void context::
#else
      bool context::
#endif
      set_type (const char* type)
      {
        ro_string t (type);
        const char* prefix = 0;

        size_t pos = t.find (' ');

        if (pos != ro_string::npos)
        {
          prefix = lookup_namespace_prefix (type + pos + 1);

          //@@ TODO: what if prefix is not found?
          //
#ifndef XSDE_EXCEPTIONS
          if (prefix == 0)
            return false;
#endif
          if (*prefix == '\0')
            prefix = 0;
        }

#ifdef XSDE_EXCEPTIONS
        start_attribute ("http://www.w3.org/2001/XMLSchema-instance", "type");

        if (prefix)
        {
          characters (prefix);
          characters (":");
        }

        characters (type, pos != ro_string::npos ? pos : t.size ());
        end_attribute ();
#else
        if (!start_attribute (
              "http://www.w3.org/2001/XMLSchema-instance", "type"))
          return false;

        if (prefix)
        {
          if (!characters (prefix) || !characters (":"))
            return false;
        }

        if (!characters (type, pos != ro_string::npos ? pos : t.size ()) ||
            !end_attribute ())
          return false;

        return true;
#endif
      }
#endif // XSDE_POLYMORPHIC

#ifdef XSDE_EXCEPTIONS
      void context::
      throw_xml_error (genx::xml_error e)
      {
        switch (e)
        {
        case GENX_ALLOC_FAILED:
          {
            throw std::bad_alloc ();
          }
        case GENX_IO_ERROR:
          {
            // This should never happen with consistent exception
            // handling usage since the write/flush functions
            // throw exceptions to indicate write failures.
            //
            throw xml (e);
          }
        default:
          {
            throw xml (e);
          }
        }
      }
#endif

#ifdef XSDE_ENCODING_ISO8859_1
      const char* context::
      conv_data (const char* iso_s, size_t utf_n, string& var)
      {
        char* buf;

        if (utf_n <= sizeof (data_buf_))
          buf = data_buf_;
        else
        {
#ifndef XSDE_CUSTOM_ALLOCATOR
          buf = new char[utf_n];
#else
          buf = static_cast<char*> (alloc (utf_n));
#endif

#ifndef XSDE_EXCEPTIONS
          if (buf == 0)
          {
            sys_error (sys_error::no_memory);
            return 0;
          }
#endif
          var.attach (buf, utf_n - 1);
        }

        iso8859_1::from (iso_s, buf);
        return buf;
      }

      const char* context::
      conv_data (const char* iso_s, size_t iso_n, size_t utf_n, string& var)
      {
        char* buf;

        if (utf_n <= sizeof (data_buf_))
          buf = data_buf_;
        else
        {
#ifndef XSDE_CUSTOM_ALLOCATOR
          buf = new char[utf_n];
#else
          buf = static_cast<char*> (alloc (utf_n));
#endif

#ifndef XSDE_EXCEPTIONS
          if (buf == 0)
          {
            sys_error (sys_error::no_memory);
            return 0;
          }
#endif
          var.attach (buf, utf_n - 1);
        }

        iso8859_1::from (iso_s, iso_n, buf);
        return buf;
      }

      const char* context::
      conv_name (const char* iso_s, size_t utf_n, char* fix, string& var)
      {
        char* buf;

        if (utf_n <= sizeof (name_buf1_))
          buf = fix;
        else
        {
#ifndef XSDE_CUSTOM_ALLOCATOR
          buf = new char[utf_n];
#else
          buf = static_cast<char*> (alloc (utf_n));
#endif

#ifndef XSDE_EXCEPTIONS
          if (buf == 0)
          {
            sys_error (sys_error::no_memory);
            return 0;
          }
#endif
          var.attach (buf, utf_n - 1);
        }

        iso8859_1::from (iso_s, buf);
        return buf;
      }
#endif // XSDE_ENCODING_ISO8859_1
    }
  }
}
