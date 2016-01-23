// file      : xsde/cxx/serializer/validating/xml-schema-simpl.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_VALIDATING_XML_SCHEMA_SIMPL_HXX
#define XSDE_CXX_SERIALIZER_VALIDATING_XML_SCHEMA_SIMPL_HXX

#include <xsde/cxx/serializer/validating/xml-schema-sskel.hxx>

#include <xsde/cxx/serializer/validating/any-type.hxx>

#ifdef XSDE_STL
#  include <xsde/cxx/serializer/validating/any-simple-type-stl.hxx>
#else
#  include <xsde/cxx/serializer/validating/any-simple-type.hxx>
#endif

#include <xsde/cxx/serializer/validating/boolean.hxx>
#include <xsde/cxx/serializer/validating/byte.hxx>
#include <xsde/cxx/serializer/validating/unsigned-byte.hxx>
#include <xsde/cxx/serializer/validating/byte.hxx>
#include <xsde/cxx/serializer/validating/unsigned-byte.hxx>
#include <xsde/cxx/serializer/validating/short.hxx>
#include <xsde/cxx/serializer/validating/unsigned-short.hxx>
#include <xsde/cxx/serializer/validating/int.hxx>
#include <xsde/cxx/serializer/validating/unsigned-int.hxx>

#ifdef XSDE_LONGLONG
#  include <xsde/cxx/serializer/validating/long-long.hxx>
#  include <xsde/cxx/serializer/validating/unsigned-long-long.hxx>
#else
#  include <xsde/cxx/serializer/validating/long.hxx>
#  include <xsde/cxx/serializer/validating/unsigned-long.hxx>
#endif

#include <xsde/cxx/serializer/validating/integer.hxx>
#include <xsde/cxx/serializer/validating/negative-integer.hxx>
#include <xsde/cxx/serializer/validating/non-positive-integer.hxx>
#include <xsde/cxx/serializer/validating/positive-integer.hxx>
#include <xsde/cxx/serializer/validating/non-negative-integer.hxx>
#include <xsde/cxx/serializer/validating/float.hxx>
#include <xsde/cxx/serializer/validating/double.hxx>
#include <xsde/cxx/serializer/validating/decimal.hxx>

#ifdef XSDE_STL
#  include <xsde/cxx/serializer/validating/string-stl.hxx>
#  include <xsde/cxx/serializer/validating/normalized-string-stl.hxx>
#  include <xsde/cxx/serializer/validating/token-stl.hxx>
#  include <xsde/cxx/serializer/validating/name-stl.hxx>
#  include <xsde/cxx/serializer/validating/nmtoken-stl.hxx>
#  include <xsde/cxx/serializer/validating/nmtokens-stl.hxx>
#  include <xsde/cxx/serializer/validating/ncname-stl.hxx>
#  include <xsde/cxx/serializer/validating/id-stl.hxx>
#  include <xsde/cxx/serializer/validating/idref-stl.hxx>
#  include <xsde/cxx/serializer/validating/idrefs-stl.hxx>
#  include <xsde/cxx/serializer/validating/language-stl.hxx>
#  include <xsde/cxx/serializer/validating/uri-stl.hxx>
#  include <xsde/cxx/serializer/validating/qname-stl.hxx>
#else
#  include <xsde/cxx/serializer/validating/string.hxx>
#  include <xsde/cxx/serializer/validating/normalized-string.hxx>
#  include <xsde/cxx/serializer/validating/token.hxx>
#  include <xsde/cxx/serializer/validating/name.hxx>
#  include <xsde/cxx/serializer/validating/nmtoken.hxx>
#  include <xsde/cxx/serializer/validating/nmtokens.hxx>
#  include <xsde/cxx/serializer/validating/ncname.hxx>
#  include <xsde/cxx/serializer/validating/id.hxx>
#  include <xsde/cxx/serializer/validating/idref.hxx>
#  include <xsde/cxx/serializer/validating/idrefs.hxx>
#  include <xsde/cxx/serializer/validating/language.hxx>
#  include <xsde/cxx/serializer/validating/uri.hxx>
#  include <xsde/cxx/serializer/validating/qname.hxx>
#endif

#include <xsde/cxx/serializer/validating/base64-binary.hxx>
#include <xsde/cxx/serializer/validating/hex-binary.hxx>

#include <xsde/cxx/serializer/validating/gday.hxx>
#include <xsde/cxx/serializer/validating/gmonth.hxx>
#include <xsde/cxx/serializer/validating/gyear.hxx>
#include <xsde/cxx/serializer/validating/gmonth-day.hxx>
#include <xsde/cxx/serializer/validating/gyear-month.hxx>
#include <xsde/cxx/serializer/validating/date.hxx>
#include <xsde/cxx/serializer/validating/time.hxx>
#include <xsde/cxx/serializer/validating/date-time.hxx>
#include <xsde/cxx/serializer/validating/duration.hxx>

#endif  // XSDE_CXX_SERIALIZER_VALIDATING_XML_SCHEMA_SIMPL_HXX
