// file      : xsde/cxx/parser/elements.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      inline parser_base::
      parser_base ()
          : resetting_ (false), context_ (0)
      {
#ifndef XSDE_EXCEPTIONS
        error_type_ = error_none;
#endif

#ifdef XSDE_REUSE_STYLE_TIEIN
        parent_ = 0;
        impl_ = 0;
#endif
      }

#ifdef XSDE_REUSE_STYLE_TIEIN
      inline parser_base::
      parser_base (parser_base* impl, void*)
          : resetting_ (false), context_ (0)
      {
#ifndef XSDE_EXCEPTIONS
        error_type_ = error_none;
#endif
        parent_ = 0;
        impl_ = impl;
      }
#endif

#ifdef XSDE_REUSE_STYLE_TIEIN
      inline void parser_base::
      _set_parent_chain ()
      {
        if (impl_ && impl_->parent_ == 0)
        {
          for (parser_base* p = impl_; p != 0; p = p->impl_)
            p->parent_ = this;
        }
      }
#endif

      inline context& parser_base::
      _context ()
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        return *(parent_ ? parent_->context_ : context_);
#else
        return *context_;
#endif
      }

      // Error handling.
      //
#ifndef XSDE_EXCEPTIONS
      inline error parser_base::
      _error () const
      {
        // Unlike context, which is stored in the top-level
        // parser, error state is stored in the "bottom-level"
        // implementation. It is done this way since the error
        // handling mechanism can be used in constructors which
        // would otherwise require passing the pointer to parent
        // parser to each implementation's c-tor.
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        const parser_base* p = !impl_ ? this : _ultimate_impl ();
#else
        const parser_base* p = this;
#endif
        switch (p->error_type_)
        {
        case error_sys:
          {
            return error (p->error_code_.sys);
          }
        case error_app:
          {
            return error (p->error_code_.app, 0, 0);
          }
        default:
          {
            return error ();
          }
        }
      }

      inline void parser_base::
      _app_error (int e)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        parser_base* p = parent_ ? parent_ : this;
#else
        parser_base* p = this;
#endif

        if (p->context_ != 0)
        {
          p->context_->app_error (e);
        }
        else
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (!impl_)
            p = this;
          else
            for (p = impl_; p->impl_ != 0; p = p->impl_) /*noop*/ ;
#endif
          p->error_type_ = error_app;
          p->error_code_.app = e;
        }
      }

      inline int parser_base::
      _app_error () const
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        const parser_base* p = !impl_ ? this : _ultimate_impl ();
#else
        const parser_base* p = this;
#endif
        return p->error_code_.app;
      }

      inline void parser_base::
      _sys_error (context::sys_error_t e)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        parser_base* p = parent_ ? parent_ : this;
#else
        parser_base* p = this;
#endif
        if (p->context_ != 0)
        {
          p->context_->sys_error (e);
        }
        else
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (!impl_)
            p = this;
          else
            for (p = impl_; p->impl_ != 0; p = p->impl_) /*noop*/;
#endif
          p->error_type_ = error_sys;
          p->error_code_.sys = e;
        }
      }

      inline context::sys_error_t parser_base::
      _sys_error () const
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        const parser_base* p = !impl_ ? this : _ultimate_impl ();
#else
        const parser_base* p = this;
#endif
        return p->error_code_.sys;
      }

      inline parser_base::error_type_t parser_base::
      _error_type () const
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        const parser_base* p = !impl_ ? this : _ultimate_impl ();
#else
        const parser_base* p = this;
#endif
        return p->error_type_;
      }

      inline void parser_base::
      _copy_error (context& ctx) const
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        const parser_base* p = !impl_ ? this : _ultimate_impl ();
#else
        const parser_base* p = this;
#endif

        switch (p->error_type_)
        {
        case error_app:
          {
            ctx.app_error (p->error_code_.app);
            break;
          }
        case error_sys:
          {
            ctx.sys_error (p->error_code_.sys);
            break;
          }
        default:
          break;
        }
      }
#endif // XSDE_EXCEPTIONS

#ifdef XSDE_PARSER_VALIDATION
      inline void parser_base::
      _schema_error (context::schema_error_t e)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        parser_base* p = parent_ ? parent_ : this;
#else
        parser_base* p = this;
#endif
        p->context_->schema_error (e);
      }
#endif
    }
  }
}
