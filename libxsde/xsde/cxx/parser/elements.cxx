// file      : xsde/cxx/parser/elements.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <assert.h>

#include <xsde/cxx/parser/elements.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      // parser_base
      //
      parser_base::
      ~parser_base ()
      {
      }

      void parser_base::
      pre ()
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        if (impl_)
          impl_->pre ();
#endif
      }

      void parser_base::
      _pre ()
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        if (impl_)
          impl_->_pre ();
#endif
      }

      void parser_base::
      _post ()
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        if (impl_)
          impl_->_post ();
#endif
      }

#ifdef XSDE_REUSE_STYLE_TIEIN

#ifdef XSDE_POLYMORPHIC
      void parser_base::
      _start_any_element (const ro_string& ns,
                          const ro_string& name,
                          const char* type)
      {
        if (impl_)
          impl_->_start_any_element (ns, name, type);
      }
#else
      void parser_base::
      _start_any_element (const ro_string& ns,
                          const ro_string& name)
      {
        if (impl_)
          impl_->_start_any_element (ns, name);
      }
#endif

      void parser_base::
      _end_any_element (const ro_string& ns,
                        const ro_string& name)
      {
        if (impl_)
          impl_->_end_any_element (ns, name);
      }

      void parser_base::
      _any_attribute (const ro_string& ns,
                      const ro_string& name,
                      const ro_string& value)
      {
        if (impl_)
          impl_->_any_attribute (ns, name, value);
      }

      void parser_base::
      _any_characters (const ro_string& s)
      {
        if (impl_)
          impl_->_any_characters (s);
      }
#else // !XSDE_REUSE_STYLE_TIEIN

#ifdef XSDE_POLYMORPHIC
      void parser_base::
      _start_any_element (const ro_string&,
                          const ro_string&,
                          const char*)
      {
      }
#else
      void parser_base::
      _start_any_element (const ro_string&,
                          const ro_string&)
      {
      }
#endif

      void parser_base::
      _end_any_element (const ro_string&,
                        const ro_string&)
      {
      }

      void parser_base::
      _any_attribute (const ro_string&,
                      const ro_string&,
                      const ro_string&)
      {
      }

      void parser_base::
      _any_characters (const ro_string&)
      {
      }
#endif // XSDE_REUSE_STYLE_TIEIN


      void parser_base::
      _pre_impl (context& c)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        assert (parent_ == 0);

        // Set the parent_ pointers in the tied-in implementations.
        //
        _set_parent_chain ();
#endif
        context_ = &c;

        previous_ = c.current_;

        c.current_.parser_ = this;
        c.current_.depth_ = 0;
        c.current_.any_ = false;

        _pre ();
      }

      void parser_base::
      _post_impl ()
      {
#if defined(XSDE_PARSER_VALIDATION) || !defined(XSDE_EXCEPTIONS)
        if (!context_->error_type ())
#endif
          _post ();

        context_->current_ = previous_;
        context_ = 0;
      }

#ifdef XSDE_POLYMORPHIC
      const char* parser_base::
      _dynamic_type () const
      {
        return 0;
      }
#endif

      void parser_base::
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

        previous_.parser_ = 0;
        previous_.depth_ = 0;
        previous_.any_ = false;
      }

#if defined (XSDE_REUSE_STYLE_TIEIN) && !defined (XSDE_EXCEPTIONS)
      const parser_base* parser_base::
      _ultimate_impl () const
      {
        const parser_base* p = impl_;
        for (; p->impl_ != 0; p = p->impl_) /*noop*/;
        return p;
      }
#endif
    }
  }
}
