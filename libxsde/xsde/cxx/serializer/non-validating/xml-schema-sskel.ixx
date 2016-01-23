// file      : xsde/cxx/serializer/non-validating/xml-schema-sskel.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace non_validating
      {
        // any_type_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline any_type_sskel::
        any_type_sskel ()
            : any_type_impl_ (0)
        {
        }

        inline any_type_sskel::
        any_type_sskel (any_type_sskel* impl, void*)
            : complex_content (impl, 0), any_type_impl_ (impl)
        {
        }
#endif

        // any_simple_type_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline any_simple_type_sskel::
        any_simple_type_sskel ()
            : any_simple_type_impl_ (0)
        {
        }

        inline any_simple_type_sskel::
        any_simple_type_sskel (any_simple_type_sskel* impl, void*)
            : simple_content (impl, 0), any_simple_type_impl_ (impl)
        {
        }
#endif

        // boolean_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline boolean_sskel::
        boolean_sskel ()
            : boolean_impl_ (0)
        {
        }

        inline boolean_sskel::
        boolean_sskel (boolean_sskel* impl, void*)
            : simple_content (impl, 0), boolean_impl_ (impl)
        {
        }
#endif

        // byte_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline byte_sskel::
        byte_sskel ()
            : byte_impl_ (0)
        {
        }

        inline byte_sskel::
        byte_sskel (byte_sskel* impl, void*)
            : simple_content (impl, 0), byte_impl_ (impl)
        {
        }
#endif

        // unsigned_byte_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline unsigned_byte_sskel::
        unsigned_byte_sskel ()
            : unsigned_byte_impl_ (0)
        {
        }

        inline unsigned_byte_sskel::
        unsigned_byte_sskel (unsigned_byte_sskel* impl, void*)
            : simple_content (impl, 0), unsigned_byte_impl_ (impl)
        {
        }
#endif

        // short_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline short_sskel::
        short_sskel ()
            : short_impl_ (0)
        {
        }

        inline short_sskel::
        short_sskel (short_sskel* impl, void*)
            : simple_content (impl, 0), short_impl_ (impl)
        {
        }
#endif

        // unsigned_short_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline unsigned_short_sskel::
        unsigned_short_sskel ()
            : unsigned_short_impl_ (0)
        {
        }

        inline unsigned_short_sskel::
        unsigned_short_sskel (unsigned_short_sskel* impl, void*)
            : simple_content (impl, 0), unsigned_short_impl_ (impl)
        {
        }
#endif

        // int_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline int_sskel::
        int_sskel ()
            : int_impl_ (0)
        {
        }

        inline int_sskel::
        int_sskel (int_sskel* impl, void*)
            : simple_content (impl, 0), int_impl_ (impl)
        {
        }
#endif

        // unsigned_int_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline unsigned_int_sskel::
        unsigned_int_sskel ()
            : unsigned_int_impl_ (0)
        {
        }

        inline unsigned_int_sskel::
        unsigned_int_sskel (unsigned_int_sskel* impl, void*)
            : simple_content (impl, 0), unsigned_int_impl_ (impl)
        {
        }
#endif

        // long_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline long_sskel::
        long_sskel ()
            : long_impl_ (0)
        {
        }

        inline long_sskel::
        long_sskel (long_sskel* impl, void*)
            : simple_content (impl, 0), long_impl_ (impl)
        {
        }
#endif

        // unsigned_long_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline unsigned_long_sskel::
        unsigned_long_sskel ()
            : unsigned_long_impl_ (0)
        {
        }

        inline unsigned_long_sskel::
        unsigned_long_sskel (unsigned_long_sskel* impl, void*)
            : simple_content (impl, 0), unsigned_long_impl_ (impl)
        {
        }
#endif

        // integer_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline integer_sskel::
        integer_sskel ()
            : integer_impl_ (0)
        {
        }

        inline integer_sskel::
        integer_sskel (integer_sskel* impl, void*)
            : simple_content (impl, 0), integer_impl_ (impl)
        {
        }
#endif

        // negative_integer_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline negative_integer_sskel::
        negative_integer_sskel ()
            : negative_integer_impl_ (0)
        {
        }

        inline negative_integer_sskel::
        negative_integer_sskel (negative_integer_sskel* impl, void*)
            : simple_content (impl, 0), negative_integer_impl_ (impl)
        {
        }
#endif

        // non_positive_integer_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline non_positive_integer_sskel::
        non_positive_integer_sskel ()
            : non_positive_integer_impl_ (0)
        {
        }

        inline non_positive_integer_sskel::
        non_positive_integer_sskel (non_positive_integer_sskel* impl, void*)
            : simple_content (impl, 0), non_positive_integer_impl_ (impl)
        {
        }
#endif

        // positive_integer_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline positive_integer_sskel::
        positive_integer_sskel ()
            : positive_integer_impl_ (0)
        {
        }

        inline positive_integer_sskel::
        positive_integer_sskel (positive_integer_sskel* impl, void*)
            : simple_content (impl, 0), positive_integer_impl_ (impl)
        {
        }
#endif

        // non_negative_integer_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline non_negative_integer_sskel::
        non_negative_integer_sskel ()
            : non_negative_integer_impl_ (0)
        {
        }

        inline non_negative_integer_sskel::
        non_negative_integer_sskel (non_negative_integer_sskel* impl, void*)
            : simple_content (impl, 0), non_negative_integer_impl_ (impl)
        {
        }
#endif

        // float_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline float_sskel::
        float_sskel ()
            : float_impl_ (0)
        {
        }

        inline float_sskel::
        float_sskel (float_sskel* impl, void*)
            : simple_content (impl, 0), float_impl_ (impl)
        {
        }
#endif

        // double_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline double_sskel::
        double_sskel ()
            : double_impl_ (0)
        {
        }

        inline double_sskel::
        double_sskel (double_sskel* impl, void*)
            : simple_content (impl, 0), double_impl_ (impl)
        {
        }
#endif

        // decimal_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline decimal_sskel::
        decimal_sskel ()
            : decimal_impl_ (0)
        {
        }

        inline decimal_sskel::
        decimal_sskel (decimal_sskel* impl, void*)
            : simple_content (impl, 0), decimal_impl_ (impl)
        {
        }
#endif

        // string_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline string_sskel::
        string_sskel ()
            : string_impl_ (0)
        {
        }

        inline string_sskel::
        string_sskel (string_sskel* impl, void*)
            : simple_content (impl, 0), string_impl_ (impl)
        {
        }
#endif

        // normalized_string_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline normalized_string_sskel::
        normalized_string_sskel ()
            : normalized_string_impl_ (0)
        {
        }

        inline normalized_string_sskel::
        normalized_string_sskel (normalized_string_sskel* impl, void*)
            : string_sskel (impl, 0), normalized_string_impl_ (impl)
        {
        }
#endif

        // token_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline token_sskel::
        token_sskel ()
            : token_impl_ (0)
        {
        }

        inline token_sskel::
        token_sskel (token_sskel* impl, void*)
            : normalized_string_sskel (impl, 0), token_impl_ (impl)
        {
        }
#endif

        // name_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline name_sskel::
        name_sskel ()
            : name_impl_ (0)
        {
        }

        inline name_sskel::
        name_sskel (name_sskel* impl, void*)
            : token_sskel (impl, 0), name_impl_ (impl)
        {
        }
#endif

        // nmtoken_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline nmtoken_sskel::
        nmtoken_sskel ()
            : nmtoken_impl_ (0)
        {
        }

        inline nmtoken_sskel::
        nmtoken_sskel (nmtoken_sskel* impl, void*)
            : token_sskel (impl, 0), nmtoken_impl_ (impl)
        {
        }
#endif

        // nmtokens_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline nmtokens_sskel::
        nmtokens_sskel ()
            : nmtokens_impl_ (0)
        {
        }

        inline nmtokens_sskel::
        nmtokens_sskel (nmtokens_sskel* impl, void*)
            : simple_content (impl, 0), nmtokens_impl_ (impl)
        {
        }
#endif

        // ncname_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline ncname_sskel::
        ncname_sskel ()
            : ncname_impl_ (0)
        {
        }

        inline ncname_sskel::
        ncname_sskel (ncname_sskel* impl, void*)
            : name_sskel (impl, 0), ncname_impl_ (impl)
        {
        }
#endif

        // id_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline id_sskel::
        id_sskel ()
            : id_impl_ (0)
        {
        }

        inline id_sskel::
        id_sskel (id_sskel* impl, void*)
            : ncname_sskel (impl, 0), id_impl_ (impl)
        {
        }
#endif

        // idref_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline idref_sskel::
        idref_sskel ()
            : idref_impl_ (0)
        {
        }

        inline idref_sskel::
        idref_sskel (idref_sskel* impl, void*)
            : ncname_sskel (impl, 0), idref_impl_ (impl)
        {
        }
#endif

        // idrefs_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline idrefs_sskel::
        idrefs_sskel ()
            : idrefs_impl_ (0)
        {
        }

        inline idrefs_sskel::
        idrefs_sskel (idrefs_sskel* impl, void*)
            : simple_content (impl, 0), idrefs_impl_ (impl)
        {
        }
#endif

        // language_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline language_sskel::
        language_sskel ()
            : language_impl_ (0)
        {
        }

        inline language_sskel::
        language_sskel (language_sskel* impl, void*)
            : token_sskel (impl, 0), language_impl_ (impl)
        {
        }
#endif

        // uri_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline uri_sskel::
        uri_sskel ()
            : uri_impl_ (0)
        {
        }

        inline uri_sskel::
        uri_sskel (uri_sskel* impl, void*)
            : simple_content (impl, 0), uri_impl_ (impl)
        {
        }
#endif

        // qname_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline qname_sskel::
        qname_sskel ()
            : qname_impl_ (0)
        {
        }

        inline qname_sskel::
        qname_sskel (qname_sskel* impl, void*)
            : simple_content (impl, 0), qname_impl_ (impl)
        {
        }
#endif

        // base64_binary_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline base64_binary_sskel::
        base64_binary_sskel ()
            : base64_binary_impl_ (0)
        {
        }

        inline base64_binary_sskel::
        base64_binary_sskel (base64_binary_sskel* impl, void*)
            : simple_content (impl, 0), base64_binary_impl_ (impl)
        {
        }
#endif

        // hex_binary_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline hex_binary_sskel::
        hex_binary_sskel ()
            : hex_binary_impl_ (0)
        {
        }

        inline hex_binary_sskel::
        hex_binary_sskel (hex_binary_sskel* impl, void*)
            : simple_content (impl, 0), hex_binary_impl_ (impl)
        {
        }
#endif

        // gday_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline gday_sskel::
        gday_sskel ()
            : gday_impl_ (0)
        {
        }

        inline gday_sskel::
        gday_sskel (gday_sskel* impl, void*)
            : simple_content (impl, 0), gday_impl_ (impl)
        {
        }
#endif

        // gmonth_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline gmonth_sskel::
        gmonth_sskel ()
            : gmonth_impl_ (0)
        {
        }

        inline gmonth_sskel::
        gmonth_sskel (gmonth_sskel* impl, void*)
            : simple_content (impl, 0), gmonth_impl_ (impl)
        {
        }
#endif

        // gyear_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline gyear_sskel::
        gyear_sskel ()
            : gyear_impl_ (0)
        {
        }

        inline gyear_sskel::
        gyear_sskel (gyear_sskel* impl, void*)
            : simple_content (impl, 0), gyear_impl_ (impl)
        {
        }
#endif

        // gmonth_day_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline gmonth_day_sskel::
        gmonth_day_sskel ()
            : gmonth_day_impl_ (0)
        {
        }

        inline gmonth_day_sskel::
        gmonth_day_sskel (gmonth_day_sskel* impl, void*)
            : simple_content (impl, 0), gmonth_day_impl_ (impl)
        {
        }
#endif

        // gyear_month_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline gyear_month_sskel::
        gyear_month_sskel ()
            : gyear_month_impl_ (0)
        {
        }

        inline gyear_month_sskel::
        gyear_month_sskel (gyear_month_sskel* impl, void*)
            : simple_content (impl, 0), gyear_month_impl_ (impl)
        {
        }
#endif

        // date_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline date_sskel::
        date_sskel ()
            : date_impl_ (0)
        {
        }

        inline date_sskel::
        date_sskel (date_sskel* impl, void*)
            : simple_content (impl, 0), date_impl_ (impl)
        {
        }
#endif

        // time_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline time_sskel::
        time_sskel ()
            : time_impl_ (0)
        {
        }

        inline time_sskel::
        time_sskel (time_sskel* impl, void*)
            : simple_content (impl, 0), time_impl_ (impl)
        {
        }
#endif

        // date_time_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline date_time_sskel::
        date_time_sskel ()
            : date_time_impl_ (0)
        {
        }

        inline date_time_sskel::
        date_time_sskel (date_time_sskel* impl, void*)
            : simple_content (impl, 0), date_time_impl_ (impl)
        {
        }
#endif

        // duration_sskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline duration_sskel::
        duration_sskel ()
            : duration_impl_ (0)
        {
        }

        inline duration_sskel::
        duration_sskel (duration_sskel* impl, void*)
            : simple_content (impl, 0), duration_impl_ (impl)
        {
        }
#endif
      }
    }
  }
}
