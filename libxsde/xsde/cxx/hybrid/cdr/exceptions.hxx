// file      : xsde/cxx/hybrid/cdr/exceptions.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_HYBRID_CDR_EXCEPTIONS_HXX
#define XSDE_CXX_HYBRID_CDR_EXCEPTIONS_HXX

#include <xsde/cxx/exceptions.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace hybrid
    {
      struct cdr_exception: xsde::cxx::exception
      {
        virtual const char*
        what () const throw ();
      };
    }
  }
}

#endif  // XSDE_CXX_HYBRID_CDR_EXCEPTIONS_HXX
