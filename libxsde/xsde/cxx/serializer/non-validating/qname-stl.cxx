// file      : xsde/cxx/serializer/non-validating/qname-stl.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/serializer/non-validating/qname-stl.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace non_validating
      {
        void qname_simpl::
        pre (const qname& value)
        {
          value_ = value;
        }

        void qname_simpl::
        _serialize_content ()
        {
          // Make sure we don't hold any references to the qname.
          //
          qname tmp ("a");
          tmp.swap (value_);

          if (!tmp.prefix ().empty ())
          {
#ifdef XSDE_EXCEPTIONS
            _characters (tmp.prefix ().c_str (), tmp.prefix ().size ());
            _characters (":", 1);
            _characters (tmp.name ().c_str (), tmp.name ().size ());
#else
            if (_characters (tmp.prefix ().c_str (), tmp.prefix ().size ()))
            {
              if (_characters (":", 1))
                _characters (tmp.name ().c_str (), tmp.name ().size ());
            }
#endif
          }
          else
            _characters (tmp.name ().c_str (), tmp.name ().size ());
        }
      }
    }
  }
}
