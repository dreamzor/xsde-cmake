// file      : xsde/cxx/serializer/non-validating/xml-schema-simpl.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_NON_VALIDATING_XML_SCHEMA_SIMPL_HXX
#define XSDE_CXX_SERIALIZER_NON_VALIDATING_XML_SCHEMA_SIMPL_HXX

#include <xsde/cxx/serializer/non-validating/xml-schema-sskel.hxx>

#include <xsde/cxx/serializer/non-validating/any-type.hxx>

#ifdef XSDE_STL
#  include <xsde/cxx/serializer/non-validating/any-simple-type-stl.hxx>
#else
#  include <xsde/cxx/serializer/non-validating/any-simple-type.hxx>
#endif

#include <xsde/cxx/serializer/non-validating/boolean.hxx>
#include <xsde/cxx/serializer/non-validating/byte.hxx>
#include <xsde/cxx/serializer/non-validating/unsigned-byte.hxx>
#include <xsde/cxx/serializer/non-validating/byte.hxx>
#include <xsde/cxx/serializer/non-validating/unsigned-byte.hxx>
#include <xsde/cxx/serializer/non-validating/short.hxx>
#include <xsde/cxx/serializer/non-validating/unsigned-short.hxx>
#include <xsde/cxx/serializer/non-validating/int.hxx>
#include <xsde/cxx/serializer/non-validating/unsigned-int.hxx>

#ifdef XSDE_LONGLONG
#  include <xsde/cxx/serializer/non-validating/long-long.hxx>
#  include <xsde/cxx/serializer/non-validating/unsigned-long-long.hxx>
#else
#  include <xsde/cxx/serializer/non-validating/long.hxx>
#  include <xsde/cxx/serializer/non-validating/unsigned-long.hxx>
#endif

#include <xsde/cxx/serializer/non-validating/integer.hxx>
#include <xsde/cxx/serializer/non-validating/negative-integer.hxx>
#include <xsde/cxx/serializer/non-validating/non-positive-integer.hxx>
#include <xsde/cxx/serializer/non-validating/positive-integer.hxx>
#include <xsde/cxx/serializer/non-validating/non-negative-integer.hxx>
#include <xsde/cxx/serializer/non-validating/float.hxx>
#include <xsde/cxx/serializer/non-validating/double.hxx>
#include <xsde/cxx/serializer/non-validating/decimal.hxx>

#ifdef XSDE_STL
#  include <xsde/cxx/serializer/non-validating/string-stl.hxx>
#  include <xsde/cxx/serializer/non-validating/normalized-string-stl.hxx>
#  include <xsde/cxx/serializer/non-validating/token-stl.hxx>
#  include <xsde/cxx/serializer/non-validating/name-stl.hxx>
#  include <xsde/cxx/serializer/non-validating/nmtoken-stl.hxx>
#  include <xsde/cxx/serializer/non-validating/nmtokens-stl.hxx>
#  include <xsde/cxx/serializer/non-validating/ncname-stl.hxx>
#  include <xsde/cxx/serializer/non-validating/id-stl.hxx>
#  include <xsde/cxx/serializer/non-validating/idref-stl.hxx>
#  include <xsde/cxx/serializer/non-validating/idrefs-stl.hxx>
#  include <xsde/cxx/serializer/non-validating/language-stl.hxx>
#  include <xsde/cxx/serializer/non-validating/uri-stl.hxx>
#  include <xsde/cxx/serializer/non-validating/qname-stl.hxx>
#else
#  include <xsde/cxx/serializer/non-validating/string.hxx>
#  include <xsde/cxx/serializer/non-validating/normalized-string.hxx>
#  include <xsde/cxx/serializer/non-validating/token.hxx>
#  include <xsde/cxx/serializer/non-validating/name.hxx>
#  include <xsde/cxx/serializer/non-validating/nmtoken.hxx>
#  include <xsde/cxx/serializer/non-validating/nmtokens.hxx>
#  include <xsde/cxx/serializer/non-validating/ncname.hxx>
#  include <xsde/cxx/serializer/non-validating/id.hxx>
#  include <xsde/cxx/serializer/non-validating/idref.hxx>
#  include <xsde/cxx/serializer/non-validating/idrefs.hxx>
#  include <xsde/cxx/serializer/non-validating/language.hxx>
#  include <xsde/cxx/serializer/non-validating/uri.hxx>
#  include <xsde/cxx/serializer/non-validating/qname.hxx>
#endif

#include <xsde/cxx/serializer/non-validating/base64-binary.hxx>
#include <xsde/cxx/serializer/non-validating/hex-binary.hxx>

#include <xsde/cxx/serializer/non-validating/gday.hxx>
#include <xsde/cxx/serializer/non-validating/gmonth.hxx>
#include <xsde/cxx/serializer/non-validating/gyear.hxx>
#include <xsde/cxx/serializer/non-validating/gmonth-day.hxx>
#include <xsde/cxx/serializer/non-validating/gyear-month.hxx>
#include <xsde/cxx/serializer/non-validating/date.hxx>
#include <xsde/cxx/serializer/non-validating/time.hxx>
#include <xsde/cxx/serializer/non-validating/date-time.hxx>
#include <xsde/cxx/serializer/non-validating/duration.hxx>

#endif  // XSDE_CXX_SERIALIZER_NON_VALIDATING_XML_SCHEMA_SIMPL_HXX
