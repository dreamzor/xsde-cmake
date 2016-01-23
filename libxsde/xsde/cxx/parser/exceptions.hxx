// file      : xsde/cxx/parser/exceptions.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_EXCEPTIONS_HXX
#define XSDE_CXX_PARSER_EXCEPTIONS_HXX

#include <xsde/cxx/config.hxx>

#ifdef XSDE_IOSTREAM
#  include <iosfwd>
#endif

#include <xsde/cxx/exceptions.hxx> // xsde::cxx::exception

#ifdef XSDE_PARSER_VALIDATION
#  include <xsde/cxx/schema-error.hxx>
#endif

#include <xsde/cxx/parser/expat/xml-error.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      // exception
      //
      struct exception: xsde::cxx::exception
      {
        exception (unsigned long line, unsigned long column);

        unsigned long
        line () const;

        unsigned long
        column () const;

        virtual const char*
        text () const = 0;

      private:
        unsigned long line_;
        unsigned long column_;
      };

#ifdef XSDE_IOSTREAM
      std::ostream&
      operator<< (std::ostream&, const exception&);
#endif


      // xml
      //
      using expat::xml_error;

      struct xml: exception
      {
        xml (xml_error, unsigned long line, unsigned long column);

        xml_error
        code () const;

        virtual const char*
        text () const;

        virtual const char*
        what () const throw ();

      private:
        xml_error code_;
      };


      // schema
      //
#ifdef XSDE_PARSER_VALIDATION
      struct schema: exception
      {
        schema (schema_error, unsigned long line, unsigned long column);

        schema_error
        code () const;

        virtual const char*
        text () const;

        virtual const char*
        what () const throw ();

      private:
        schema_error code_;
      };
#endif
    }
  }
}

#include <xsde/cxx/parser/exceptions.ixx>

#endif  // XSDE_CXX_PARSER_EXCEPTIONS_HXX
