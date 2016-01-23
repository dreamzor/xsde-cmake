// file      : xsde/cxx/serializer/validating/qname.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <string.h> // strlen

#include <xsde/cxx/xml/ncname.hxx>

#include <xsde/cxx/serializer/validating/qname.hxx>

#ifdef XSDE_CUSTOM_ALLOCATOR
#  include <xsde/cxx/allocator.hxx>
#endif

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
        qname_simpl::
        ~qname_simpl ()
        {
          if (free_ && value_)
          {
            qname* v = const_cast<qname*> (value_);
#ifndef XSDE_CUSTOM_ALLOCATOR
            delete v;
#else
            v->~qname ();
            cxx::free (v);
#endif
          }
        }

        void qname_simpl::
        pre (const qname* value)
        {
          value_ = value;
        }

        void qname_simpl::
        _serialize_content ()
        {
          const char* ns = value_->name ();
          size_t nn = strlen (ns);

          const char* ps = value_->prefix ();

          if (ps != 0 && *ps != '\0')
          {
            size_t pn = strlen (ps);

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

          if (free_)
          {
            qname* v = const_cast<qname*> (value_);
#ifndef XSDE_CUSTOM_ALLOCATOR
            delete v;
#else
            v->~qname ();
            cxx::free (v);
#endif
            value_ = 0;
          }
        }
      }
    }
  }
}
