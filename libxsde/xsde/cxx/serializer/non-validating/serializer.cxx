// file      : xsde/cxx/serializer/non-validating/serializer.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/serializer/non-validating/serializer.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace non_validating
      {
        // simple_content
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        void simple_content::
        _serialize_content ()
        {
          if (impl_)
            impl_->_serialize_content ();
        }
#endif
      }
    }
  }
}
