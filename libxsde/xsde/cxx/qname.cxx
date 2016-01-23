// file      : xsde/cxx/qname.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/strdupx.hxx>
#include <xsde/cxx/qname.hxx>

namespace xsde
{
  namespace cxx
  {

#ifdef XSDE_EXCEPTIONS

    void qname::
    prefix_copy (const char* prefix)
    {
#ifndef XSDE_CUSTOM_ALLOCATOR
      delete[] prefix_;
#else
      cxx::free (prefix_);
#endif

      if (prefix)
        prefix_ = strdupx (prefix);
      else
        prefix_ = 0;
    }

    void qname::
    name_copy (const char* name)
    {
#ifndef XSDE_CUSTOM_ALLOCATOR
      delete[] name_;
#else
      cxx::free (name_);
#endif

      if (name)
        name_ = strdupx (name);
      else
        name_ = 0;
    }

    struct qname_guard
    {
      qname_guard (qname* p) : p_ (p) {}

      ~qname_guard ()
      {
#ifndef XSDE_CUSTOM_ALLOCATOR
        delete p_;
#else
        if (p_ != 0)
        {
          p_->~qname ();
          cxx::free (p_);
        }
#endif
      }

      void
      release () { p_ = 0; }

    private:
      qname* p_;
    };

    qname* qname::
    _clone () const
    {
#ifndef XSDE_CUSTOM_ALLOCATOR
      qname* c = new qname;
#else
      // Default qname c-tor cannot throw so we don't need alloc_guard.
      //
      qname* c = static_cast<qname*> (cxx::alloc (sizeof (qname)));
      new (c) qname;
#endif
      qname_guard g (c);
      _copy (*c);
      g.release ();
      return c;
    }

#else

    qname::error qname::
    prefix_copy (const char* prefix)
    {
#ifndef XSDE_CUSTOM_ALLOCATOR
      delete[] prefix_;
#else
      cxx::free (prefix_);
#endif

      if (prefix)
      {
        prefix_ = strdupx (prefix);

        if (prefix_ == 0)
          return error_no_memory;
      }
      else
        prefix_ = 0;

      return error_none;
    }

    qname::error qname::
    name_copy (const char* name)
    {
#ifndef XSDE_CUSTOM_ALLOCATOR
      delete[] name_;
#else
      cxx::free (name_);
#endif

      if (name)
      {
        name_ = strdupx (name);

        if (name_ == 0)
          return error_no_memory;
      }
      else
        name_ = 0;

      return error_none;
    }

    qname* qname::
    _clone () const
    {
#ifndef XSDE_CUSTOM_ALLOCATOR
      qname* c = new qname;
#else
      qname* c = static_cast<qname*> (cxx::alloc (sizeof (qname)));
#endif

      if (c == 0)
        return 0;

#ifdef XSDE_CUSTOM_ALLOCATOR
      new (c) qname;
#endif

      if (!_copy (*c))
      {
#ifndef XSDE_CUSTOM_ALLOCATOR
        delete c;
#else
        c->~qname ();
        cxx::free (c);
#endif
        return 0;
      }

      return c;
    }

#endif
  }
}
