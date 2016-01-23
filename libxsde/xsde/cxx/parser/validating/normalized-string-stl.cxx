// file      : xsde/cxx/parser/validating/normalized-string-stl.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/parser/validating/normalized-string-stl.hxx>
#include <xsde/cxx/parser/validating/string-common.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
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

        void normalized_string_pimpl::
        _post ()
        {
          string_common::validate_facets (str_, _facets (), _context ());
        }

        std::string normalized_string_pimpl::
        post_normalized_string ()
        {
          std::string r;
          r.swap (str_);
          return r;
        }
      }
    }
  }
}
