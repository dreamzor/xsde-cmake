// file      : xsde/cxx/serializer/validating/qname-stl.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/xml/ncname.hxx>

#include <xsde/cxx/serializer/validating/qname-stl.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
        void qname_simpl::
        pre (const qname& value)
        {
          value_ = value;
        }

        void qname_simpl::
        _serialize_content ()
        {
          // Make sure we don't hold any references to the qname.
          //
          qname tmp ("a");
          tmp.swap (value_);

          const char* ns = tmp.name ().c_str ();
          size_t nn = tmp.name ().size ();

          if (!tmp.prefix ().empty ())
          {
            const char* ps = tmp.prefix ().c_str ();
            size_t pn = tmp.prefix ().size ();

            if (xml::valid_ncname (ps, pn) && xml::valid_ncname (ns, nn))
            {
#ifdef XSDE_EXCEPTIONS
              _characters (ps, pn);
              _characters (":", 1);
              _characters (ns, nn);
#else
              if (_characters (ps, pn))
              {
                if (_characters (":", 1))
                  _characters (ns, nn);
              }
#endif
            }
            else
              _schema_error (schema_error::invalid_qname_value);
          }
          else
          {
            if (xml::valid_ncname (ns, nn))
              _characters (ns, nn);
            else
              _schema_error (schema_error::invalid_qname_value);
          }
        }
      }
    }
  }
}
