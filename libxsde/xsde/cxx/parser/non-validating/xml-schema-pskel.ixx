// file      : xsde/cxx/parser/non-validating/xml-schema-pskel.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace non_validating
      {
        // any_type_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline any_type_pskel::
        any_type_pskel ()
            : any_type_impl_ (0)
        {
        }

        inline any_type_pskel::
        any_type_pskel (any_type_pskel* impl, void*)
            : complex_content (impl, 0), any_type_impl_ (impl)
        {
        }
#endif

        // any_simple_type_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline any_simple_type_pskel::
        any_simple_type_pskel ()
            : any_simple_type_impl_ (0)
        {
        }

        inline any_simple_type_pskel::
        any_simple_type_pskel (any_simple_type_pskel* impl, void*)
            : simple_content (impl, 0), any_simple_type_impl_ (impl)
        {
        }
#endif

        // boolean_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline boolean_pskel::
        boolean_pskel ()
            : boolean_impl_ (0)
        {
        }

        inline boolean_pskel::
        boolean_pskel (boolean_pskel* impl, void*)
            : simple_content (impl, 0), boolean_impl_ (impl)
        {
        }
#endif

        // byte_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline byte_pskel::
        byte_pskel ()
            : byte_impl_ (0)
        {
        }

        inline byte_pskel::
        byte_pskel (byte_pskel* impl, void*)
            : simple_content (impl, 0), byte_impl_ (impl)
        {
        }
#endif

        // unsigned_byte_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline unsigned_byte_pskel::
        unsigned_byte_pskel ()
            : unsigned_byte_impl_ (0)
        {
        }

        inline unsigned_byte_pskel::
        unsigned_byte_pskel (unsigned_byte_pskel* impl, void*)
            : simple_content (impl, 0), unsigned_byte_impl_ (impl)
        {
        }
#endif

        // short_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline short_pskel::
        short_pskel ()
            : short_impl_ (0)
        {
        }

        inline short_pskel::
        short_pskel (short_pskel* impl, void*)
            : simple_content (impl, 0), short_impl_ (impl)
        {
        }
#endif

        // unsigned_short_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline unsigned_short_pskel::
        unsigned_short_pskel ()
            : unsigned_short_impl_ (0)
        {
        }

        inline unsigned_short_pskel::
        unsigned_short_pskel (unsigned_short_pskel* impl, void*)
            : simple_content (impl, 0), unsigned_short_impl_ (impl)
        {
        }
#endif

        // int_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline int_pskel::
        int_pskel ()
            : int_impl_ (0)
        {
        }

        inline int_pskel::
        int_pskel (int_pskel* impl, void*)
            : simple_content (impl, 0), int_impl_ (impl)
        {
        }
#endif

        // unsigned_int_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline unsigned_int_pskel::
        unsigned_int_pskel ()
            : unsigned_int_impl_ (0)
        {
        }

        inline unsigned_int_pskel::
        unsigned_int_pskel (unsigned_int_pskel* impl, void*)
            : simple_content (impl, 0), unsigned_int_impl_ (impl)
        {
        }
#endif

        // long_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline long_pskel::
        long_pskel ()
            : long_impl_ (0)
        {
        }

        inline long_pskel::
        long_pskel (long_pskel* impl, void*)
            : simple_content (impl, 0), long_impl_ (impl)
        {
        }
#endif

        // unsigned_long_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline unsigned_long_pskel::
        unsigned_long_pskel ()
            : unsigned_long_impl_ (0)
        {
        }

        inline unsigned_long_pskel::
        unsigned_long_pskel (unsigned_long_pskel* impl, void*)
            : simple_content (impl, 0), unsigned_long_impl_ (impl)
        {
        }
#endif

        // integer_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline integer_pskel::
        integer_pskel ()
            : integer_impl_ (0)
        {
        }

        inline integer_pskel::
        integer_pskel (integer_pskel* impl, void*)
            : simple_content (impl, 0), integer_impl_ (impl)
        {
        }
#endif

        // negative_integer_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline negative_integer_pskel::
        negative_integer_pskel ()
            : negative_integer_impl_ (0)
        {
        }

        inline negative_integer_pskel::
        negative_integer_pskel (negative_integer_pskel* impl, void*)
            : simple_content (impl, 0), negative_integer_impl_ (impl)
        {
        }
#endif

        // non_positive_integer_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline non_positive_integer_pskel::
        non_positive_integer_pskel ()
            : non_positive_integer_impl_ (0)
        {
        }

        inline non_positive_integer_pskel::
        non_positive_integer_pskel (non_positive_integer_pskel* impl, void*)
            : simple_content (impl, 0), non_positive_integer_impl_ (impl)
        {
        }
#endif

        // positive_integer_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline positive_integer_pskel::
        positive_integer_pskel ()
            : positive_integer_impl_ (0)
        {
        }

        inline positive_integer_pskel::
        positive_integer_pskel (positive_integer_pskel* impl, void*)
            : simple_content (impl, 0), positive_integer_impl_ (impl)
        {
        }
#endif

        // non_negative_integer_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline non_negative_integer_pskel::
        non_negative_integer_pskel ()
            : non_negative_integer_impl_ (0)
        {
        }

        inline non_negative_integer_pskel::
        non_negative_integer_pskel (non_negative_integer_pskel* impl, void*)
            : simple_content (impl, 0), non_negative_integer_impl_ (impl)
        {
        }
#endif

        // float_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline float_pskel::
        float_pskel ()
            : float_impl_ (0)
        {
        }

        inline float_pskel::
        float_pskel (float_pskel* impl, void*)
            : simple_content (impl, 0), float_impl_ (impl)
        {
        }
#endif

        // double_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline double_pskel::
        double_pskel ()
            : double_impl_ (0)
        {
        }

        inline double_pskel::
        double_pskel (double_pskel* impl, void*)
            : simple_content (impl, 0), double_impl_ (impl)
        {
        }
#endif

        // decimal_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline decimal_pskel::
        decimal_pskel ()
            : decimal_impl_ (0)
        {
        }

        inline decimal_pskel::
        decimal_pskel (decimal_pskel* impl, void*)
            : simple_content (impl, 0), decimal_impl_ (impl)
        {
        }
#endif

        // string_facets
        //
        inline string_facets::
        string_facets ()
        {
          facets_.whitespace_ = 0;
        }

        inline void string_facets::
        _whitespace_facet (unsigned int v)
        {
          facets_.whitespace_ = v;
        }

        // string_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline string_pskel::
        string_pskel ()
            : string_impl_ (0)
        {
        }

        inline string_pskel::
        string_pskel (string_pskel* impl, void*)
            : simple_content (impl, 0), string_impl_ (impl)
        {
        }
#endif
        inline const string_facets::facets& string_pskel::
        _facets () const
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (parent_ != 0)
            return static_cast<const string_pskel&> (*parent_).facets_;
          else
#endif
          return facets_;
        }

        // normalized_string_pskel
        //
        inline normalized_string_pskel::
        normalized_string_pskel ()
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          normalized_string_impl_ = 0;
#endif
          _whitespace_facet (1); // replace
        }

#ifdef XSDE_REUSE_STYLE_TIEIN
        inline normalized_string_pskel::
        normalized_string_pskel (normalized_string_pskel* impl, void*)
            : simple_content (impl, 0), normalized_string_impl_ (impl)
        {
          _whitespace_facet (1); // replace
        }
#endif
        inline const string_facets::facets& normalized_string_pskel::
        _facets () const
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (parent_ != 0)
            return static_cast<const normalized_string_pskel&> (
              *parent_).facets_;
          else
#endif
          return facets_;
        }

        // token_pskel
        //
        inline token_pskel::
        token_pskel ()
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          token_impl_ = 0;
#endif
          _whitespace_facet (2); // collapse
        }

#ifdef XSDE_REUSE_STYLE_TIEIN
        inline token_pskel::
        token_pskel (token_pskel* impl, void*)
            : simple_content (impl, 0), token_impl_ (impl)
        {
          _whitespace_facet (2); // collapse
        }
#endif
        inline const string_facets::facets& token_pskel::
        _facets () const
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (parent_ != 0)
            return static_cast<const token_pskel&> (*parent_).facets_;
          else
#endif
          return facets_;
        }

        // name_pskel
        //
        inline name_pskel::
        name_pskel ()
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          name_impl_ = 0;
#endif
          _whitespace_facet (2); // collapse
        }

#ifdef XSDE_REUSE_STYLE_TIEIN
        inline name_pskel::
        name_pskel (name_pskel* impl, void*)
            : simple_content (impl, 0), name_impl_ (impl)
        {
          _whitespace_facet (2); // collapse
        }
#endif
        inline const string_facets::facets& name_pskel::
        _facets () const
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (parent_ != 0)
            return static_cast<const name_pskel&> (*parent_).facets_;
          else
#endif
          return facets_;
        }

        // nmtoken_pskel
        //
        inline nmtoken_pskel::
        nmtoken_pskel ()
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          nmtoken_impl_ = 0;
#endif
          _whitespace_facet (2); // collapse
        }

#ifdef XSDE_REUSE_STYLE_TIEIN
        inline nmtoken_pskel::
        nmtoken_pskel (nmtoken_pskel* impl, void*)
            : simple_content (impl, 0), nmtoken_impl_ (impl)
        {
          _whitespace_facet (2); // collapse
        }
#endif
        inline const string_facets::facets& nmtoken_pskel::
        _facets () const
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (parent_ != 0)
            return static_cast<const nmtoken_pskel&> (*parent_).facets_;
          else
#endif
          return facets_;
        }

        // nmtokens_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline nmtokens_pskel::
        nmtokens_pskel ()
            : nmtokens_impl_ (0)
        {
        }

        inline nmtokens_pskel::
        nmtokens_pskel (nmtokens_pskel* impl, void*)
            : list_base (impl, 0), nmtokens_impl_ (impl)
        {
        }
#endif

        // ncname_pskel
        //
        inline ncname_pskel::
        ncname_pskel ()
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          ncname_impl_ = 0;
#endif
          _whitespace_facet (2); // collapse
        }

#ifdef XSDE_REUSE_STYLE_TIEIN
        inline ncname_pskel::
        ncname_pskel (ncname_pskel* impl, void*)
            : simple_content (impl, 0), ncname_impl_ (impl)
        {
          _whitespace_facet (2); // collapse
        }
#endif
        inline const string_facets::facets& ncname_pskel::
        _facets () const
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (parent_ != 0)
            return static_cast<const ncname_pskel&> (*parent_).facets_;
          else
#endif
          return facets_;
        }

        // id_pskel
        //
        inline id_pskel::
        id_pskel ()
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          id_impl_ = 0;
#endif
          _whitespace_facet (2); // collapse
        }

#ifdef XSDE_REUSE_STYLE_TIEIN
        inline id_pskel::
        id_pskel (id_pskel* impl, void*)
            : simple_content (impl, 0), id_impl_ (impl)
        {
          _whitespace_facet (2); // collapse
        }
#endif
        inline const string_facets::facets& id_pskel::
        _facets () const
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (parent_ != 0)
            return static_cast<const id_pskel&> (*parent_).facets_;
          else
#endif
          return facets_;
        }

        // idref_pskel
        //
        inline idref_pskel::
        idref_pskel ()
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          idref_impl_ = 0;
#endif
          _whitespace_facet (2); // collapse
        }

#ifdef XSDE_REUSE_STYLE_TIEIN
        inline idref_pskel::
        idref_pskel (idref_pskel* impl, void*)
            : simple_content (impl, 0), idref_impl_ (impl)
        {
          _whitespace_facet (2); // collapse
        }
#endif
        inline const string_facets::facets& idref_pskel::
        _facets () const
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (parent_ != 0)
            return static_cast<const idref_pskel&> (*parent_).facets_;
          else
#endif
          return facets_;
        }

        // idrefs_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline idrefs_pskel::
        idrefs_pskel ()
            : idrefs_impl_ (0)
        {
        }

        inline idrefs_pskel::
        idrefs_pskel (idrefs_pskel* impl, void*)
            : list_base (impl, 0), idrefs_impl_ (impl)
        {
        }
#endif

        // language_pskel
        //
        inline language_pskel::
        language_pskel ()
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          language_impl_ = 0;
#endif
          _whitespace_facet (2); // collapse
        }

#ifdef XSDE_REUSE_STYLE_TIEIN
        inline language_pskel::
        language_pskel (language_pskel* impl, void*)
            : simple_content (impl, 0), language_impl_ (impl)
        {
          _whitespace_facet (2); // collapse
        }
#endif
        inline const string_facets::facets& language_pskel::
        _facets () const
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (parent_ != 0)
            return static_cast<const language_pskel&> (*parent_).facets_;
          else
#endif
          return facets_;
        }

        // uri_pskel
        //
        inline uri_pskel::
        uri_pskel ()
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          uri_impl_ = 0;
#endif
          _whitespace_facet (2); // collapse
        }

#ifdef XSDE_REUSE_STYLE_TIEIN
        inline uri_pskel::
        uri_pskel (uri_pskel* impl, void*)
            : simple_content (impl, 0), uri_impl_ (impl)
        {
          _whitespace_facet (2); // collapse
        }
#endif
        inline const string_facets::facets& uri_pskel::
        _facets () const
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (parent_ != 0)
            return static_cast<const uri_pskel&> (*parent_).facets_;
          else
#endif
          return facets_;
        }

        // qname_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline qname_pskel::
        qname_pskel ()
            : qname_impl_ (0)
        {
        }

        inline qname_pskel::
        qname_pskel (qname_pskel* impl, void*)
            : simple_content (impl, 0), qname_impl_ (impl)
        {
        }
#endif

        // base64_binary_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline base64_binary_pskel::
        base64_binary_pskel ()
            : base64_binary_impl_ (0)
        {
        }

        inline base64_binary_pskel::
        base64_binary_pskel (base64_binary_pskel* impl, void*)
            : simple_content (impl, 0), base64_binary_impl_ (impl)
        {
        }
#endif

        // hex_binary_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline hex_binary_pskel::
        hex_binary_pskel ()
            : hex_binary_impl_ (0)
        {
        }

        inline hex_binary_pskel::
        hex_binary_pskel (hex_binary_pskel* impl, void*)
            : simple_content (impl, 0), hex_binary_impl_ (impl)
        {
        }
#endif

        // gday_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline gday_pskel::
        gday_pskel ()
            : gday_impl_ (0)
        {
        }

        inline gday_pskel::
        gday_pskel (gday_pskel* impl, void*)
            : simple_content (impl, 0), gday_impl_ (impl)
        {
        }
#endif

        // gmonth_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline gmonth_pskel::
        gmonth_pskel ()
            : gmonth_impl_ (0)
        {
        }

        inline gmonth_pskel::
        gmonth_pskel (gmonth_pskel* impl, void*)
            : simple_content (impl, 0), gmonth_impl_ (impl)
        {
        }
#endif

        // gyear_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline gyear_pskel::
        gyear_pskel ()
            : gyear_impl_ (0)
        {
        }

        inline gyear_pskel::
        gyear_pskel (gyear_pskel* impl, void*)
            : simple_content (impl, 0), gyear_impl_ (impl)
        {
        }
#endif

        // gmonth_day_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline gmonth_day_pskel::
        gmonth_day_pskel ()
            : gmonth_day_impl_ (0)
        {
        }

        inline gmonth_day_pskel::
        gmonth_day_pskel (gmonth_day_pskel* impl, void*)
            : simple_content (impl, 0), gmonth_day_impl_ (impl)
        {
        }
#endif

        // gyear_month_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline gyear_month_pskel::
        gyear_month_pskel ()
            : gyear_month_impl_ (0)
        {
        }

        inline gyear_month_pskel::
        gyear_month_pskel (gyear_month_pskel* impl, void*)
            : simple_content (impl, 0), gyear_month_impl_ (impl)
        {
        }
#endif

        // date_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline date_pskel::
        date_pskel ()
            : date_impl_ (0)
        {
        }

        inline date_pskel::
        date_pskel (date_pskel* impl, void*)
            : simple_content (impl, 0), date_impl_ (impl)
        {
        }
#endif

        // time_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline time_pskel::
        time_pskel ()
            : time_impl_ (0)
        {
        }

        inline time_pskel::
        time_pskel (time_pskel* impl, void*)
            : simple_content (impl, 0), time_impl_ (impl)
        {
        }
#endif

        // date_time_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline date_time_pskel::
        date_time_pskel ()
            : date_time_impl_ (0)
        {
        }

        inline date_time_pskel::
        date_time_pskel (date_time_pskel* impl, void*)
            : simple_content (impl, 0), date_time_impl_ (impl)
        {
        }
#endif

        // duration_pskel
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline duration_pskel::
        duration_pskel ()
            : duration_impl_ (0)
        {
        }

        inline duration_pskel::
        duration_pskel (duration_pskel* impl, void*)
            : simple_content (impl, 0), duration_impl_ (impl)
        {
        }
#endif
      }
    }
  }
}
