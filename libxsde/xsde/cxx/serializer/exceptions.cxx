// file      : xsde/cxx/serializer/exceptions.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/config.hxx>

#ifdef XSDE_IOSTREAM
#  include <iostream>
#endif

#include <xsde/cxx/serializer/exceptions.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      // exception
      //

#ifdef XSDE_IOSTREAM
      std::ostream&
      operator<< (std::ostream& os, const exception& e)
      {
        return os << e.text ();
      }
#endif

      // xml
      //
      const char* xml::
      text () const
      {
        return genx::xml_error_text (code_);
      }

      const char* xml::
      what () const throw ()
      {
        return "xml error";
      }

      // schema
      //
#ifdef XSDE_SERIALIZER_VALIDATION
      const char* schema::
      text () const
      {
        return schema_error::text (code_);
      }

      const char* schema::
      what () const throw ()
      {
        return "schema error";
      }
#endif
    }
  }
}
