// file      : xsde/cxx/parser/context.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_CONTEXT_HXX
#define XSDE_CXX_PARSER_CONTEXT_HXX

#include <xsde/cxx/config.hxx>

#include <stddef.h> // size_t

#include <xsde/c/expat/expat.h>

#include <xsde/cxx/ro-string.hxx>

#ifndef XSDE_EXCEPTIONS
#  include <xsde/cxx/sys-error.hxx>
#endif

#ifdef XSDE_PARSER_VALIDATION
#  include <xsde/cxx/schema-error.hxx>
#endif

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      struct parser_base;

      struct parser_state
      {
        parser_state ();

        // Depth is maintained only when we don't have a parser for a
        // document fragment or if we are handling a wildcard in which
        // case the any flag should be set.
        //
        parser_base* parser_;
        size_t depth_;
        bool any_;
      };

      class context
      {
      public:
        context ();

      private:
        context (const context&);
        context& operator= (const context&);

      public:
        XML_Parser
        xml_parser ();

        // Return namespace and name of the current element being parsed.
        //
        const ro_string&
        element_namespace () const;

        const ro_string&
        element_name () const;

        // Error handling via codes.
        //
      public:

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
#ifdef XSDE_PARSER_VALIDATION
      public:
        typedef cxx::schema_error::value schema_error_t;

        schema_error_t
        schema_error () const;

        void
        schema_error (schema_error_t);
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
#if defined(XSDE_PARSER_VALIDATION) || !defined(XSDE_EXCEPTIONS)
      public:
        enum error_type_t
        {
          error_none = 0,
          error_app,
          error_schema,
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
#endif
#ifdef XSDE_PARSER_VALIDATION
          schema_error_t schema;
#endif
#ifndef XSDE_EXCEPTIONS
          sys_error_t sys;
#endif
        } error_code_;

#endif // XSDE_PARSER_VALIDATION || !XSDE_EXCEPTIONS

      public:
        void
        start_wildcard_content ();

        parser_base*
        nested_parser () const
        {
          return nested_parser_;
        }

        void
        nested_parser (parser_base* p)
        {
          nested_parser_ = p;
        }

        void
        reset (XML_Parser);

        void
        element_namespace (const ro_string&);

        void
        element_name (const ro_string&);

      public:
        parser_state current_;

      private:
        // Nested parser when transitioning from outer to inner or from
        // inner to outer parsers.
        //
        parser_base* nested_parser_;

      protected:
        XML_Parser xml_parser_;

        ro_string ns_;
        ro_string name_;
      };
    }
  }
}

#include <xsde/cxx/parser/context.ixx>

#endif  // XSDE_CXX_PARSER_CONTEXT_HXX
