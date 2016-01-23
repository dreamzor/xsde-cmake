// file      : xsde/cxx/serializer/genx/document.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace genx
      {
        // serializer_auto_ptr
        //
        inline serializer_auto_ptr::
        ~serializer_auto_ptr ()
        {
          if (serializer_ != 0)
            genxDispose (serializer_);
        }

        inline serializer_auto_ptr::
        serializer_auto_ptr (genxWriter serializer)
            : serializer_ (serializer)
        {
        }

        inline serializer_auto_ptr& serializer_auto_ptr::
        operator= (genxWriter serializer)
        {
          if (serializer_ != 0)
            genxDispose (serializer_);

          serializer_ = serializer;
          return *this;
        }

        // document_simpl
        //

#ifdef XSDE_STL
        inline void document_simpl::
        add_prefix (const std::string& p, const std::string& ns)
        {
          add_prefix (p.c_str (), ns.c_str ());
        }

        inline void document_simpl::
        add_default_prefix (const std::string& ns)
        {
          add_default_prefix (ns.c_str ());
        }

        inline void document_simpl::
        add_schema (const std::string& ns, const std::string& l  )
        {
          add_schema (ns.c_str (), l.c_str ());
        }

        inline void document_simpl::
        add_no_namespace_schema (const std::string& l)
        {
          add_no_namespace_schema (l.c_str ());
        }
#endif

        inline void document_simpl::
        serialize (write_bound_func wbf, flush_func ff,
                   void* user_data, flags f)
        {
          serialize (0, wbf, ff, user_data, f);
        }

#ifndef XSDE_EXCEPTIONS
        inline const error& document_simpl::
        _error () const
        {
          return error_;
        }
#endif
      }
    }
  }
}
