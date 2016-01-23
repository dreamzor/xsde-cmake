// file      : xsde/cxx/hybrid/any-type-sskel.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/hybrid/any-type-sskel.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace hybrid
    {
#ifdef XSDE_POLYMORPHIC
      const char* any_type_sskel::
      _static_type ()
      {
        return "anyType http://www.w3.org/2001/XMLSchema";
      }

      const char* any_type_sskel::
      _dynamic_type () const
      {
        return _static_type ();
      }
#endif
    }
  }
}
