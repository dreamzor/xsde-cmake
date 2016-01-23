// file      : xsde/cxx/parser/non-validating/qname-stl.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/parser/non-validating/qname-stl.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace non_validating
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

        qname qname_pimpl::
        post_qname ()
        {
          ro_string tmp (str_.data (), str_.size ());
          ro_string::size_type size = trim_right (tmp);
          ro_string::size_type pos = tmp.find (':');

          if (pos != ro_string::npos)
          {
            std::string prefix (tmp.data (), pos);
            std::string name (tmp.data () + pos + 1, size - pos - 1);
            return qname (prefix, name);
          }
          else
          {
            str_.resize (size);
            return qname (str_);
          }
        }
      }
    }
  }
}
