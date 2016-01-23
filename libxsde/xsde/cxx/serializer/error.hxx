// file      : xsde/cxx/serializer/error.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_ERROR_HXX
#define XSDE_CXX_SERIALIZER_ERROR_HXX

#include <xsde/cxx/config.hxx>
#include <xsde/cxx/sys-error.hxx>

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
      using genx::xml_error;

      // This type is only used when C++ exceptions are not used.
      //
      struct error
      {
        enum error_type
        {
          none,
          sys,
          xml,
          schema,
          app
        };

      public:
        error_type
        type () const;

        // Returns true if there is an error so that you can write
        // if (s.error ()) or if (error e = s.error ()).
        //
        typedef void (error::*bool_convertible) ();
        operator bool_convertible () const;


        // sys
        //
      public:
        error (sys_error::value);

        sys_error
        sys_code () const;

        const char*
        sys_text () const;

        // xml
        //
      public:
        error (xml_error);

        xml_error
        xml_code () const;

        const char*
        xml_text () const;


        // schema
        //
#ifdef XSDE_SERIALIZER_VALIDATION
      public:
        error (schema_error::value);

        schema_error
        schema_code () const;

        const char*
        schema_text () const;
#endif

        // app
        //
      public:
        error (int app_code);

        int
        app_code () const;


      public:
        error ();

      private:
        void
        true_ ();

      private:
        error_type type_;

        union
        {
          sys_error::value sys;
          xml_error xml;
#ifdef XSDE_SERIALIZER_VALIDATION
          schema_error::value schema;
#endif
          int app;
        } code_;
      };
    }
  }
}

#include <xsde/cxx/serializer/error.ixx>

#endif  // XSDE_CXX_SERIALIZER_ERROR_HXX
