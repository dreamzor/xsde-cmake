// file      : xsde/cxx/parser/error.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      inline
      error::error_type error::
      type () const
      {
        return type_;
      }

      inline
      unsigned long error::
      line () const
      {
        return line_;
      }

      inline
      unsigned long error::
      column () const
      {
        return column_;
      }

      inline
      error::
      operator error::bool_convertible () const
      {
        return type_ != none ? &error::true_ : 0;
      }

      // sys
      //

      inline
      error::
      error (sys_error e)
          : type_ (sys), line_ (0), column_ (0)
      {
        code_.sys = e;
      }

      inline
      sys_error error::
      sys_code () const
      {
        return code_.sys;
      }

      inline
      const char* error::
      sys_text () const
      {
        return sys_error::text (code_.sys);
      }

      // xml
      //

      inline
      error::
      error (xml_error e, unsigned long l, unsigned long c)
          : type_ (xml), line_ (l), column_ (c)
      {
        code_.xml = e;
      }

      inline
      xml_error error::
      xml_code () const
      {
        return code_.xml;
      }

      inline
      const char* error::
      xml_text () const
      {
        return expat::xml_error_text (code_.xml);
      }

      // schema
      //

#ifdef XSDE_PARSER_VALIDATION
      inline
      error::
      error (schema_error::value e, unsigned long l, unsigned long c)
          : type_ (schema), line_ (l), column_ (c)
      {
        code_.schema = e;
      }

      inline
      schema_error error::
      schema_code () const
      {
        return code_.schema;
      }

      inline
      const char* error::
      schema_text () const
      {
        return schema_error::text (code_.schema);
      }
#endif

      // app
      //

      inline
      error::
      error (int e, unsigned long l, unsigned long c)
          : type_ (app), line_ (l), column_ (c)
      {
        code_.app = e;
      }

      inline
      int error::
      app_code () const
      {
        return code_.app;
      }

      inline
      error::
      error ()
          : type_ (none)
      {
      }
    }
  }
}
