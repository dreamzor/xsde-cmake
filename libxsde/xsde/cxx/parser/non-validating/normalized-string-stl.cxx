// file      : xsde/cxx/parser/non-validating/normalized-string-stl.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/parser/non-validating/normalized-string-stl.hxx>
#include <xsde/cxx/parser/non-validating/string-common.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace non_validating
      {
        void normalized_string_pimpl::
        _pre ()
        {
          str_.erase ();
        }

        void normalized_string_pimpl::
        _characters (const ro_string& s)
        {
          if (_facets ().whitespace_ == 2 && str_.size () == 0)
          {
            ro_string tmp (s.data (), s.size ());

            if (trim_left (tmp) != 0)
              str_ += tmp;
          }
          else
            str_ += s;
        }

        std::string normalized_string_pimpl::
        post_normalized_string ()
        {
          string_common::process_facets (str_, _facets ());

          std::string r;
          r.swap (str_);
          return r;
        }
      }
    }
  }
}
