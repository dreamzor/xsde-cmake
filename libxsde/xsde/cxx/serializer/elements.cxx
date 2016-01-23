// file      : xsde/cxx/serializer/elements.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <assert.h>

#include <xsde/cxx/serializer/elements.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      // serializer_base
      //
      serializer_base::
      ~serializer_base ()
      {
      }

      void serializer_base::
      _pre ()
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        if (impl_)
          impl_->_pre ();
#endif
      }

      void serializer_base::
      _serialize_attributes ()
      {
      }

      void serializer_base::
      _serialize_content ()
      {
      }

      void serializer_base::
      _post ()
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        if (impl_)
          impl_->_post ();
#endif
      }

      void serializer_base::
      post ()
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        if (impl_)
          impl_->post ();
#endif
      }

      void serializer_base::
      _pre_impl (context& c)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        assert (parent_ == 0);

        // Set the parent_ pointers in the tied-in implementations.
        //
        _set_parent_chain ();
#endif
        ++depth_;
        context_ = &c;

        _pre ();
      }

      void serializer_base::
      _post_impl ()
      {
#if defined(XSDE_SERIALIZER_VALIDATION) || !defined(XSDE_EXCEPTIONS)
        if (!context_->error_type ())
#endif
          _post ();

        if (--depth_ == 0)
          context_ = 0;
      }

#ifdef XSDE_POLYMORPHIC
      const char* serializer_base::
      _dynamic_type () const
      {
        return 0;
      }
#endif

      void serializer_base::
      _reset ()
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        if (impl_)
          impl_->_reset ();
#endif

#ifndef XSDE_EXCEPTIONS
        error_type_ = error_none;
#endif
        context_ = 0;
        depth_ = 0;
      }

#if defined (XSDE_REUSE_STYLE_TIEIN) && !defined (XSDE_EXCEPTIONS)
      const serializer_base* serializer_base::
      _ultimate_impl () const
      {
        const serializer_base* s = impl_;
        for (; s->impl_ != 0; s = s->impl_) /*noop*/;
        return s;
      }
#endif
    }
  }
}
