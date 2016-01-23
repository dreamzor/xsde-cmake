// file      : xsde/cxx/parser/non-validating/string-common.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/parser/non-validating/string-common.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace non_validating
      {
        void string_common::
        process_facets (
#ifdef XSDE_STL
          std::string& str,
#else
          string& str,
#endif
          const string_facets::facets& f)
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
        }
      }
    }
  }
}
