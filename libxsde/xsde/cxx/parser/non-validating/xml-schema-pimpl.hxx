// file      : xsde/cxx/parser/non-validating/xml-schema-pimpl.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_NON_VALIDATING_XML_SCHEMA_PIMPL_HXX
#define XSDE_CXX_PARSER_NON_VALIDATING_XML_SCHEMA_PIMPL_HXX

#include <xsde/cxx/parser/non-validating/xml-schema-pskel.hxx>

#include <xsde/cxx/parser/non-validating/any-type.hxx>

#ifdef XSDE_STL
#  include <xsde/cxx/parser/non-validating/any-simple-type-stl.hxx>
#else
#  include <xsde/cxx/parser/non-validating/any-simple-type.hxx>
#endif

#include <xsde/cxx/parser/non-validating/boolean.hxx>
#include <xsde/cxx/parser/non-validating/byte.hxx>
#include <xsde/cxx/parser/non-validating/unsigned-byte.hxx>
#include <xsde/cxx/parser/non-validating/byte.hxx>
#include <xsde/cxx/parser/non-validating/unsigned-byte.hxx>
#include <xsde/cxx/parser/non-validating/short.hxx>
#include <xsde/cxx/parser/non-validating/unsigned-short.hxx>
#include <xsde/cxx/parser/non-validating/int.hxx>
#include <xsde/cxx/parser/non-validating/unsigned-int.hxx>

#ifdef XSDE_LONGLONG
#  include <xsde/cxx/parser/non-validating/long-long.hxx>
#  include <xsde/cxx/parser/non-validating/unsigned-long-long.hxx>
#else
#  include <xsde/cxx/parser/non-validating/long.hxx>
#  include <xsde/cxx/parser/non-validating/unsigned-long.hxx>
#endif

#include <xsde/cxx/parser/non-validating/integer.hxx>
#include <xsde/cxx/parser/non-validating/negative-integer.hxx>
#include <xsde/cxx/parser/non-validating/non-positive-integer.hxx>
#include <xsde/cxx/parser/non-validating/positive-integer.hxx>
#include <xsde/cxx/parser/non-validating/non-negative-integer.hxx>
#include <xsde/cxx/parser/non-validating/float.hxx>
#include <xsde/cxx/parser/non-validating/double.hxx>
#include <xsde/cxx/parser/non-validating/decimal.hxx>

#ifdef XSDE_STL
#  include <xsde/cxx/parser/non-validating/string-stl.hxx>
#  include <xsde/cxx/parser/non-validating/normalized-string-stl.hxx>
#  include <xsde/cxx/parser/non-validating/token-stl.hxx>
#  include <xsde/cxx/parser/non-validating/name-stl.hxx>
#  include <xsde/cxx/parser/non-validating/nmtoken-stl.hxx>
#  include <xsde/cxx/parser/non-validating/nmtokens-stl.hxx>
#  include <xsde/cxx/parser/non-validating/ncname-stl.hxx>
#  include <xsde/cxx/parser/non-validating/id-stl.hxx>
#  include <xsde/cxx/parser/non-validating/idref-stl.hxx>
#  include <xsde/cxx/parser/non-validating/idrefs-stl.hxx>
#  include <xsde/cxx/parser/non-validating/language-stl.hxx>
#  include <xsde/cxx/parser/non-validating/uri-stl.hxx>
#  include <xsde/cxx/parser/non-validating/qname-stl.hxx>
#else
#  include <xsde/cxx/parser/non-validating/string.hxx>
#  include <xsde/cxx/parser/non-validating/normalized-string.hxx>
#  include <xsde/cxx/parser/non-validating/token.hxx>
#  include <xsde/cxx/parser/non-validating/name.hxx>
#  include <xsde/cxx/parser/non-validating/nmtoken.hxx>
#  include <xsde/cxx/parser/non-validating/nmtokens.hxx>
#  include <xsde/cxx/parser/non-validating/ncname.hxx>
#  include <xsde/cxx/parser/non-validating/id.hxx>
#  include <xsde/cxx/parser/non-validating/idref.hxx>
#  include <xsde/cxx/parser/non-validating/idrefs.hxx>
#  include <xsde/cxx/parser/non-validating/language.hxx>
#  include <xsde/cxx/parser/non-validating/uri.hxx>
#  include <xsde/cxx/parser/non-validating/qname.hxx>
#endif

#include <xsde/cxx/parser/non-validating/base64-binary.hxx>
#include <xsde/cxx/parser/non-validating/hex-binary.hxx>

#include <xsde/cxx/parser/non-validating/gday.hxx>
#include <xsde/cxx/parser/non-validating/gmonth.hxx>
#include <xsde/cxx/parser/non-validating/gyear.hxx>
#include <xsde/cxx/parser/non-validating/gmonth-day.hxx>
#include <xsde/cxx/parser/non-validating/gyear-month.hxx>
#include <xsde/cxx/parser/non-validating/date.hxx>
#include <xsde/cxx/parser/non-validating/time.hxx>
#include <xsde/cxx/parser/non-validating/date-time.hxx>
#include <xsde/cxx/parser/non-validating/duration.hxx>

#endif  // XSDE_CXX_PARSER_NON_VALIDATING_XML_SCHEMA_PIMPL_HXX
