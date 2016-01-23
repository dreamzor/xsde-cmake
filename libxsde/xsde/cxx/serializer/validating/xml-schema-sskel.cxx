// file      : xsde/cxx/serializer/validating/xml-schema-sskel.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/serializer/validating/xml-schema-sskel.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
        // any_type_sskel
        //
        void any_type_sskel::
        pre ()
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (any_type_impl_)
            any_type_impl_->pre ();
#endif
        }

        // static/dynamic_type function implementations.
        //
#ifdef XSDE_POLYMORPHIC
        const char* any_type_sskel::
        _static_type ()
        {
          return "anyType http://www.w3.org/2001/XMLSchema";
        }

        const char* any_type_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* any_simple_type_sskel::
        _static_type ()
        {
          return "anySimpleType http://www.w3.org/2001/XMLSchema";
        }

        const char* any_simple_type_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* boolean_sskel::
        _static_type ()
        {
          return "boolean http://www.w3.org/2001/XMLSchema";
        }

        const char* boolean_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* byte_sskel::
        _static_type ()
        {
          return "byte http://www.w3.org/2001/XMLSchema";
        }

        const char* byte_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* unsigned_byte_sskel::
        _static_type ()
        {
          return "unsignedByte http://www.w3.org/2001/XMLSchema";
        }

        const char* unsigned_byte_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* short_sskel::
        _static_type ()
        {
          return "short http://www.w3.org/2001/XMLSchema";
        }

        const char* short_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* unsigned_short_sskel::
        _static_type ()
        {
          return "unsignedShort http://www.w3.org/2001/XMLSchema";
        }

        const char* unsigned_short_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* int_sskel::
        _static_type ()
        {
          return "int http://www.w3.org/2001/XMLSchema";
        }

        const char* int_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* unsigned_int_sskel::
        _static_type ()
        {
          return "unsignedInt http://www.w3.org/2001/XMLSchema";
        }

        const char* unsigned_int_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* long_sskel::
        _static_type ()
        {
          return "long http://www.w3.org/2001/XMLSchema";
        }

        const char* long_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* unsigned_long_sskel::
        _static_type ()
        {
          return "unsignedLong http://www.w3.org/2001/XMLSchema";
        }

        const char* unsigned_long_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* integer_sskel::
        _static_type ()
        {
          return "integer http://www.w3.org/2001/XMLSchema";
        }

        const char* integer_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* negative_integer_sskel::
        _static_type ()
        {
          return "negativeInteger http://www.w3.org/2001/XMLSchema";
        }

        const char* negative_integer_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* non_positive_integer_sskel::
        _static_type ()
        {
          return "nonPositiveInteger http://www.w3.org/2001/XMLSchema";
        }

        const char* non_positive_integer_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* positive_integer_sskel::
        _static_type ()
        {
          return "positiveInteger http://www.w3.org/2001/XMLSchema";
        }

        const char* positive_integer_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* non_negative_integer_sskel::
        _static_type ()
        {
          return "nonNegativeInteger http://www.w3.org/2001/XMLSchema";
        }

        const char* non_negative_integer_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* float_sskel::
        _static_type ()
        {
          return "float http://www.w3.org/2001/XMLSchema";
        }

        const char* float_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* double_sskel::
        _static_type ()
        {
          return "double http://www.w3.org/2001/XMLSchema";
        }

        const char* double_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* decimal_sskel::
        _static_type ()
        {
          return "decimal http://www.w3.org/2001/XMLSchema";
        }

        const char* decimal_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* string_sskel::
        _static_type ()
        {
          return "string http://www.w3.org/2001/XMLSchema";
        }

        const char* string_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* normalized_string_sskel::
        _static_type ()
        {
          return "normalizedString http://www.w3.org/2001/XMLSchema";
        }

        const char* normalized_string_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* token_sskel::
        _static_type ()
        {
          return "token http://www.w3.org/2001/XMLSchema";
        }

        const char* token_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* name_sskel::
        _static_type ()
        {
          return "Name http://www.w3.org/2001/XMLSchema";
        }

        const char* name_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* nmtoken_sskel::
        _static_type ()
        {
          return "NMTOKEN http://www.w3.org/2001/XMLSchema";
        }

        const char* nmtoken_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* nmtokens_sskel::
        _static_type ()
        {
          return "NMTOKENS http://www.w3.org/2001/XMLSchema";
        }

        const char* nmtokens_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* ncname_sskel::
        _static_type ()
        {
          return "NCName http://www.w3.org/2001/XMLSchema";
        }

        const char* ncname_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* id_sskel::
        _static_type ()
        {
          return "ID http://www.w3.org/2001/XMLSchema";
        }

        const char* id_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* idref_sskel::
        _static_type ()
        {
          return "IDREF http://www.w3.org/2001/XMLSchema";
        }

        const char* idref_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* idrefs_sskel::
        _static_type ()
        {
          return "IDREFS http://www.w3.org/2001/XMLSchema";
        }

        const char* idrefs_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* language_sskel::
        _static_type ()
        {
          return "language http://www.w3.org/2001/XMLSchema";
        }

        const char* language_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* uri_sskel::
        _static_type ()
        {
          return "anyURI http://www.w3.org/2001/XMLSchema";
        }

        const char* uri_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* qname_sskel::
        _static_type ()
        {
          return "QName http://www.w3.org/2001/XMLSchema";
        }

        const char* qname_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* base64_binary_sskel::
        _static_type ()
        {
          return "base64Binary http://www.w3.org/2001/XMLSchema";
        }

        const char* base64_binary_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* hex_binary_sskel::
        _static_type ()
        {
          return "hexBinary http://www.w3.org/2001/XMLSchema";
        }

        const char* hex_binary_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* gday_sskel::
        _static_type ()
        {
          return "gDay http://www.w3.org/2001/XMLSchema";
        }

        const char* gday_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* gmonth_sskel::
        _static_type ()
        {
          return "gMonth http://www.w3.org/2001/XMLSchema";
        }

        const char* gmonth_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* gyear_sskel::
        _static_type ()
        {
          return "gYear http://www.w3.org/2001/XMLSchema";
        }

        const char* gyear_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* gmonth_day_sskel::
        _static_type ()
        {
          return "gMonthDay http://www.w3.org/2001/XMLSchema";
        }

        const char* gmonth_day_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* gyear_month_sskel::
        _static_type ()
        {
          return "gYearMonth http://www.w3.org/2001/XMLSchema";
        }

        const char* gyear_month_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* date_sskel::
        _static_type ()
        {
          return "date http://www.w3.org/2001/XMLSchema";
        }

        const char* date_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* time_sskel::
        _static_type ()
        {
          return "time http://www.w3.org/2001/XMLSchema";
        }

        const char* time_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* date_time_sskel::
        _static_type ()
        {
          return "dateTime http://www.w3.org/2001/XMLSchema";
        }

        const char* date_time_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }

        const char* duration_sskel::
        _static_type ()
        {
          return "duration http://www.w3.org/2001/XMLSchema";
        }

        const char* duration_sskel::
        _dynamic_type () const
        {
          return _static_type ();
        }
#endif // XSDE_POLYMORPHIC
      }
    }
  }
}
