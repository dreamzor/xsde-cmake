// file      : xsde/cxx/serializer/genx/xml-error.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/serializer/genx/xml-error.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace genx
      {
        static const char* const text_[] =
        {
          "no error",
          "illegal UTF-8 character",
          "illegal XML character",
          "illegal name",
          "out of memory",
          "illegal namespace name",
          "internal error",
          "duplicate prefix",
          "call out of sequence",
          "mismatched end element call",
          "output error",
          "missing attribute value",
          "malformed comment body",
          "illegal character sequence in processing instruction",
          "processing instruction target is XML",
          "duplicate attribute",
          "attribute in default namespace",
          "different prefixes for the same namespace in the same element",
          "default namespace in an unqualified element"
        };

        const char*
        xml_error_text (xml_error e)
        {
          return text_[e];
        }
      }
    }
  }
}

