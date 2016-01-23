// file      : xsde/cxx/parser/validating/qname-stl.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/xml/ncname.hxx>

#include <xsde/cxx/parser/validating/qname-stl.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
      {
        void qname_pimpl::
        _pre ()
        {
          str_.erase ();
        }

        void qname_pimpl::
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

        void qname_pimpl::
        _post ()
        {
          ro_string tmp (str_.data (), str_.size ());
          ro_string::size_type size = trim_right (tmp);
          ro_string::size_type pos = tmp.find (':');

          const char* s = tmp.data ();

          if (pos != ro_string::npos)
          {
            if (xml::valid_ncname (s, pos) &&
                xml::valid_ncname (s + pos + 1, size - pos - 1))
            {
              prefix_.assign (s, pos);
              name_.assign (s + pos + 1, size - pos - 1);
            }
            else
              _schema_error (schema_error::invalid_qname_value);
          }
          else
          {
            if (xml::valid_ncname (s, size))
            {
              prefix_.erase ();
              str_.resize (size);
              name_.swap (str_);
            }
            else
              _schema_error (schema_error::invalid_qname_value);
          }
        }

        qname qname_pimpl::
        post_qname ()
        {
          return qname (prefix_, name_);
        }
      }
    }
  }
}
