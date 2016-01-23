// file      : xsde/cxx/serializer/validating/xml-schema-sskel.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

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
        inline byte_sskel::
        byte_sskel ()
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          byte_impl_ = 0;
#endif
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }

#ifdef XSDE_REUSE_STYLE_TIEIN
        inline byte_sskel::
        byte_sskel (byte_sskel* impl, void*)
            : simple_content (impl, 0), byte_impl_ (impl)
        {
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }
#endif
        inline void byte_sskel::
        _max_facet (signed char v, bool inc)
        {
          facets_.max_ = v;
          facets_.max_set_ = 1;
          facets_.max_inc_ = inc;
        }

        inline void byte_sskel::
        _min_facet (signed char v, bool inc)
        {
          facets_.min_ = v;
          facets_.min_set_ = 1;
          facets_.min_inc_ = inc;
        }

        inline const byte_sskel::facets& byte_sskel::
        _facets () const
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (parent_ != 0)
            return static_cast<const byte_sskel&> (*parent_).facets_;
          else
#endif
            return facets_;
        }

        // unsigned_byte_sskel
        //
        inline unsigned_byte_sskel::
        unsigned_byte_sskel ()
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          unsigned_byte_impl_ = 0;
#endif
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }

#ifdef XSDE_REUSE_STYLE_TIEIN
        inline unsigned_byte_sskel::
        unsigned_byte_sskel (unsigned_byte_sskel* impl, void*)
            : simple_content (impl, 0), unsigned_byte_impl_ (impl)
        {
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }
#endif

        inline void unsigned_byte_sskel::
        _max_facet (unsigned char v, bool inc)
        {
          facets_.max_ = v;
          facets_.max_set_ = 1;
          facets_.max_inc_ = inc;
        }

        inline void unsigned_byte_sskel::
        _min_facet (unsigned char v, bool inc)
        {
          facets_.min_ = v;
          facets_.min_set_ = 1;
          facets_.min_inc_ = inc;
        }

        inline const unsigned_byte_sskel::facets& unsigned_byte_sskel::
        _facets () const
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (parent_ != 0)
            return static_cast<const unsigned_byte_sskel&> (*parent_).facets_;
          else
#endif
            return facets_;
        }

        // short_sskel
        //
        inline short_sskel::
        short_sskel ()
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          short_impl_ = 0;
#endif
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }

#ifdef XSDE_REUSE_STYLE_TIEIN
        inline short_sskel::
        short_sskel (short_sskel* impl, void*)
            : simple_content (impl, 0), short_impl_ (impl)
        {
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }
#endif

        inline void short_sskel::
        _max_facet (short v, bool inc)
        {
          facets_.max_ = v;
          facets_.max_set_ = 1;
          facets_.max_inc_ = inc;
        }

        inline void short_sskel::
        _min_facet (short v, bool inc)
        {
          facets_.min_ = v;
          facets_.min_set_ = 1;
          facets_.min_inc_ = inc;
        }

        inline const short_sskel::facets& short_sskel::
        _facets () const
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (parent_ != 0)
            return static_cast<const short_sskel&> (*parent_).facets_;
          else
#endif
            return facets_;
        }

        // unsigned_short_sskel
        //
        inline unsigned_short_sskel::
        unsigned_short_sskel ()
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          unsigned_short_impl_ = 0;
#endif
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }

#ifdef XSDE_REUSE_STYLE_TIEIN
        inline unsigned_short_sskel::
        unsigned_short_sskel (unsigned_short_sskel* impl, void*)
            : simple_content (impl, 0), unsigned_short_impl_ (impl)
        {
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }
#endif

        inline void unsigned_short_sskel::
        _max_facet (unsigned short v, bool inc)
        {
          facets_.max_ = v;
          facets_.max_set_ = 1;
          facets_.max_inc_ = inc;
        }

        inline void unsigned_short_sskel::
        _min_facet (unsigned short v, bool inc)
        {
          facets_.min_ = v;
          facets_.min_set_ = 1;
          facets_.min_inc_ = inc;
        }

        inline const unsigned_short_sskel::facets& unsigned_short_sskel::
        _facets () const
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (parent_ != 0)
            return static_cast<const unsigned_short_sskel&> (*parent_).facets_;
          else
#endif
            return facets_;
        }

        // int_sskel
        //
        inline int_sskel::
        int_sskel ()
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          int_impl_ = 0;
#endif
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }

#ifdef XSDE_REUSE_STYLE_TIEIN
        inline int_sskel::
        int_sskel (int_sskel* impl, void*)
            : simple_content (impl, 0), int_impl_ (impl)
        {
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }
#endif
        inline void int_sskel::
        _max_facet (int v, bool inc)
        {
          facets_.max_ = v;
          facets_.max_set_ = 1;
          facets_.max_inc_ = inc;
        }

        inline void int_sskel::
        _min_facet (int v, bool inc)
        {
          facets_.min_ = v;
          facets_.min_set_ = 1;
          facets_.min_inc_ = inc;
        }

        inline const int_sskel::facets& int_sskel::
        _facets () const
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (parent_ != 0)
            return static_cast<const int_sskel&> (*parent_).facets_;
          else
#endif
            return facets_;
        }

        // unsigned_int_sskel
        //
        inline unsigned_int_sskel::
        unsigned_int_sskel ()
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          unsigned_int_impl_ = 0;
#endif
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }

#ifdef XSDE_REUSE_STYLE_TIEIN
        inline unsigned_int_sskel::
        unsigned_int_sskel (unsigned_int_sskel* impl, void*)
            : simple_content (impl, 0), unsigned_int_impl_ (impl)
        {
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }
#endif

        inline void unsigned_int_sskel::
        _max_facet (unsigned int v, bool inc)
        {
          facets_.max_ = v;
          facets_.max_set_ = 1;
          facets_.max_inc_ = inc;
        }

        inline void unsigned_int_sskel::
        _min_facet (unsigned int v, bool inc)
        {
          facets_.min_ = v;
          facets_.min_set_ = 1;
          facets_.min_inc_ = inc;
        }

        inline const unsigned_int_sskel::facets& unsigned_int_sskel::
        _facets () const
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (parent_ != 0)
            return static_cast<const unsigned_int_sskel&> (*parent_).facets_;
          else
#endif
            return facets_;
        }

        // long_sskel
        //
        inline long_sskel::
        long_sskel ()
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          long_impl_ = 0;
#endif
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }

#ifdef XSDE_REUSE_STYLE_TIEIN
        inline long_sskel::
        long_sskel (long_sskel* impl, void*)
            : simple_content (impl, 0), long_impl_ (impl)
        {
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }
#endif

        inline void long_sskel::
#ifdef XSDE_LONGLONG
        _max_facet (long long v, bool inc)
#else
        _max_facet (long v, bool inc)
#endif

        {
          facets_.max_ = v;
          facets_.max_set_ = 1;
          facets_.max_inc_ = inc;
        }

        inline void long_sskel::
#ifdef XSDE_LONGLONG
        _min_facet (long long v, bool inc)
#else
        _min_facet (long v, bool inc)
#endif
        {
          facets_.min_ = v;
          facets_.min_set_ = 1;
          facets_.min_inc_ = inc;
        }

        inline const long_sskel::facets& long_sskel::
        _facets () const
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (parent_ != 0)
            return static_cast<const long_sskel&> (*parent_).facets_;
          else
#endif
            return facets_;
        }

        // unsigned_long_sskel
        //
        inline unsigned_long_sskel::
        unsigned_long_sskel ()
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          unsigned_long_impl_ = 0;
#endif
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }

#ifdef XSDE_REUSE_STYLE_TIEIN
        inline unsigned_long_sskel::
        unsigned_long_sskel (unsigned_long_sskel* impl, void*)
            : simple_content (impl, 0), unsigned_long_impl_ (impl)
        {
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }
#endif

        inline void unsigned_long_sskel::
#ifdef XSDE_LONGLONG
        _max_facet (unsigned long long v, bool inc)
#else
        _max_facet (unsigned long v, bool inc)
#endif
        {
          facets_.max_ = v;
          facets_.max_set_ = 1;
          facets_.max_inc_ = inc;
        }

        inline void unsigned_long_sskel::
#ifdef XSDE_LONGLONG
        _min_facet (unsigned long long v, bool inc)
#else
        _min_facet (unsigned long v, bool inc)
#endif
        {
          facets_.min_ = v;
          facets_.min_set_ = 1;
          facets_.min_inc_ = inc;
        }

        inline const unsigned_long_sskel::facets& unsigned_long_sskel::
        _facets () const
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (parent_ != 0)
            return static_cast<const unsigned_long_sskel&> (*parent_).facets_;
          else
#endif
            return facets_;
        }

        // integer_sskel
        //
        inline integer_sskel::
        integer_sskel ()
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          integer_impl_ = 0;
#endif
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }

#ifdef XSDE_REUSE_STYLE_TIEIN
        inline integer_sskel::
        integer_sskel (integer_sskel* impl, void*)
            : simple_content (impl, 0), integer_impl_ (impl)
        {
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }
#endif
        inline void integer_sskel::
        _max_facet (long v, bool inc)
        {
          facets_.max_ = v;
          facets_.max_set_ = 1;
          facets_.max_inc_ = inc;
        }

        inline void integer_sskel::
        _min_facet (long v, bool inc)
        {
          facets_.min_ = v;
          facets_.min_set_ = 1;
          facets_.min_inc_ = inc;
        }

        inline const integer_sskel::facets& integer_sskel::
        _facets () const
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (parent_ != 0)
            return static_cast<const integer_sskel&> (*parent_).facets_;
          else
#endif
            return facets_;
        }

        // negative_integer_sskel
        //
        inline negative_integer_sskel::
        negative_integer_sskel ()
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          negative_integer_impl_ = 0;
#endif
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }

#ifdef XSDE_REUSE_STYLE_TIEIN
        inline negative_integer_sskel::
        negative_integer_sskel (negative_integer_sskel* impl, void*)
            : simple_content (impl, 0), negative_integer_impl_ (impl)
        {
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }
#endif
        inline void negative_integer_sskel::
        _max_facet (long v, bool inc)
        {
          facets_.max_ = v;
          facets_.max_set_ = 1;
          facets_.max_inc_ = inc;
        }

        inline void negative_integer_sskel::
        _min_facet (long v, bool inc)
        {
          facets_.min_ = v;
          facets_.min_set_ = 1;
          facets_.min_inc_ = inc;
        }

        inline const negative_integer_sskel::facets& negative_integer_sskel::
        _facets () const
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (parent_ != 0)
            return static_cast<const negative_integer_sskel&> (
              *parent_).facets_;
          else
#endif
            return facets_;
        }

        // non_positive_integer_sskel
        //
        inline non_positive_integer_sskel::
        non_positive_integer_sskel ()
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          non_positive_integer_impl_ = 0;
#endif
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }

#ifdef XSDE_REUSE_STYLE_TIEIN
        inline non_positive_integer_sskel::
        non_positive_integer_sskel (non_positive_integer_sskel* impl, void*)
            : simple_content (impl, 0), non_positive_integer_impl_ (impl)
        {
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }
#endif
                inline void non_positive_integer_sskel::
        _max_facet (long v, bool inc)
        {
          facets_.max_ = v;
          facets_.max_set_ = 1;
          facets_.max_inc_ = inc;
        }

        inline void non_positive_integer_sskel::
        _min_facet (long v, bool inc)
        {
          facets_.min_ = v;
          facets_.min_set_ = 1;
          facets_.min_inc_ = inc;
        }

        inline const non_positive_integer_sskel::facets&
        non_positive_integer_sskel::
        _facets () const
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (parent_ != 0)
            return static_cast<const non_positive_integer_sskel&> (
              *parent_).facets_;
          else
#endif
            return facets_;
        }

        // positive_integer_sskel
        //
        inline positive_integer_sskel::
        positive_integer_sskel ()
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          positive_integer_impl_ = 0;
#endif
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }

#ifdef XSDE_REUSE_STYLE_TIEIN
        inline positive_integer_sskel::
        positive_integer_sskel (positive_integer_sskel* impl, void*)
            : simple_content (impl, 0), positive_integer_impl_ (impl)
        {
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }
#endif
        inline void positive_integer_sskel::
        _max_facet (unsigned long v, bool inc)
        {
          facets_.max_ = v;
          facets_.max_set_ = 1;
          facets_.max_inc_ = inc;
        }

        inline void positive_integer_sskel::
        _min_facet (unsigned long v, bool inc)
        {
          facets_.min_ = v;
          facets_.min_set_ = 1;
          facets_.min_inc_ = inc;
        }

        inline const positive_integer_sskel::facets& positive_integer_sskel::
        _facets () const
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (parent_ != 0)
            return static_cast<const positive_integer_sskel&> (
              *parent_).facets_;
          else
#endif
            return facets_;
        }

        // non_negative_integer_sskel
        //
        inline non_negative_integer_sskel::
        non_negative_integer_sskel ()
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          non_negative_integer_impl_ = 0;
#endif
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }

#ifdef XSDE_REUSE_STYLE_TIEIN
        inline non_negative_integer_sskel::
        non_negative_integer_sskel (non_negative_integer_sskel* impl, void*)
            : simple_content (impl, 0), non_negative_integer_impl_ (impl)
        {
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }
#endif
        inline void non_negative_integer_sskel::
        _max_facet (unsigned long v, bool inc)
        {
          facets_.max_ = v;
          facets_.max_set_ = 1;
          facets_.max_inc_ = inc;
        }

        inline void non_negative_integer_sskel::
        _min_facet (unsigned long v, bool inc)
        {
          facets_.min_ = v;
          facets_.min_set_ = 1;
          facets_.min_inc_ = inc;
        }

        inline const non_negative_integer_sskel::facets&
        non_negative_integer_sskel::
        _facets () const
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (parent_ != 0)
            return static_cast<const non_negative_integer_sskel&> (
              *parent_).facets_;
          else
#endif
            return facets_;
        }

        // float_sskel
        //
        inline float_sskel::
        float_sskel ()
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          float_impl_ = 0;
#endif
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }

#ifdef XSDE_REUSE_STYLE_TIEIN
        inline float_sskel::
        float_sskel (float_sskel* impl, void*)
            : simple_content (impl, 0), float_impl_ (impl)
        {
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }
#endif
        inline void float_sskel::
        _max_facet (float v, bool inc)
        {
          facets_.max_ = v;
          facets_.max_set_ = 1;
          facets_.max_inc_ = inc;
        }

        inline void float_sskel::
        _min_facet (float v, bool inc)
        {
          facets_.min_ = v;
          facets_.min_set_ = 1;
          facets_.min_inc_ = inc;
        }

        inline const float_sskel::facets& float_sskel::
        _facets () const
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (parent_ != 0)
            return static_cast<const float_sskel&> (*parent_).facets_;
          else
#endif
            return facets_;
        }

        // double_sskel
        //
        inline double_sskel::
        double_sskel ()
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          double_impl_ = 0;
#endif
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }

#ifdef XSDE_REUSE_STYLE_TIEIN
        inline double_sskel::
        double_sskel (double_sskel* impl, void*)
            : simple_content (impl, 0), double_impl_ (impl)
        {
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }
#endif
        inline void double_sskel::
        _max_facet (double v, bool inc)
        {
          facets_.max_ = v;
          facets_.max_set_ = 1;
          facets_.max_inc_ = inc;
        }

        inline void double_sskel::
        _min_facet (double v, bool inc)
        {
          facets_.min_ = v;
          facets_.min_set_ = 1;
          facets_.min_inc_ = inc;
        }

        inline const double_sskel::facets& double_sskel::
        _facets () const
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (parent_ != 0)
            return static_cast<const double_sskel&> (*parent_).facets_;
          else
#endif
            return facets_;
        }

        // decimal_sskel
        //
        inline decimal_sskel::
        decimal_sskel ()
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          decimal_impl_ = 0;
#endif
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }

#ifdef XSDE_REUSE_STYLE_TIEIN
        inline decimal_sskel::
        decimal_sskel (decimal_sskel* impl, void*)
            : simple_content (impl, 0), decimal_impl_ (impl)
        {
          facets_.min_set_ = 0;
          facets_.max_set_ = 0;
        }
#endif
        inline void decimal_sskel::
        _max_facet (double v, bool inc)
        {
          facets_.max_ = v;
          facets_.max_set_ = 1;
          facets_.max_inc_ = inc;
        }

        inline void decimal_sskel::
        _min_facet (double v, bool inc)
        {
          facets_.min_ = v;
          facets_.min_set_ = 1;
          facets_.min_inc_ = inc;
        }

        inline const decimal_sskel::facets& decimal_sskel::
        _facets () const
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (parent_ != 0)
            return static_cast<const decimal_sskel&> (*parent_).facets_;
          else
#endif
            return facets_;
        }

        // string_facets
        //
        inline string_facets::
        string_facets ()
        {
          facets_.length_set_ = 0;
          facets_.min_length_set_ = 0;
          facets_.max_length_set_ = 0;

          facets_.enum_ = 0;
          facets_.enum_count_ = 0;

#ifdef XSDE_REGEXP
          facets_.pattern_set_ = 0;
#endif
        }

#ifdef XSDE_REGEXP
        inline string_facets::
        ~string_facets ()
        {
          if (facets_.pattern_set_ == 2)
            xmlRegFreeRegexp (facets_.pattern_.regexp);
        }
#endif

        inline void string_facets::
        _length_facet (size_t v)
        {
          facets_.length_ = v;
          facets_.length_set_ = 1;
        }

        inline void string_facets::
        _max_length_facet (size_t v)
        {
          facets_.max_length_ = v;
          facets_.max_length_set_ = 1;
        }

        inline void string_facets::
        _min_length_facet (size_t v)
        {
          facets_.min_length_ = v;
          facets_.min_length_set_ = 1;
        }

        inline void string_facets::
        _enumeration_facet (const char* const* e, size_t count)
        {
          facets_.enum_ = e;
          facets_.enum_count_ = count;
        }

#ifndef XSDE_REGEXP
        inline void string_facets::
        _pattern_facet (const char*)
        {
        }
#else
        inline void string_facets::
        _pattern_facet (const char* s)
        {
          facets_.pattern_.str = s;
          facets_.pattern_set_ = 1;
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

        inline const string_facets::facets& string_sskel::
        _facets () const
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (parent_ != 0)
            return static_cast<const string_sskel&> (*parent_).facets_;
          else
#endif
            return facets_;
        }

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
        inline const string_facets::facets& uri_sskel::
        _facets () const
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (parent_ != 0)
            return static_cast<const uri_sskel&> (*parent_).facets_;
          else
#endif
            return facets_;
        }

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
