// file      : xsde/cxx/parser/validating/token-stl.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/parser/validating/token-stl.hxx>
#include <xsde/cxx/parser/validating/string-common.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
      {
        void token_pimpl::
        _pre ()
        {
          str_.erase ();
        }

        void token_pimpl::
        _characters (const ro_string& s)
        {
          if (str_.size () == 0)
          {
            ro_string tmp (s.data (), s.size ());

            if (trim_left (tmp) != 0)
              str_ += tmp;
          }
          else
            str_ += s;
        }

        void token_pimpl::
        _post ()
        {
          string_common::validate_facets (str_, _facets (), _context ());
        }

        std::string token_pimpl::
        post_token ()
        {
          std::string r;
          r.swap (str_);
          return r;
        }
      }
    }
  }
}
