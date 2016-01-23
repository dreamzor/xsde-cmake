// file      : xsde/cxx/parser/validating/idref-stl.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/xml/ncname.hxx>

#include <xsde/cxx/parser/validating/idref-stl.hxx>
#include <xsde/cxx/parser/validating/string-common.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
      {
        void idref_pimpl::
        _pre ()
        {
          str_.erase ();
        }

        void idref_pimpl::
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

        void idref_pimpl::
        _post ()
        {
          if (!string_common::validate_facets (str_, _facets (), _context ()))
            return;

          if (!xml::valid_ncname (str_.c_str (), str_.size ()))
            _schema_error (schema_error::invalid_idref_value);
        }

        std::string idref_pimpl::
        post_idref ()
        {
          std::string r;
          r.swap (str_);
          return r;
        }
      }
    }
  }
}
