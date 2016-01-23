// file      : xsde/cxx/parser/context.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      // parser_state
      //
      inline parser_state::
      parser_state ()
          : parser_ (0), depth_ (0), any_ (false)
      {
      }

      // context
      //
      inline context::
      context ()
          : xml_parser_ (0)
      {
#if defined(XSDE_PARSER_VALIDATION) || !defined(XSDE_EXCEPTIONS)
        error_type_ = error_none;
#endif
      }

      inline XML_Parser context::
      xml_parser ()
      {
        return xml_parser_;
      }

      inline const ro_string& context::
      element_namespace () const
      {
        return ns_;
      }

      inline const ro_string& context::
      element_name () const
      {
        return name_;
      }

      inline void context::
      start_wildcard_content ()
      {
        current_.any_ = true;
        current_.depth_++;
      }

      inline void context::
      reset (XML_Parser parser)
      {
        xml_parser_ = parser;
        current_ = parser_state ();

#if defined(XSDE_PARSER_VALIDATION) || !defined(XSDE_EXCEPTIONS)
        error_type_ = error_none;
#endif
      }

      inline void context::
      element_namespace (const ro_string& ns)
      {
        ns_.assign (ns);
      }

      inline void context::
      element_name (const ro_string& name)
      {
        name_.assign (name);
      }

      //
      //
#ifndef XSDE_EXCEPTIONS
      inline int context::
      app_error () const
      {
        return error_code_.app;
      }

      inline void context::
      app_error (int e)
      {
        error_type_ = error_app;
        error_code_.app = e;
      }

      inline void context::
      sys_error (sys_error_t e)
      {
        error_type_ = error_sys;
        error_code_.sys = e;
      }

      inline context::sys_error_t context::
      sys_error () const
      {
        return error_code_.sys;
      }
#endif

#ifdef XSDE_PARSER_VALIDATION
      inline context::schema_error_t context::
      schema_error () const
      {
        return error_code_.schema;
      }

      inline void context::
      schema_error (schema_error_t e)
      {
        error_type_ = error_schema;
        error_code_.schema = e;
      }
#endif

#if defined(XSDE_PARSER_VALIDATION) || !defined(XSDE_EXCEPTIONS)
      inline context::error_type_t context::
      error_type () const
      {
        return error_type_;
      }
#endif
    }
  }
}
