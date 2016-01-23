// file      : xsde/cxx/parser/validating/xml-schema-pskel.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_VALIDATING_XML_SCHEMA_PSKEL_HXX
#define XSDE_CXX_PARSER_VALIDATING_XML_SCHEMA_PSKEL_HXX

#include <xsde/cxx/config.hxx>

#ifdef XSDE_STL
#  include <string>
#endif

#ifdef XSDE_REGEXP
#  include <xsde/c/regexp/xmlregexp.h>
#endif

#include <xsde/cxx/parser/xml-schema.hxx>

#include <xsde/cxx/parser/validating/parser.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
      {
        // anyType and anySimpleType. All events are routed to the
        // _any_* callbacks.
        //
        struct any_type_pskel: complex_content
        {
#ifdef XSDE_POLYMORPHIC
          virtual bool
          _start_element_impl (const ro_string&,
                               const ro_string&,
                               const char*);
#else
          virtual bool
          _start_element_impl (const ro_string&, const ro_string&);
#endif

          virtual bool
          _end_element_impl (const ro_string&, const ro_string&);

          virtual bool
          _attribute_impl_phase_two (const ro_string&,
                                     const ro_string&,
                                     const ro_string&);

          virtual bool
          _characters_impl (const ro_string&);

          virtual void
          post_any_type ();

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif

#ifdef XSDE_REUSE_STYLE_TIEIN
          any_type_pskel ();
          any_type_pskel (any_type_pskel* impl, void*);

        protected:
          any_type_pskel* any_type_impl_;
#endif
        };

        struct any_simple_type_pskel: simple_content
        {
#ifdef XSDE_STL
          virtual std::string
#else
          virtual char*
#endif
          post_any_simple_type () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif

#ifdef XSDE_REUSE_STYLE_TIEIN
          any_simple_type_pskel ();
          any_simple_type_pskel (any_simple_type_pskel* impl, void*);

        protected:
          any_simple_type_pskel* any_simple_type_impl_;
#endif
        };

        // Boolean.
        //
        struct boolean_pskel: simple_content
        {
          virtual bool
          post_boolean () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif

#ifdef XSDE_REUSE_STYLE_TIEIN
          boolean_pskel ();
          boolean_pskel (boolean_pskel* impl, void*);

        protected:
          boolean_pskel* boolean_impl_;
#endif
        };


        // 8-bit
        //

        struct byte_pskel: simple_content
        {
          virtual signed char
          post_byte () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif
          byte_pskel ();

#ifdef XSDE_REUSE_STYLE_TIEIN
          byte_pskel (byte_pskel* impl, void*);

        protected:
          byte_pskel* byte_impl_;
#endif
          // Facets.
          //
        public:
          void
          _max_facet (signed char, bool inclusive);

          void
          _min_facet (signed char, bool inclusive);

        protected:
          struct facets
          {
            signed char min_;
            signed char max_;

            unsigned int min_set_ : 1;
            unsigned int min_inc_ : 1;
            unsigned int max_set_ : 1;
            unsigned int max_inc_ : 1;
          };

          const facets&
          _facets () const;

        private:
          facets facets_;
        };

        struct unsigned_byte_pskel: simple_content
        {
          virtual unsigned char
          post_unsigned_byte () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif

          unsigned_byte_pskel ();

#ifdef XSDE_REUSE_STYLE_TIEIN
          unsigned_byte_pskel (unsigned_byte_pskel* impl, void*);

        protected:
          unsigned_byte_pskel* unsigned_byte_impl_;
#endif
          // Facets.
          //
        public:
          void
          _max_facet (unsigned char, bool inclusive);

          void
          _min_facet (unsigned char, bool inclusive);

        protected:
          struct facets
          {
            unsigned char min_;
            unsigned char max_;

            unsigned int min_set_ : 1;
            unsigned int min_inc_ : 1;
            unsigned int max_set_ : 1;
            unsigned int max_inc_ : 1;
          };

          const facets&
          _facets () const;

        private:
          facets facets_;
        };


        // 16-bit
        //

        struct short_pskel: simple_content
        {
          virtual short
          post_short () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif

          short_pskel ();

#ifdef XSDE_REUSE_STYLE_TIEIN
          short_pskel (short_pskel* impl, void*);

        protected:
          short_pskel* short_impl_;
#endif
          // Facets.
          //
        public:
          void
          _max_facet (short, bool inclusive);

          void
          _min_facet (short, bool inclusive);

        protected:
          struct facets
          {
            short min_;
            short max_;

            unsigned int min_set_ : 1;
            unsigned int min_inc_ : 1;
            unsigned int max_set_ : 1;
            unsigned int max_inc_ : 1;
          };

          const facets&
          _facets () const;

        private:
          facets facets_;
        };

        struct unsigned_short_pskel: simple_content
        {
          virtual unsigned short
          post_unsigned_short () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif

          unsigned_short_pskel ();

#ifdef XSDE_REUSE_STYLE_TIEIN
          unsigned_short_pskel (unsigned_short_pskel* impl, void*);

        protected:
          unsigned_short_pskel* unsigned_short_impl_;
#endif
          // Facets.
          //
        public:
          void
          _max_facet (unsigned short, bool inclusive);

          void
          _min_facet (unsigned short, bool inclusive);

        protected:
          struct facets
          {
            unsigned short min_;
            unsigned short max_;

            unsigned int min_set_ : 1;
            unsigned int min_inc_ : 1;
            unsigned int max_set_ : 1;
            unsigned int max_inc_ : 1;
          };

          const facets&
          _facets () const;

        private:
          facets facets_;
        };


        // 32-bit
        //

        struct int_pskel: simple_content
        {
          virtual int
          post_int () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif
          int_pskel ();

#ifdef XSDE_REUSE_STYLE_TIEIN
          int_pskel (int_pskel* impl, void*);

        protected:
          int_pskel* int_impl_;
#endif
          // Facets.
          //
        public:
          void
          _max_facet (int, bool inclusive);

          void
          _min_facet (int, bool inclusive);

        protected:
          struct facets
          {
            int min_;
            int max_;

            unsigned int min_set_ : 1;
            unsigned int min_inc_ : 1;
            unsigned int max_set_ : 1;
            unsigned int max_inc_ : 1;
          };

          const facets&
          _facets () const;

        private:
          facets facets_;
        };

        struct unsigned_int_pskel: simple_content
        {
          virtual unsigned int
          post_unsigned_int () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif

          unsigned_int_pskel ();

#ifdef XSDE_REUSE_STYLE_TIEIN
          unsigned_int_pskel (unsigned_int_pskel* impl, void*);

        protected:
          unsigned_int_pskel* unsigned_int_impl_;
#endif
          // Facets.
          //
        public:
          void
          _max_facet (unsigned int, bool inclusive);

          void
          _min_facet (unsigned int, bool inclusive);

        protected:
          struct facets
          {
            unsigned int min_;
            unsigned int max_;

            unsigned int min_set_ : 1;
            unsigned int min_inc_ : 1;
            unsigned int max_set_ : 1;
            unsigned int max_inc_ : 1;
          };

          const facets&
          _facets () const;

        private:
          facets facets_;
        };


        // 64-bit
        //
#ifdef XSDE_LONGLONG

        struct long_pskel: simple_content
        {
          virtual long long
          post_long () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif
          long_pskel ();

#ifdef XSDE_REUSE_STYLE_TIEIN
          long_pskel (long_pskel* impl, void*);

        protected:
          long_pskel* long_impl_;
#endif
          // Facets.
          //
        public:
          void
          _max_facet (long long, bool inclusive);

          void
          _min_facet (long long, bool inclusive);

        protected:
          struct facets
          {
            long long min_;
            long long max_;

            unsigned int min_set_ : 1;
            unsigned int min_inc_ : 1;
            unsigned int max_set_ : 1;
            unsigned int max_inc_ : 1;
          };

          const facets&
          _facets () const;

        private:
          facets facets_;
        };

        struct unsigned_long_pskel: simple_content
        {
          virtual unsigned long long
          post_unsigned_long () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif
          unsigned_long_pskel ();

#ifdef XSDE_REUSE_STYLE_TIEIN
          unsigned_long_pskel (unsigned_long_pskel* impl, void*);

        protected:
          unsigned_long_pskel* unsigned_long_impl_;
#endif
          // Facets.
          //
        public:
          void
          _max_facet (unsigned long long, bool inclusive);

          void
          _min_facet (unsigned long long, bool inclusive);

        protected:
          struct facets
          {
            unsigned long long min_;
            unsigned long long max_;

            unsigned int min_set_ : 1;
            unsigned int min_inc_ : 1;
            unsigned int max_set_ : 1;
            unsigned int max_inc_ : 1;
          };

          const facets&
          _facets () const;

        private:
          facets facets_;
        };

#else

        struct long_pskel: simple_content
        {
          virtual long
          post_long () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif
          long_pskel ();

#ifdef XSDE_REUSE_STYLE_TIEIN
          long_pskel (long_pskel* impl, void*);

        protected:
          long_pskel* long_impl_;
#endif
          // Facets.
          //
        public:
          void
          _max_facet (long, bool inclusive);

          void
          _min_facet (long, bool inclusive);

        protected:
          struct facets
          {
            long min_;
            long max_;

            unsigned int min_set_ : 1;
            unsigned int min_inc_ : 1;
            unsigned int max_set_ : 1;
            unsigned int max_inc_ : 1;
          };

          const facets&
          _facets () const;

        private:
          facets facets_;
        };

        struct unsigned_long_pskel: simple_content
        {
          virtual unsigned long
          post_unsigned_long () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif
          unsigned_long_pskel ();

#ifdef XSDE_REUSE_STYLE_TIEIN
          unsigned_long_pskel (unsigned_long_pskel* impl, void*);

        protected:
          unsigned_long_pskel* unsigned_long_impl_;
#endif
          // Facets.
          //
        public:
          void
          _max_facet (unsigned long, bool inclusive);

          void
          _min_facet (unsigned long, bool inclusive);

        protected:
          struct facets
          {
            unsigned long min_;
            unsigned long max_;

            unsigned int min_set_ : 1;
            unsigned int min_inc_ : 1;
            unsigned int max_set_ : 1;
            unsigned int max_inc_ : 1;
          };

          const facets&
          _facets () const;

        private:
          facets facets_;
        };
#endif


        // Arbitrary-length integers.
        //

        struct integer_pskel: simple_content
        {
          virtual long
          post_integer () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif
          integer_pskel ();

#ifdef XSDE_REUSE_STYLE_TIEIN
          integer_pskel (integer_pskel* impl, void*);

        protected:
          integer_pskel* integer_impl_;
#endif
          // Facets.
          //
        public:
          void
          _max_facet (long, bool inclusive);

          void
          _min_facet (long, bool inclusive);

        protected:
          struct facets
          {
            long min_;
            long max_;

            unsigned int min_set_ : 1;
            unsigned int min_inc_ : 1;
            unsigned int max_set_ : 1;
            unsigned int max_inc_ : 1;
          };

          const facets&
          _facets () const;

        private:
          facets facets_;
        };

        struct negative_integer_pskel: simple_content
        {
          virtual long
          post_negative_integer () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif
          negative_integer_pskel ();

#ifdef XSDE_REUSE_STYLE_TIEIN
          negative_integer_pskel (negative_integer_pskel* impl, void*);

        protected:
          negative_integer_pskel* negative_integer_impl_;
#endif
          // Facets.
          //
        public:
          void
          _max_facet (long, bool inclusive);

          void
          _min_facet (long, bool inclusive);

        protected:
          struct facets
          {
            long min_;
            long max_;

            unsigned int min_set_ : 1;
            unsigned int min_inc_ : 1;
            unsigned int max_set_ : 1;
            unsigned int max_inc_ : 1;
          };

          const facets&
          _facets () const;

        private:
          facets facets_;
        };

        struct non_positive_integer_pskel: simple_content
        {
          virtual long
          post_non_positive_integer () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif
          non_positive_integer_pskel ();

#ifdef XSDE_REUSE_STYLE_TIEIN
          non_positive_integer_pskel (non_positive_integer_pskel* impl, void*);

        protected:
          non_positive_integer_pskel* non_positive_integer_impl_;
#endif
          // Facets.
          //
        public:
          void
          _max_facet (long, bool inclusive);

          void
          _min_facet (long, bool inclusive);

        protected:
          struct facets
          {
            long min_;
            long max_;

            unsigned int min_set_ : 1;
            unsigned int min_inc_ : 1;
            unsigned int max_set_ : 1;
            unsigned int max_inc_ : 1;
          };

          const facets&
          _facets () const;

        private:
          facets facets_;
        };

        struct positive_integer_pskel: simple_content
        {
          virtual unsigned long
          post_positive_integer () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif
          positive_integer_pskel ();

#ifdef XSDE_REUSE_STYLE_TIEIN
          positive_integer_pskel (positive_integer_pskel* impl, void*);

        protected:
          positive_integer_pskel* positive_integer_impl_;
#endif
          // Facets.
          //
        public:
          void
          _max_facet (unsigned long, bool inclusive);

          void
          _min_facet (unsigned long, bool inclusive);

        protected:
          struct facets
          {
            unsigned long min_;
            unsigned long max_;

            unsigned int min_set_ : 1;
            unsigned int min_inc_ : 1;
            unsigned int max_set_ : 1;
            unsigned int max_inc_ : 1;
          };

          const facets&
          _facets () const;

        private:
          facets facets_;
        };

        struct non_negative_integer_pskel: simple_content
        {
          virtual unsigned long
          post_non_negative_integer () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif
          non_negative_integer_pskel ();

#ifdef XSDE_REUSE_STYLE_TIEIN
          non_negative_integer_pskel (non_negative_integer_pskel* impl, void*);

        protected:
          non_negative_integer_pskel* non_negative_integer_impl_;
#endif
          // Facets.
          //
        public:
          void
          _max_facet (unsigned long, bool inclusive);

          void
          _min_facet (unsigned long, bool inclusive);

        protected:
          struct facets
          {
            unsigned long min_;
            unsigned long max_;

            unsigned int min_set_ : 1;
            unsigned int min_inc_ : 1;
            unsigned int max_set_ : 1;
            unsigned int max_inc_ : 1;
          };

          const facets&
          _facets () const;

        private:
          facets facets_;
        };


        // Floats.
        //

        struct float_pskel: simple_content
        {
          virtual float
          post_float () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif
          float_pskel ();

#ifdef XSDE_REUSE_STYLE_TIEIN
          float_pskel (float_pskel* impl, void*);

        protected:
          float_pskel* float_impl_;
#endif
          // Facets.
          //
        public:
          void
          _max_facet (float, bool inclusive);

          void
          _min_facet (float, bool inclusive);

        protected:
          struct facets
          {
            float min_;
            float max_;

            unsigned int min_set_ : 1;
            unsigned int min_inc_ : 1;
            unsigned int max_set_ : 1;
            unsigned int max_inc_ : 1;
          };

          const facets&
          _facets () const;

        private:
          facets facets_;
        };

        struct double_pskel: simple_content
        {
          virtual double
          post_double () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif
          double_pskel ();

#ifdef XSDE_REUSE_STYLE_TIEIN
          double_pskel (double_pskel* impl, void*);

        protected:
          double_pskel* double_impl_;
#endif
          // Facets.
          //
        public:
          void
          _max_facet (double, bool inclusive);

          void
          _min_facet (double, bool inclusive);

        protected:
          struct facets
          {
            double min_;
            double max_;

            unsigned int min_set_ : 1;
            unsigned int min_inc_ : 1;
            unsigned int max_set_ : 1;
            unsigned int max_inc_ : 1;
          };

          const facets&
          _facets () const;

        private:
          facets facets_;
        };

        struct decimal_pskel: simple_content
        {
          virtual double
          post_decimal () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif
          decimal_pskel ();

#ifdef XSDE_REUSE_STYLE_TIEIN
          decimal_pskel (decimal_pskel* impl, void*);

        protected:
          decimal_pskel* decimal_impl_;
#endif
          // Facets.
          //
        public:
          void
          _max_facet (double, bool inclusive);

          void
          _min_facet (double, bool inclusive);

        protected:
          struct facets
          {
            double min_;
            double max_;

            unsigned int min_set_ : 1;
            unsigned int min_inc_ : 1;
            unsigned int max_set_ : 1;
            unsigned int max_inc_ : 1;
          };

          const facets&
          _facets () const;

        private:
          facets facets_;
        };


        //
        // String-based types. If STL is disabled you are getting a C
        // string that you have to delete with delete[] (or custom
        // deallocator if enabled).
        //

        struct string_facets
        {
          string_facets ();
#ifdef XSDE_REGEXP
          ~string_facets ();
#endif

          void
          _length_facet (size_t);

          void
          _max_length_facet (size_t);

          void
          _min_length_facet (size_t);

          void
          _whitespace_facet (unsigned int);

          void
          _enumeration_facet (const char* const*, size_t count);

          void
          _pattern_facet (const char*);

        public:
          struct facets
          {
            size_t length_;
            size_t min_length_;
            size_t max_length_;

            const char* const* enum_;
            size_t enum_count_;

#ifdef XSDE_REGEXP
            union
            {
              const char* str;
              xmlRegexpPtr regexp;
            } pattern_;
#endif
            unsigned int length_set_ : 1;
            unsigned int min_length_set_ : 1;
            unsigned int max_length_set_ : 1;

#ifdef XSDE_REGEXP
            // 0 - not set
            // 1 - string
            // 2 - compiled
            //
            unsigned int pattern_set_: 2;
#endif
            // 0 - preserve
            // 1 - replace
            // 2 - collapse
            //
            unsigned int whitespace_: 2;
          };

        protected:
          facets facets_;
        };

        struct string_pskel: simple_content, string_facets
        {
#ifdef XSDE_STL
          virtual std::string
#else
          virtual char*
#endif
          post_string () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif

#ifdef XSDE_REUSE_STYLE_TIEIN
          string_pskel ();
          string_pskel (string_pskel* impl, void*);

        protected:
          string_pskel* string_impl_;
#endif
        protected:
          const string_facets::facets&
          _facets () const;
        };

        struct normalized_string_pskel: simple_content, string_facets
        {
#ifdef XSDE_STL
          virtual std::string
#else
          virtual char*
#endif
          post_normalized_string () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif
          normalized_string_pskel ();

#ifdef XSDE_REUSE_STYLE_TIEIN
          normalized_string_pskel (normalized_string_pskel* impl, void*);

        protected:
          normalized_string_pskel* normalized_string_impl_;
#endif
        protected:
          const string_facets::facets&
          _facets () const;
        };

        struct token_pskel: simple_content, string_facets
        {
#ifdef XSDE_STL
          virtual std::string
#else
          virtual char*
#endif
          post_token () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif
          token_pskel ();

#ifdef XSDE_REUSE_STYLE_TIEIN
          token_pskel (token_pskel* impl, void*);

        protected:
          token_pskel* token_impl_;
#endif
        protected:
          const string_facets::facets&
          _facets () const;
        };

        struct name_pskel: simple_content, string_facets
        {
#ifdef XSDE_STL
          virtual std::string
#else
          virtual char*
#endif
          post_name () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif
          name_pskel ();

#ifdef XSDE_REUSE_STYLE_TIEIN
          name_pskel (name_pskel* impl, void*);

        protected:
          name_pskel* name_impl_;
#endif
        protected:
          const string_facets::facets&
          _facets () const;
        };

        struct nmtoken_pskel: simple_content, string_facets
        {
#ifdef XSDE_STL
          virtual std::string
#else
          virtual char*
#endif
          post_nmtoken () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif
          nmtoken_pskel ();

#ifdef XSDE_REUSE_STYLE_TIEIN
          nmtoken_pskel (nmtoken_pskel* impl, void*);

        protected:
          nmtoken_pskel* nmtoken_impl_;
#endif
        protected:
          const string_facets::facets&
          _facets () const;
        };

        struct nmtokens_pskel: list_base
        {
          virtual string_sequence*
          post_nmtokens () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif

#ifdef XSDE_REUSE_STYLE_TIEIN
          nmtokens_pskel ();
          nmtokens_pskel (nmtokens_pskel* impl, void*);

        protected:
          nmtokens_pskel* nmtokens_impl_;
#endif
        };

        struct ncname_pskel: simple_content, string_facets
        {
#ifdef XSDE_STL
          virtual std::string
#else
          virtual char*
#endif
          post_ncname () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif
          ncname_pskel ();

#ifdef XSDE_REUSE_STYLE_TIEIN
          ncname_pskel (ncname_pskel* impl, void*);

        protected:
          ncname_pskel* ncname_impl_;
#endif
        protected:
          const string_facets::facets&
          _facets () const;
        };

        struct id_pskel: simple_content, string_facets
        {
#ifdef XSDE_STL
          virtual std::string
#else
          virtual char*
#endif
          post_id () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif
          id_pskel ();

#ifdef XSDE_REUSE_STYLE_TIEIN
          id_pskel (id_pskel* impl, void*);

        protected:
          id_pskel* id_impl_;
#endif
        protected:
          const string_facets::facets&
          _facets () const;
        };

        struct idref_pskel: simple_content, string_facets
        {
#ifdef XSDE_STL
          virtual std::string
#else
          virtual char*
#endif
          post_idref () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif
          idref_pskel ();

#ifdef XSDE_REUSE_STYLE_TIEIN
          idref_pskel (idref_pskel* impl, void*);

        protected:
          idref_pskel* idref_impl_;
#endif
        protected:
          const string_facets::facets&
          _facets () const;
        };

        struct idrefs_pskel: list_base
        {
          virtual string_sequence*
          post_idrefs () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif

#ifdef XSDE_REUSE_STYLE_TIEIN
          idrefs_pskel ();
          idrefs_pskel (idrefs_pskel* impl, void*);

        protected:
          idrefs_pskel* idrefs_impl_;
#endif
        };

        struct language_pskel: simple_content, string_facets
        {
#ifdef XSDE_STL
          virtual std::string
#else
          virtual char*
#endif
          post_language () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif
          language_pskel ();

#ifdef XSDE_REUSE_STYLE_TIEIN
          language_pskel (language_pskel* impl, void*);

        protected:
          language_pskel* language_impl_;
#endif
        protected:
          const string_facets::facets&
          _facets () const;
        };

        struct uri_pskel: simple_content, string_facets
        {
#ifdef XSDE_STL
          virtual std::string
#else
          virtual char*
#endif
          post_uri () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif
          uri_pskel ();

#ifdef XSDE_REUSE_STYLE_TIEIN
          uri_pskel (uri_pskel* impl, void*);

        protected:
          uri_pskel* uri_impl_;
#endif
        protected:
          const string_facets::facets&
          _facets () const;
        };

        struct qname_pskel: simple_content
        {
#ifdef XSDE_STL
          virtual qname
#else
          virtual qname*
#endif
          post_qname () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif

#ifdef XSDE_REUSE_STYLE_TIEIN
          qname_pskel ();
          qname_pskel (qname_pskel* impl, void*);

        protected:
          qname_pskel* qname_impl_;
#endif
        };

        // base64Binary
        //
        struct base64_binary_pskel: simple_content
        {
          virtual buffer*
          post_base64_binary () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif

#ifdef XSDE_REUSE_STYLE_TIEIN
          base64_binary_pskel ();
          base64_binary_pskel (base64_binary_pskel* impl, void*);

        protected:
          base64_binary_pskel* base64_binary_impl_;
#endif
        };

        // hexBinary
        //
        struct hex_binary_pskel: simple_content
        {
          virtual buffer*
          post_hex_binary () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif

#ifdef XSDE_REUSE_STYLE_TIEIN
          hex_binary_pskel ();
          hex_binary_pskel (hex_binary_pskel* impl, void*);

        protected:
          hex_binary_pskel* hex_binary_impl_;
#endif
        };

        // Time and date types.
        //
        struct gday_pskel: simple_content
        {
          virtual gday
          post_gday () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif

#ifdef XSDE_REUSE_STYLE_TIEIN
          gday_pskel ();
          gday_pskel (gday_pskel* impl, void*);

        protected:
          gday_pskel* gday_impl_;
#endif
        };

        struct gmonth_pskel: simple_content
        {
          virtual gmonth
          post_gmonth () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif

#ifdef XSDE_REUSE_STYLE_TIEIN
          gmonth_pskel ();
          gmonth_pskel (gmonth_pskel* impl, void*);

        protected:
          gmonth_pskel* gmonth_impl_;
#endif
        };

        struct gyear_pskel: simple_content
        {
          virtual gyear
          post_gyear () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif

#ifdef XSDE_REUSE_STYLE_TIEIN
          gyear_pskel ();
          gyear_pskel (gyear_pskel* impl, void*);

        protected:
          gyear_pskel* gyear_impl_;
#endif
        };

        struct gmonth_day_pskel: simple_content
        {
          virtual gmonth_day
          post_gmonth_day () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif

#ifdef XSDE_REUSE_STYLE_TIEIN
          gmonth_day_pskel ();
          gmonth_day_pskel (gmonth_day_pskel* impl, void*);

        protected:
          gmonth_day_pskel* gmonth_day_impl_;
#endif
        };

        struct gyear_month_pskel: simple_content
        {
          virtual gyear_month
          post_gyear_month () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif

#ifdef XSDE_REUSE_STYLE_TIEIN
          gyear_month_pskel ();
          gyear_month_pskel (gyear_month_pskel* impl, void*);

        protected:
          gyear_month_pskel* gyear_month_impl_;
#endif
        };

        struct date_pskel: simple_content
        {
          virtual date
          post_date () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif

#ifdef XSDE_REUSE_STYLE_TIEIN
          date_pskel ();
          date_pskel (date_pskel* impl, void*);

        protected:
          date_pskel* date_impl_;
#endif
        };

        struct time_pskel: simple_content
        {
          virtual time
          post_time () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif

#ifdef XSDE_REUSE_STYLE_TIEIN
          time_pskel ();
          time_pskel (time_pskel* impl, void*);

        protected:
          time_pskel* time_impl_;
#endif
        };

        struct date_time_pskel: simple_content
        {
          virtual date_time
          post_date_time () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif

#ifdef XSDE_REUSE_STYLE_TIEIN
          date_time_pskel ();
          date_time_pskel (date_time_pskel* impl, void*);

        protected:
          date_time_pskel* date_time_impl_;
#endif
        };

        struct duration_pskel: simple_content
        {
          virtual duration
          post_duration () = 0;

#ifdef XSDE_POLYMORPHIC
          static const char*
          _static_type ();

          virtual const char*
          _dynamic_type () const;
#endif

#ifdef XSDE_REUSE_STYLE_TIEIN
          duration_pskel ();
          duration_pskel (duration_pskel* impl, void*);

        protected:
          duration_pskel* duration_impl_;
#endif
        };
      }
    }
  }
}

#include <xsde/cxx/parser/validating/xml-schema-pskel.ixx>

#endif  // XSDE_CXX_PARSER_VALIDATING_XML_SCHEMA_PSKEL_HXX
