// file      : xsde/cxx/hybrid/any-type.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/config.hxx>

#ifdef XSDE_CUSTOM_ALLOCATOR
#  include <xsde/cxx/allocator.hxx>
#endif

#include <xsde/cxx/hybrid/any-type.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace hybrid
    {
      // any_type
      //
      any_type::
      ~any_type ()
      {
#ifndef XSDE_CUSTOM_ALLOCATOR
        delete data_;
#else
        if (data_ != 0)
        {
          data_->~data_sequence ();
          cxx::free (data_);
        }
#endif
      }

#ifdef XSDE_EXCEPTIONS
      void any_type::
      allocate_custom_data ()
      {
        if (data_ != 0)
          return;

#ifndef XSDE_CUSTOM_ALLOCATOR
        data_ = new data_sequence;
#else
        // Default data_sequence c-tor cannot throw so we don't need a guard.
        //
        data_ = static_cast<data_sequence*> (
          cxx::alloc (sizeof (data_sequence)));
        new (data_) data_sequence;
#endif
      }

      void any_type::
      _copy (any_type& c) const
      {
        if (data_ != 0)
        {
          c.allocate_custom_data ();
          data_->copy (c.custom_data ());
        }
      }

      struct any_type_guard
      {
        any_type_guard (any_type* p) : p_ (p) {}

        ~any_type_guard ()
        {
#ifndef XSDE_CUSTOM_ALLOCATOR
          delete p_;
#else
          if (p_ != 0)
          {
            p_->~any_type ();
            cxx::free (p_);
          }
#endif
        }

        void
        release () { p_ = 0; }

      private:
        any_type* p_;
      };

      any_type* any_type::
      _clone () const
      {
#ifndef XSDE_CUSTOM_ALLOCATOR
        any_type* c = new any_type;
#else
        // Default any_type c-tor cannot throw so we don't need alloc_guard.
        //
        any_type* c = static_cast<any_type*> (cxx::alloc (sizeof (any_type)));
        new (c) any_type;
#endif
        any_type_guard g (c);
        _copy (*c);
        g.release ();
        return c;
      }
#else
      bool any_type::
      allocate_custom_data ()
      {
        if (data_ != 0)
          return true;

#ifndef XSDE_CUSTOM_ALLOCATOR
        data_ = new data_sequence;
#else
        data_ = static_cast<data_sequence*> (
          cxx::alloc (sizeof (data_sequence)));
#endif
        if (data_ == 0)
          return false;

#ifdef XSDE_CUSTOM_ALLOCATOR
        new (data_) data_sequence;
#endif
        return true;
      }

      bool any_type::
      _copy (any_type& c) const
      {
        if (data_ != 0)
        {
          if (!c.allocate_custom_data () ||
              !data_->copy (c.custom_data ()))
            return false;
        }

        return true;
      }

      any_type* any_type::
      _clone () const
      {
#ifndef XSDE_CUSTOM_ALLOCATOR
        any_type* c = new any_type;
#else
        any_type* c = static_cast<any_type*> (cxx::alloc (sizeof (any_type)));
#endif

        if (c == 0)
          return 0;

#ifdef XSDE_CUSTOM_ALLOCATOR
        new (c) any_type;
#endif

        if (!_copy (*c))
        {
#ifndef XSDE_CUSTOM_ALLOCATOR
          delete c;
#else
          c->~any_type ();
          cxx::free (c);
#endif
          return 0;
        }

        return c;
      }
#endif

#ifdef XSDE_POLYMORPHIC
#ifdef XSDE_STL
      const std::string& any_type::
      _dynamic_type () const
      {
        return _static_type ();
      }

      static const std::string any_type_static_type_ =
        "anyType http://www.w3.org/2001/XMLSchema";

      const std::string& any_type::
      _static_type ()
      {
        return any_type_static_type_;
      }
#else
      const char* any_type::
      _dynamic_type () const
      {
        return _static_type ();
      }

      const char* any_type::
      _static_type ()
      {
        return "anyType http://www.w3.org/2001/XMLSchema";
      }
#endif
#endif
    }
  }
}
