// file      : xsde/cxx/qname-stl.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsde
{
  namespace cxx
  {
    inline qname::
    qname ()
    {
    }

    inline qname::
    qname (const std::string& name)
        : prefix_ (), name_ (name)
    {
    }

    inline qname::
    qname (const std::string& prefix, const std::string& name)
        : prefix_ (prefix), name_ (name)
    {
    }

    inline void qname::
    swap (qname& x)
    {
      prefix_.swap (x.prefix_);
      name_.swap (x.name_);
    }

    inline const std::string& qname::
    prefix () const
    {
      return prefix_;
    }

    inline std::string& qname::
    prefix ()
    {
      return prefix_;
    }

    inline void qname::
    prefix (const std::string& prefix)
    {
      prefix_ = prefix;
    }

    inline const std::string& qname::
    name () const
    {
      return name_;
    }

    inline std::string& qname::
    name ()
    {
      return name_;
    }

    inline void qname::
    name (const std::string& name)
    {
      name_ = name;
    }

    inline bool
    operator== (const qname& x, const qname& y)
    {
      return x.name () == y.name () && x.prefix () == y.prefix ();
    }

    inline bool
    operator!= (const qname& x, const qname& y)
    {
      return !(x == y);
    }
  }
}
