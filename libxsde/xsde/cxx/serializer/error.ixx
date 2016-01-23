// file      : xsde/cxx/serializer/error.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      inline
      error::error_type error::
      type () const
      {
        return type_;
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
      error (sys_error::value e)
          : type_ (sys)
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
      error (xml_error e)
          : type_ (xml)
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
        return genx::xml_error_text (code_.xml);
      }

      // schema
      //

#ifdef XSDE_SERIALIZER_VALIDATION
      inline
      error::
      error (schema_error::value e)
          : type_ (schema)
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
      error (int e)
          : type_ (app)
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
