// file      : xsde/cxx/serializer/non-validating/qname.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/serializer/non-validating/qname.hxx>

#ifdef XSDE_CUSTOM_ALLOCATOR
#  include <xsde/cxx/allocator.hxx>
#endif

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace non_validating
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
          const char* p = value_->prefix ();

          if (p != 0 && *p != '\0')
          {
#ifdef XSDE_EXCEPTIONS
            _characters (p);
            _characters (":", 1);
            _characters (value_->name ());
#else
            if (_characters (p))
            {
              if (_characters (":", 1))
                _characters (value_->name ());
            }
#endif
          }
          else
          {
            _characters (value_->name ());
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
