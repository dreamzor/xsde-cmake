// file      : xsde/cxx/schema-error.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/schema-error.hxx>

namespace xsde
{
  namespace cxx
  {
    static const char* const text_[] =
    {
      "no error",
      "expected attribute not encountered",
      "unexpected attribute encountered",
      "expected element not encountered",
      "unexpected element encountered",
      "unexpected characters encountered",
      "invalid boolean value",
      "invalid byte value",
      "invalid unsignedByte value",
      "invalid short value",
      "invalid unsignedShort value",
      "invalid int value",
      "invalid unsignedInt value",
      "invalid long value",
      "invalid unsignedLong value",
      "invalid integer value",
      "invalid negativeInteger value",
      "invalid nonPositiveInteger value",
      "invalid positiveInteger value",
      "invalid nonNegativeInteger value",
      "invalid float value",
      "invalid double value",
      "invalid decimal value",
      "invalid normalizedString value",
      "invalid token value",
      "invalid Name value",
      "invalid NMTOKEN value",
      "invalid NMTOKENS value",
      "invalid NCName value",
      "invalid ID value",
      "invalid IDREF value",
      "invalid IDREFS value",
      "invalid language value",
      "invalid QName value",
      "invalid base64Binary value",
      "invalid hexBinary value",
      "invalid gDay value",
      "invalid gMonth value",
      "invalid gYear value",
      "invalid gMonthDay value",
      "invalid gYearMonth value",
      "invalid date value",
      "invalid time value",
      "invalid dateTime value",
      "invalid duration value",
      "value is greater than maximum allowed",
      "value is less than minimum allowed",
      "value is not in enumeration",
      "value does not match pattern",
      "length is greater than maximum allowed",
      "length is less than minimum allowed",
      "length is not equal to prescribed length",
      "invalid xsi:type attribute",
      "dynamic and static types are not related by inheritance"
    };

    const char* schema_error::
    text (value v)
    {
      return text_[v];
    }
  }
}
