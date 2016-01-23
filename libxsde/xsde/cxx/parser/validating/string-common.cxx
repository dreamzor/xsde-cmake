// file      : xsde/cxx/parser/validating/string-common.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/config.hxx>

#ifdef XSDE_REGEXP
#ifdef XSDE_EXCEPTIONS
#  include <new> // std::bad_alloc
#endif
#endif

#include <xsde/cxx/string-search.hxx>
#include <xsde/cxx/parser/validating/string-common.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
      {
        bool string_common::
        validate_facets (
#ifdef XSDE_STL
          std::string& str,
#else
          string& str,
#endif
          const string_facets::facets& f,
          context& ctx)
        {
#ifdef XSDE_STL
          typedef std::string::size_type size_type;
#else
          typedef string::size_type size_type;
#endif

          if (f.whitespace_ == 2)
          {
            // Collapse. The left trimming has already been performed.
            //
            size_type size = str.size ();
            size_type j = 0;

            bool subs = false;

            for (size_type i = 0; i < size; ++i)
            {
              char c = str[i];

              if (c == 0x20 || c == 0x0A || c == 0x0D || c == 0x09)
              {
                subs = true;
              }
              else
              {
                if (subs)
                {
                  subs = false;
                  str[j++] = 0x20;
                }

                str[j++] = c;
              }
            }

#ifdef XSDE_STL
            str.resize (j);
#else
            str.truncate (j);
#endif
          }
          else if (f.whitespace_ == 1)
          {
            // Replace.
            //
            size_type size = str.size ();

            for (size_type i = 0; i < size; ++i)
            {
              char& c = str[i];

              if (c == 0x0A || c == 0x0D || c == 0x09)
                c = 0x20;
            }
          }

#ifdef XSDE_STL
          const char* s = str.c_str ();
#else
          const char* s = str.data ();
#endif
          size_t n = str.size ();

          if (f.length_set_ && n != f.length_)
          {
            ctx.schema_error (schema_error::length_not_equal_prescribed);
            return false;
          }

          if (f.min_length_set_ && n < f.min_length_)
          {
            ctx.schema_error (schema_error::length_less_than_min);
            return false;
          }

          if (f.max_length_set_ && n > f.max_length_)
          {
            ctx.schema_error (schema_error::length_greater_than_max);
            return false;
          }

          if (f.enum_count_ != 0)
          {
            size_t i = search (f.enum_, f.enum_count_, s);

            if (i == f.enum_count_)
            {
              ctx.schema_error (schema_error::value_not_in_enumeration);
              return false;
            }
          }

#ifdef XSDE_REGEXP
          if (f.pattern_set_ != 0)
          {
            if (f.pattern_set_ == 1)
            {
              xmlRegexpPtr r = xmlRegexpCompile (
                reinterpret_cast<const xmlChar*> (f.pattern_.str));

              if (r == 0)
              {
#ifdef XSDE_EXCEPTIONS
                throw std::bad_alloc ();
#else
                ctx.sys_error (sys_error::no_memory);
                return false;
#endif

              }

              string_facets::facets& t =
                const_cast<string_facets::facets&> (f);

              t.pattern_.regexp = r;
              t.pattern_set_ = 2;
            }

            if (xmlRegexpExec (
                  f.pattern_.regexp,
                  reinterpret_cast<const xmlChar*> (s)) != 1)
            {
              ctx.schema_error (schema_error::value_pattern_mismatch);
              return false;
            }
          }
#endif
          return true;
        }
      }
    }
  }
}
