// file      : xsde/cxx/parser/validating/xml-schema-pimpl.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_VALIDATING_XML_SCHEMA_PIMPL_HXX
#define XSDE_CXX_PARSER_VALIDATING_XML_SCHEMA_PIMPL_HXX

#include <xsde/cxx/parser/validating/xml-schema-pskel.hxx>

#include <xsde/cxx/parser/validating/any-type.hxx>

#ifdef XSDE_STL
#  include <xsde/cxx/parser/validating/any-simple-type-stl.hxx>
#else
#  include <xsde/cxx/parser/validating/any-simple-type.hxx>
#endif

#include <xsde/cxx/parser/validating/boolean.hxx>
#include <xsde/cxx/parser/validating/byte.hxx>
#include <xsde/cxx/parser/validating/unsigned-byte.hxx>
#include <xsde/cxx/parser/validating/byte.hxx>
#include <xsde/cxx/parser/validating/unsigned-byte.hxx>
#include <xsde/cxx/parser/validating/short.hxx>
#include <xsde/cxx/parser/validating/unsigned-short.hxx>
#include <xsde/cxx/parser/validating/int.hxx>
#include <xsde/cxx/parser/validating/unsigned-int.hxx>

#ifdef XSDE_LONGLONG
#  include <xsde/cxx/parser/validating/long-long.hxx>
#  include <xsde/cxx/parser/validating/unsigned-long-long.hxx>
#else
#  include <xsde/cxx/parser/validating/long.hxx>
#  include <xsde/cxx/parser/validating/unsigned-long.hxx>
#endif

#include <xsde/cxx/parser/validating/integer.hxx>
#include <xsde/cxx/parser/validating/negative-integer.hxx>
#include <xsde/cxx/parser/validating/non-positive-integer.hxx>
#include <xsde/cxx/parser/validating/positive-integer.hxx>
#include <xsde/cxx/parser/validating/non-negative-integer.hxx>
#include <xsde/cxx/parser/validating/float.hxx>
#include <xsde/cxx/parser/validating/double.hxx>
#include <xsde/cxx/parser/validating/decimal.hxx>

#ifdef XSDE_STL
#  include <xsde/cxx/parser/validating/string-stl.hxx>
#  include <xsde/cxx/parser/validating/normalized-string-stl.hxx>
#  include <xsde/cxx/parser/validating/token-stl.hxx>
#  include <xsde/cxx/parser/validating/name-stl.hxx>
#  include <xsde/cxx/parser/validating/nmtoken-stl.hxx>
#  include <xsde/cxx/parser/validating/nmtokens-stl.hxx>
#  include <xsde/cxx/parser/validating/ncname-stl.hxx>
#  include <xsde/cxx/parser/validating/id-stl.hxx>
#  include <xsde/cxx/parser/validating/idref-stl.hxx>
#  include <xsde/cxx/parser/validating/idrefs-stl.hxx>
#  include <xsde/cxx/parser/validating/language-stl.hxx>
#  include <xsde/cxx/parser/validating/uri-stl.hxx>
#  include <xsde/cxx/parser/validating/qname-stl.hxx>
#else
#  include <xsde/cxx/parser/validating/string.hxx>
#  include <xsde/cxx/parser/validating/normalized-string.hxx>
#  include <xsde/cxx/parser/validating/token.hxx>
#  include <xsde/cxx/parser/validating/name.hxx>
#  include <xsde/cxx/parser/validating/nmtoken.hxx>
#  include <xsde/cxx/parser/validating/nmtokens.hxx>
#  include <xsde/cxx/parser/validating/ncname.hxx>
#  include <xsde/cxx/parser/validating/id.hxx>
#  include <xsde/cxx/parser/validating/idref.hxx>
#  include <xsde/cxx/parser/validating/idrefs.hxx>
#  include <xsde/cxx/parser/validating/language.hxx>
#  include <xsde/cxx/parser/validating/uri.hxx>
#  include <xsde/cxx/parser/validating/qname.hxx>
#endif

#include <xsde/cxx/parser/validating/base64-binary.hxx>
#include <xsde/cxx/parser/validating/hex-binary.hxx>

#include <xsde/cxx/parser/validating/gday.hxx>
#include <xsde/cxx/parser/validating/gmonth.hxx>
#include <xsde/cxx/parser/validating/gyear.hxx>
#include <xsde/cxx/parser/validating/gmonth-day.hxx>
#include <xsde/cxx/parser/validating/gyear-month.hxx>
#include <xsde/cxx/parser/validating/date.hxx>
#include <xsde/cxx/parser/validating/time.hxx>
#include <xsde/cxx/parser/validating/date-time.hxx>
#include <xsde/cxx/parser/validating/duration.hxx>

#endif  // XSDE_CXX_PARSER_VALIDATING_XML_SCHEMA_PIMPL_HXX
