// file      : xsde/cxx/parser/validating/uri-stl.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/parser/validating/uri-stl.hxx>
#include <xsde/cxx/parser/validating/string-common.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
      {
        void uri_pimpl::
        _pre ()
        {
          str_.erase ();
        }

        void uri_pimpl::
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

        void uri_pimpl::
        _post ()
        {
          // According to Datatypes 3.2.17 and RFC2396 pretty much anything
          // can be a URI and conforming processors do not need to figure
          // out and verify particular URI schemes.
          //
          string_common::validate_facets (str_, _facets (), _context ());
        }

        std::string uri_pimpl::
        post_uri ()
        {
          std::string r;
          r.swap (str_);
          return r;
        }
      }
    }
  }
}
