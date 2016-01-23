// file      : xsde/cxx/parser/expat/xml-error.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_EXPAT_XML_ERROR_HXX
#define XSDE_CXX_PARSER_EXPAT_XML_ERROR_HXX

#include <xsde/c/expat/expat.h>

enum XML_Error_Ex
{
  XML_ERROR_UNREPRESENTABLE = 0x10000
};

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace expat
      {
        // The xml_error type can hold values from XML_Error and
        // XML_Error_Ex enums.
        //
        typedef unsigned int xml_error;

        const char*
        xml_error_text (xml_error);
      }
    }
  }
}

#endif  // XSDE_CXX_PARSER_EXPAT_XML_ERROR_HXX
