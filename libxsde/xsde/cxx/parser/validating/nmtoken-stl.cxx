// file      : xsde/cxx/parser/validating/nmtoken-stl.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/xml/char-table.hxx>

#include <xsde/cxx/parser/validating/nmtoken-stl.hxx>
#include <xsde/cxx/parser/validating/string-common.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
      {
        void nmtoken_pimpl::
        _pre ()
        {
          str_.erase ();
        }

        void nmtoken_pimpl::
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

        void nmtoken_pimpl::
        _post ()
        {
          if (!string_common::validate_facets (str_, _facets (), _context ()))
            return;

          typedef std::string::size_type size_type;
          size_type size = str_.size ();

          // For now we are only checking the US-ASCII characters.
          //

          bool ok = (size != 0);

          if (ok)
          {
            for (size_type i = 0; i < size; ++i)
            {
              unsigned char c = static_cast<unsigned char> (str_[i]);

              if (c < 0x80 && !(xml::char_table[c] & xml::name_char_mask))
              {
                ok = false;
                break;
              }
            }
          }

          if (!ok)
            _schema_error (schema_error::invalid_nmtoken_value);
        }

        std::string nmtoken_pimpl::
        post_nmtoken ()
        {
          std::string r;
          r.swap (str_);
          return r;
        }
      }
    }
  }
}
