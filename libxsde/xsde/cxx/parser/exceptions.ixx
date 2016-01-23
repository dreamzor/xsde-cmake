// file      : xsde/cxx/parser/exceptions.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      // exception
      //
      inline exception::
      exception (unsigned long line, unsigned long column)
          : line_ (line), column_ (column)
      {
      }

      inline unsigned long exception::
      line () const
      {
        return line_;
      }

      inline unsigned long exception::
      column () const
      {
        return column_;
      }


      // xml
      //
      inline xml::
      xml (xml_error code, unsigned long line, unsigned long column)
          : exception (line, column), code_ (code)
      {
      }

      inline xml_error xml::
      code () const
      {
        return code_;
      }


      // schema
      //
#ifdef XSDE_PARSER_VALIDATION
      inline schema::
      schema (schema_error code, unsigned long line, unsigned long column)
          : exception (line, column), code_ (code)
      {
      }

      inline schema_error schema::
      code () const
      {
        return code_;
      }
#endif
    }
  }
}

