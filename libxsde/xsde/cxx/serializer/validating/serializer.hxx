// file      : xsde/cxx/serializer/validating/serializer.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_VALIDATING_SERIALIZER_HXX
#define XSDE_CXX_SERIALIZER_VALIDATING_SERIALIZER_HXX

#include <xsde/cxx/config.hxx>

#include <xsde/cxx/serializer/elements.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
        struct empty_content: serializer_base
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          empty_content ();
          empty_content (empty_content* impl, void*);
#endif
        };

        //
        //
        struct simple_content: empty_content
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          virtual void
          _serialize_content ();

          simple_content ();
          simple_content (simple_content* impl, void*);
#endif
        };

        //
        //
        struct complex_content: empty_content
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          complex_content ();
          complex_content (complex_content* impl, void*);
#endif
        };
      }
    }
  }
}

#include <xsde/cxx/serializer/validating/serializer.ixx>

#endif  // XSDE_CXX_SERIALIZER_VALIDATING_SERIALIZER_HXX
