// file      : xsde/cxx/parser/error.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_ERROR_HXX
#define XSDE_CXX_PARSER_ERROR_HXX

#include <xsde/cxx/config.hxx>
#include <xsde/cxx/sys-error.hxx>

#include <xsde/cxx/parser/expat/xml-error.hxx>

#ifdef XSDE_PARSER_VALIDATION
#  include <xsde/cxx/schema-error.hxx>
#endif

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      using expat::xml_error;

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


        // Line and column are only available for xml, schema, and
        // app errors.
        //
        unsigned long
        line () const;

        unsigned long
        column () const;


        // Returns true if there is an error so that you can write
        // if (p.error ()) or if (error e = p.error ()).
        //
        typedef void (error::*bool_convertible) ();
        operator bool_convertible () const;


        // sys
        //
      public:
        error (sys_error);

        sys_error
        sys_code () const;

        const char*
        sys_text () const;


        // xml
        //
      public:
        error (xml_error, unsigned long line, unsigned long column);

        xml_error
        xml_code () const;

        const char*
        xml_text () const;


        // schema
        //
#ifdef XSDE_PARSER_VALIDATION
      public:
        error (schema_error::value, unsigned long line, unsigned long column);

        schema_error
        schema_code () const;

        const char*
        schema_text () const;
#endif

        // app
        //
      public:
        error (int app_code, unsigned long line, unsigned long column);

        int
        app_code () const;


      public:
        error ();

      private:
        void
        true_ ();

      private:
        error_type type_;
        unsigned long line_;
        unsigned long column_;

        union
        {
          sys_error::value sys;
          xml_error xml;
#ifdef XSDE_PARSER_VALIDATION
          schema_error::value schema;
#endif
          int app;
        } code_;
      };
    }
  }
}

#include <xsde/cxx/parser/error.ixx>

#endif  // XSDE_CXX_PARSER_ERROR_HXX
