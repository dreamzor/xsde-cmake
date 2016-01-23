// file      : xsde/cxx/qname.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_QNAME_HXX
#define XSDE_CXX_QNAME_HXX

#include <xsde/cxx/config.hxx>

namespace xsde
{
  namespace cxx
  {
    class qname
    {
    public:
#ifndef XSDE_EXCEPTIONS
      enum error
      {
        error_none,
        error_no_memory
      };
#endif

      ~qname ();

      // The default c-tor creates an uninitialized qname. Use
      // modifiers to initialize it.
      //
      qname ();

      explicit
      qname (char* name);
      qname (char* prefix, char* name);

      void
      swap (qname&);

    private:
      qname (const qname&);
      qname& operator= (const qname&);

    public:
      char*
      prefix ();

      const char*
      prefix () const;

      void
      prefix (char*);

#ifndef XSDE_EXCEPTIONS
      error
#else
      void
#endif
      prefix_copy (const char*);

      char*
      prefix_detach ();

    public:
      char*
      name ();

      const char*
      name () const;

      void
      name (char*);

#ifndef XSDE_EXCEPTIONS
      error
#else
      void
#endif
      name_copy (const char*);

      char*
      name_detach ();

      qname*
      _clone () const;

#ifndef XSDE_EXCEPTIONS
      bool
#else
      void
#endif
      _copy (qname&) const;

    private:
      char* prefix_;
      char* name_;
    };

    bool
    operator== (const qname&, const qname&);

    bool
    operator!= (const qname&, const qname&);
  }
}

#include <xsde/cxx/qname.ixx>

#endif  // XSDE_CXX_QNAME_HXX
