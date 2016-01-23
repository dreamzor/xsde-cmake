// file      : xsde/cxx/schema-error.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SCHEMA_ERROR_HXX
#define XSDE_CXX_SCHEMA_ERROR_HXX

namespace xsde
{
  namespace cxx
  {
    struct schema_error
    {
      enum value
      {
        none,
        expected_attribute,
        unexpected_attribute,
        expected_element,
        unexpected_element,
        unexpected_characters,
        invalid_boolean_value,
        invalid_byte_value,
        invalid_unsigned_byte_value,
        invalid_short_value,
        invalid_unsigned_short_value,
        invalid_int_value,
        invalid_unsigned_int_value,
        invalid_long_value,
        invalid_unsigned_long_value,
        invalid_integer_value,
        invalid_negative_integer_value,
        invalid_non_positive_integer_value,
        invalid_positive_integer_value,
        invalid_non_negative_integer_value,
        invalid_float_value,
        invalid_double_value,
        invalid_decimal_value,
        invalid_normalized_string_value,
        invalid_token_value,
        invalid_name_value,
        invalid_nmtoken_value,
        invalid_nmtokens_value,
        invalid_ncname_value,
        invalid_id_value,
        invalid_idref_value,
        invalid_idrefs_value,
        invalid_language_value,
        invalid_qname_value,
        invalid_base64_binary_value,
        invalid_hex_binary_value,
        invalid_gday_value,
        invalid_gmonth_value,
        invalid_gyear_value,
        invalid_gmonth_day_value,
        invalid_gyear_month_value,
        invalid_date_value,
        invalid_time_value,
        invalid_date_time_value,
        invalid_duration_value,
        value_greater_than_max,
        value_less_than_min,
        value_not_in_enumeration,
        value_pattern_mismatch,
        length_greater_than_max,
        length_less_than_min,
        length_not_equal_prescribed,
        invalid_xsi_type,
        not_derived
      };

      schema_error (value v);

      operator value () const
      {
        return v_;
      }

      static const char*
      text (value);

    private:
      value v_;
    };
  }
}

#include <xsde/cxx/schema-error.ixx>

#endif  // XSDE_CXX_SCHEMA_ERROR_HXX
