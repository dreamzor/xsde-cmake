// file      : xsde/cxx/qname.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <string.h> // strcmp

#ifdef XSDE_CUSTOM_ALLOCATOR
#  include <xsde/cxx/allocator.hxx>
#endif

namespace xsde
{
  namespace cxx
  {
    // c-tors, d-tor and swap
    //
    inline qname::
    ~qname ()
    {
#ifndef XSDE_CUSTOM_ALLOCATOR
      delete[] prefix_;
      delete[] name_;
#else
      cxx::free (prefix_);
      cxx::free (name_);
#endif
    }

    inline qname::
    qname ()
        : prefix_ (0), name_ (0)
    {
    }

    inline qname::
    qname (char* n)
        : prefix_ (0), name_ (n)
    {
    }

    inline qname::
    qname (char* p, char* n)
        : prefix_ (p), name_ (n)
    {
    }

    inline void qname::
    swap (qname& x)
    {
      char* p = prefix_;
      char* n = name_;

      prefix_ = x.prefix_;
      name_ = x.name_;

      x.prefix_ = p;
      x.name_ = n;
    }

    // preix
    //
    inline char* qname::
    prefix ()
    {
      return prefix_;
    }

    inline const char* qname::
    prefix () const
    {
      return prefix_;
    }

    inline void qname::
    prefix (char* prefix)
    {
#ifndef XSDE_CUSTOM_ALLOCATOR
      delete[] prefix_;
#else
      cxx::free (prefix_);
#endif
      prefix_ = prefix;
    }

    inline char* qname::
    prefix_detach ()
    {
      char* r = prefix_;
      prefix_ = 0;
      return r;
    }

    // name
    //
    inline char* qname::
    name ()
    {
      return name_;
    }

    inline const char* qname::
    name () const
    {
      return name_;
    }

    inline void qname::
    name (char* name)
    {
#ifndef XSDE_CUSTOM_ALLOCATOR
      delete[] name_;
#else
      cxx::free (name_);
#endif
      name_ = name;
    }

    inline char* qname::
    name_detach ()
    {
      char* r = name_;
      name_ = 0;
      return r;
    }

#ifdef XSDE_EXCEPTIONS
    inline void qname::
    _copy (qname& c) const
    {
      c.prefix_copy (prefix_);
      c.name_copy (name_);
    }
#else
    inline bool qname::
    _copy (qname& c) const
    {
      if (c.prefix_copy (prefix_) || c.name_copy (name_))
        return false;

      return true;
    }
#endif

    //
    //
    inline bool
    operator== (const qname& x, const qname& y)
    {
      return strcmp (x.name (), y.name ()) == 0 &&
        strcmp (x.prefix (), y.prefix ()) == 0;
    }

    inline bool
    operator!= (const qname& x, const qname& y)
    {
      return !(x == y);
    }
  }
}
