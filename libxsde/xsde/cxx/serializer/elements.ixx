// file      : xsde/cxx/serializer/elements.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      inline serializer_base::
      serializer_base ()
          : resetting_ (false), context_ (0), depth_ (0)
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
      inline serializer_base::
      serializer_base (serializer_base* impl, void*)
          : resetting_ (false), context_ (0), depth_ (0)
      {
#ifndef XSDE_EXCEPTIONS
        error_type_ = error_none;
#endif
        parent_ = 0;
        impl_ = impl;
      }
#endif

#ifdef XSDE_REUSE_STYLE_TIEIN
      inline void serializer_base::
      _set_parent_chain ()
      {
        if (impl_ && impl_->parent_ == 0)
        {
          for (serializer_base* s = impl_; s != 0; s = s->impl_)
            s->parent_ = this;
        }
      }
#endif

      inline context& serializer_base::
      _context ()
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        return *(parent_ ? parent_->context_ : context_);
#else
        return *context_;
#endif
      }

#ifdef XSDE_EXCEPTIONS
      inline void serializer_base::
      _start_element (const char* name)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        s->context_->start_element (name);
      }

      inline void serializer_base::
      _start_element (const char* ns, const char* name)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        s->context_->start_element (ns, name);
      }

      inline void serializer_base::
      _end_element ()
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        s->context_->end_element ();
      }

      inline void serializer_base::
      _start_attribute (const char* name)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        s->context_->start_attribute (name);
      }

      inline void serializer_base::
      _start_attribute (const char* ns, const char* name)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        s->context_->start_attribute (ns, name);
      }

      inline void serializer_base::
      _end_attribute ()
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        s->context_->end_attribute ();
      }

      inline void serializer_base::
      _attribute (const char* name, const char* value)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        s->context_->attribute (name, value);
      }

      inline void serializer_base::
      _attribute (const char* ns, const char* name, const char* value)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        s->context_->attribute (ns, name, value);
      }

      inline void serializer_base::
      _characters (const char* str)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        s->context_->characters (str);
      }

      inline void serializer_base::
      _characters (const char* str, size_t n)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        s->context_->characters (str, n);
      }

      inline void serializer_base::
      _declare_namespace (const char* ns, const char* p)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        s->context_->declare_namespace (ns, p);
      }

      inline void serializer_base::
      _declare_default_namespace (const char* ns)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        s->context_->declare_default_namespace (ns);
      }

      inline void serializer_base::
      _clear_default_namespace ()
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        s->context_->clear_default_namespace ();
      }

      inline const char* serializer_base::
      _lookup_namespace_prefix (const char* ns)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        return s->context_->lookup_namespace_prefix (ns);
      }

#ifdef XSDE_POLYMORPHIC
      inline void serializer_base::
      _set_type (const char* type)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        s->context_->set_type (type);
      }
#endif

#else // XSDE_EXCEPTIONS

      inline bool serializer_base::
      _start_element (const char* name)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        return s->context_->start_element (name);
      }

      inline bool serializer_base::
      _start_element (const char* ns, const char* name)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        return s->context_->start_element (ns, name);
      }

      inline bool serializer_base::
      _end_element ()
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        return s->context_->end_element ();
      }

      inline bool serializer_base::
      _start_attribute (const char* name)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        return s->context_->start_attribute (name);
      }

      inline bool serializer_base::
      _start_attribute (const char* ns, const char* name)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        return s->context_->start_attribute (ns, name);
      }

      inline bool serializer_base::
      _end_attribute ()
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        return s->context_->end_attribute ();
      }

      inline bool serializer_base::
      _attribute (const char* name, const char* value)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        return s->context_->attribute (name, value);
      }

      inline bool serializer_base::
      _attribute (const char* ns, const char* name, const char* value)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        return s->context_->attribute (ns, name, value);
      }

      inline bool serializer_base::
      _characters (const char* str)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        return s->context_->characters (str);
      }

      inline bool serializer_base::
      _characters (const char* str, size_t n)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        return s->context_->characters (str, n);
      }

      inline bool serializer_base::
      _declare_namespace (const char* ns, const char* p)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        return s->context_->declare_namespace (ns, p);
      }

      inline bool serializer_base::
      _declare_default_namespace (const char* ns)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        return s->context_->declare_default_namespace (ns);
      }

      inline bool serializer_base::
      _clear_default_namespace ()
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        return s->context_->clear_default_namespace ();
      }

      inline const char* serializer_base::
      _lookup_namespace_prefix (const char* ns)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        return s->context_->lookup_namespace_prefix (ns);
      }

#ifdef XSDE_POLYMORPHIC
      inline bool serializer_base::
      _set_type (const char* type)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        return s->context_->set_type (type);
      }
#endif

#endif // !XSDE_EXCEPTIONS

      // Error handling.
      //
#ifndef XSDE_EXCEPTIONS
      inline error serializer_base::
      _error () const
      {
        // Unlike context, which is stored in the top-level
        // serializer, error state is stored in the "bottom-
        // level" implementation. It is done this way since the
        // error handling mechanism can be used in constructors
        // which would otherwise require passing the pointer to
        // parent serializer to each implementation's c-tor.
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        const serializer_base* s = !impl_ ? this : _ultimate_impl ();
#else
        const serializer_base* s = this;
#endif
        switch (s->error_type_)
        {
        case error_sys:
          {
            return error (s->error_code_.sys);
          }
        case error_app:
          {
            return error (s->error_code_.app);
          }
        default:
          {
            return error ();
          }
        }
      }

      inline void serializer_base::
      _app_error (int e)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif

        if (s->context_ != 0)
        {
          s->context_->app_error (e);
        }
        else
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (!impl_)
            s = this;
          else
            for (s = impl_; s->impl_ != 0; s = s->impl_) /*noop*/;
#endif
          s->error_type_ = error_app;
          s->error_code_.app = e;
        }
      }

      inline int serializer_base::
      _app_error () const
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        const serializer_base* s = !impl_ ? this : _ultimate_impl ();
#else
        const serializer_base* s = this;
#endif
        return s->error_code_.app;
      }

      inline void serializer_base::
      _sys_error (context::sys_error_t e)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        if (s->context_ != 0)
        {
          s->context_->sys_error (e);
        }
        else
        {
#ifdef XSDE_REUSE_STYLE_TIEIN
          if (!impl_)
            s = this;
          else
            for (s = impl_; s->impl_ != 0; s = s->impl_) /*noop*/;
#endif
          s->error_type_ = error_sys;
          s->error_code_.sys = e;
        }
      }

      inline context::sys_error_t serializer_base::
      _sys_error () const
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        const serializer_base* s = !impl_ ? this : _ultimate_impl ();
#else
        const serializer_base* s = this;
#endif
        return s->error_code_.sys;
      }

      inline void serializer_base::
      _xml_error (context::xml_error_t e)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        s->context_->xml_error (e);
      }

      inline serializer_base::error_type_t serializer_base::
      _error_type () const
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        const serializer_base* s = !impl_ ? this : _ultimate_impl ();
#else
        const serializer_base* s = this;
#endif
        return s->error_type_;
      }

      inline void serializer_base::
      _copy_error (context& ctx) const
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        const serializer_base* s = !impl_ ? this : _ultimate_impl ();
#else
        const serializer_base* s = this;
#endif
        switch (s->error_type_)
        {
        case error_app:
          {
            ctx.app_error (s->error_code_.app);
            break;
          }
        case error_sys:
          {
            ctx.sys_error (s->error_code_.sys);
            break;
          }
        default:
          break;
        }
      }
#endif // XSDE_EXCEPTIONS

#ifdef XSDE_SERIALIZER_VALIDATION
      inline void serializer_base::
      _schema_error (context::schema_error_t e)
      {
#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base* s = parent_ ? parent_ : this;
#else
        serializer_base* s = this;
#endif
        s->context_->schema_error (e);
      }
#endif
    }
  }
}
