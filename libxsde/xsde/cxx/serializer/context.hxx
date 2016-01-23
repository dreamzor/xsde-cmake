// file      : xsde/cxx/serializer/context.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_CONTEXT_HXX
#define XSDE_CXX_SERIALIZER_CONTEXT_HXX

#include <xsde/cxx/config.hxx>

#include <stddef.h> // size_t

#include <xsde/c/genx/genx.h>
#include <xsde/cxx/string.hxx>

#ifndef XSDE_EXCEPTIONS
#  include <xsde/cxx/sys-error.hxx>
#endif

#include <xsde/cxx/serializer/genx/xml-error.hxx>

#ifdef XSDE_SERIALIZER_VALIDATION
#  include <xsde/cxx/schema-error.hxx>
#endif

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      class context
      {
      public:
        context (genxWriter xml_serializer);

      private:
        context (const context&);
        context& operator= (const context&);

      public:
        genxWriter
        xml_serializer ();

#ifdef XSDE_POLYMORPHIC
      public:
        // Set/get the dynamic serializer type id (as opaque const void*)
        // in case of polymorphic serialization. If type id is not set,
        // static type is assumed.
        //
        void
        type_id (const void*);

        const void*
        type_id ();
#endif

      public:
#ifdef XSDE_EXCEPTIONS
        void
        start_element (const char* name);

        void
        start_element (const char* ns, const char* name);

        void
        end_element ();

        void
        start_attribute (const char* name);

        void
        start_attribute (const char* ns, const char* name);

        void
        end_attribute ();

        void
        attribute (const char* name, const char* value);

        void
        attribute (const char* ns, const char* name, const char* value);

        void
        characters (const char*);

        void
        characters (const char*, size_t);

        void
        declare_namespace (const char* ns, const char* prefix);

        void
        declare_default_namespace (const char* ns);

        void
        clear_default_namespace ();

        const char*
        lookup_namespace_prefix (const char* ns);

#ifdef XSDE_POLYMORPHIC
        void
        set_type (const char* type);
#endif
#else
        bool
        start_element (const char* name);

        bool
        start_element (const char* ns, const char* name);

        bool
        end_element ();

        bool
        start_attribute (const char* name);

        bool
        start_attribute (const char* ns, const char* name);

        bool
        end_attribute ();

        bool
        attribute (const char* name, const char* value);

        bool
        attribute (const char* ns, const char* name, const char* value);

        bool
        characters (const char*);

        bool
        characters (const char*, size_t);

        bool
        declare_namespace (const char* ns, const char* prefix);

        bool
        declare_default_namespace (const char* ns);

        bool
        clear_default_namespace ();

        const char*
        lookup_namespace_prefix (const char* ns);

#ifdef XSDE_POLYMORPHIC
        bool
        set_type (const char* type);
#endif
#endif

        // Error handling via exceptions.
        //

#ifdef XSDE_EXCEPTIONS
      public:
        void
        throw_xml_error (genx::xml_error);
#endif

        // Error handling via codes.
        //

        // Application error.
        //
#ifndef XSDE_EXCEPTIONS
      public:
        int
        app_error () const;

        void
        app_error (int);
#endif

        // Schema error.
        //
#ifdef XSDE_SERIALIZER_VALIDATION
      public:
        typedef cxx::schema_error::value schema_error_t;

        schema_error_t
        schema_error () const;

        void
        schema_error (schema_error_t);
#endif

        // XML error.
        //
#ifndef XSDE_EXCEPTIONS
      public:
        typedef genx::xml_error xml_error_t;

        xml_error_t
        xml_error () const;

        void
        xml_error (xml_error_t);
#endif

        // System error.
        //
#ifndef XSDE_EXCEPTIONS
      public:
        typedef cxx::sys_error::value sys_error_t;

        sys_error_t
        sys_error () const;

        void
        sys_error (sys_error_t);
#endif

        // Implementation details.
        //
#if defined(XSDE_SERIALIZER_VALIDATION) || !defined(XSDE_EXCEPTIONS)
      public:
        enum error_type_t
        {
          error_none = 0,
          error_app,
          error_schema,
          error_xml,
          error_sys
        };

        error_type_t
        error_type () const;

      protected:
        error_type_t error_type_;

        union
        {
#ifndef XSDE_EXCEPTIONS
          int app;
          xml_error_t xml;
#endif
#ifdef XSDE_SERIALIZER_VALIDATION
          schema_error_t schema;
#endif
#ifndef XSDE_EXCEPTIONS
          sys_error_t sys;
#endif
        } error_code_;

#endif // XSDE_SERIALIZER_VALIDATION || !XSDE_EXCEPTIONS

      protected:
        genxWriter xml_serializer_;

#ifdef XSDE_POLYMORPHIC
        const void* type_id_;
#endif

        // Support for ISO-8859-1 conversion.
        //
#ifdef XSDE_ENCODING_ISO8859_1
      protected:
        const char*
        conv_data (const char* iso_s, size_t utf_n, string& var);

        const char*
        conv_data (const char* iso_s, size_t iso_n, size_t utf_n, string& var);

        const char*
        conv_name (const char* iso_s, size_t utf_n, char* fix, string& var);

        char data_buf_[256];
        char name_buf1_[128];
        char name_buf2_[128]; // Keep buf1 and buf2 sizes the same.
#endif
      };
    }
  }
}

#include <xsde/cxx/serializer/context.ixx>

#endif  // XSDE_CXX_SERIALIZER_CONTEXT_HXX
