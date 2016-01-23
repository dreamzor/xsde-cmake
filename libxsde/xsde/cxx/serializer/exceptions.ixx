// file      : xsde/cxx/serializer/exceptions.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      // xml
      //
      inline xml::
      xml (xml_error code)
          : code_ (code)
      {
      }

      inline xml_error xml::
      code () const
      {
        return code_;
      }

      // schema
      //
#ifdef XSDE_SERIALIZER_VALIDATION
      inline schema::
      schema (schema_error code)
          : code_ (code)
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

