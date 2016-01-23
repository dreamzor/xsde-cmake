// file      : xsde/cxx/serializer/exceptions.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_EXCEPTIONS_HXX
#define XSDE_CXX_SERIALIZER_EXCEPTIONS_HXX

#include <xsde/cxx/config.hxx>

#ifdef XSDE_IOSTREAM
#  include <iosfwd>
#endif

#include <xsde/cxx/exceptions.hxx> // xsde::cxx::exception

#ifdef XSDE_SERIALIZER_VALIDATION
#  include <xsde/cxx/schema-error.hxx>
#endif

#include <xsde/cxx/serializer/genx/xml-error.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      // exception
      //
      struct exception: xsde::cxx::exception
      {
        virtual const char*
        text () const = 0;
      };

#ifdef XSDE_IOSTREAM
      std::ostream&
      operator<< (std::ostream&, const exception&);
#endif


      // xml
      //
      using genx::xml_error;

      struct xml: exception
      {
        xml (xml_error);

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
#ifdef XSDE_SERIALIZER_VALIDATION
      struct schema: exception
      {
        schema (schema_error);

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

#include <xsde/cxx/serializer/exceptions.ixx>

#endif  // XSDE_CXX_SERIALIZER_EXCEPTIONS_HXX
