// file      : xsde/cxx/parser/validating/qname.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/config.hxx>

#ifdef XSDE_CUSTOM_ALLOCATOR
#  include <xsde/cxx/allocator.hxx>
#endif

#include <xsde/cxx/xml/ncname.hxx>

#include <xsde/cxx/parser/validating/qname.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
      {
        qname_pimpl::
        ~qname_pimpl ()
        {
          if (!base_ && qn_)
          {
#ifndef XSDE_CUSTOM_ALLOCATOR
            delete qn_;
#else
            qn_->~qname ();
            cxx::free (qn_);
#endif
          }
        }

        void qname_pimpl::
        _reset ()
        {
          qname_pskel::_reset ();

          if (!base_ && qn_)
          {
#ifndef XSDE_CUSTOM_ALLOCATOR
            delete qn_;
#else
            qn_->~qname ();
            cxx::free (qn_);
#endif
            qn_ = 0;
          }
        }

        qname_pimpl::
        qname_pimpl (bool base)
            : base_ (base), qn_ (0)
        {
        }

        void qname_pimpl::
        pre_impl (qname* qn)
        {
          qn_ = qn;
        }

        void qname_pimpl::
        _pre ()
        {
          if (qn_ == 0)
          {
#ifndef XSDE_CUSTOM_ALLOCATOR
            qn_ = new qname ();
#else
            qn_ = static_cast<qname*> (alloc (sizeof (qname)));

#ifdef XSDE_EXCEPTIONS
            alloc_guard ag (qn_);
            new (qn_) qname ();
            ag.release ();
#else
            if (qn_)
              new (qn_) qname ();
#endif
#endif

#ifndef XSDE_EXCEPTIONS
            if (qn_ == 0)
            {
              _sys_error (sys_error::no_memory);
              return;
            }
#endif
          }

#ifdef XSDE_EXCEPTIONS
          str_.assign ("", 0);
#else
          if (str_.assign ("", 0))
            _sys_error (sys_error::no_memory);
#endif
        }

        void qname_pimpl::
        _characters (const ro_string& s)
        {
          if (str_.size () == 0)
          {
            ro_string tmp (s.data (), s.size ());

            if (trim_left (tmp) != 0)
            {
#ifdef XSDE_EXCEPTIONS
              str_.append (tmp.data (), tmp.size ());
#else
              if (str_.append (tmp.data (), tmp.size ()))
                _sys_error (sys_error::no_memory);
#endif
            }
          }
          else
          {
#ifdef XSDE_EXCEPTIONS
            str_.append (s.data (), s.size ());
#else
            if (str_.append (s.data (), s.size ()))
              _sys_error (sys_error::no_memory);
#endif
          }
        }

        void qname_pimpl::
        _post ()
        {
          ro_string tmp (str_.data (), str_.size ());
          ro_string::size_type size = trim_right (tmp);
          ro_string::size_type pos = tmp.find (':');

          string name;
          string prefix;

          const char* s = tmp.data ();

          if (pos != ro_string::npos)
          {
            if (xml::valid_ncname (s, pos) &&
                xml::valid_ncname (s + pos + 1, size - pos - 1))
            {
#ifdef XSDE_EXCEPTIONS
              prefix.assign (s, pos);
              name.assign (s + pos + 1, size - pos - 1);
#else
              if (prefix.assign (s, pos) ||
                  name.assign (s + pos + 1, size - pos - 1))
              {
                _sys_error (sys_error::no_memory);
                return;
              }
#endif
            }
            else
            {
              _schema_error (schema_error::invalid_qname_value);
              return;
            }
          }
          else
          {
            if (xml::valid_ncname (s, size))
            {
#ifdef XSDE_EXCEPTIONS
              prefix.assign ("", 0);
              str_.truncate (size);
              name.swap (str_);
#else
              if (prefix.assign ("", 0))
              {
                _sys_error (sys_error::no_memory);
                return;
              }
              else
              {
                str_.truncate (size);
                name.swap (str_);
              }
#endif
            }
            else
            {
              _schema_error (schema_error::invalid_qname_value);
              return;
            }
          }

          qn_->prefix (prefix.detach ());
          qn_->name (name.detach ());
        }

        qname* qname_pimpl::
        post_qname ()
        {
          qname* r = qn_;
          qn_ = 0;
          return r;
        }
      }
    }
  }
}
