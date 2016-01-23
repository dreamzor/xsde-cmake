// file      : xsde/cxx/serializer/validating/string-common.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/config.hxx>

#include <string.h> // strlen

#ifdef XSDE_REGEXP
#ifdef XSDE_EXCEPTIONS
#  include <new> // std::bad_alloc
#endif
#endif

#include <xsde/cxx/string-search.hxx>
#include <xsde/cxx/serializer/validating/string-common.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
        bool string_common::
        validate_facets (const char* s,
                         const string_facets::facets& f,
                         context& ctx)
        {
          if (f.length_set_ ||
              f.min_length_set_ ||
              f.max_length_set_ ||
              f.enum_count_ != 0
#ifdef XSDE_REGEXP
              || f.pattern_set_ != 0
#endif
          )
          {
            return validate_facets (s, strlen (s), f, ctx);
          }

          return true;
        }

        bool string_common::
        validate_facets (const char* s,
                         size_t n,
                         const string_facets::facets& f,
                         context& ctx)
        {
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
            if (search (f.enum_, f.enum_count_, s) == f.enum_count_)
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
