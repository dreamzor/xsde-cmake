// file      : xsde/cxx/serializer/elements.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_ELEMENTS_HXX
#define XSDE_CXX_SERIALIZER_ELEMENTS_HXX

#include <xsde/cxx/config.hxx>

#include <stddef.h> // size_t

#include <xsde/cxx/serializer/context.hxx>

#ifndef XSDE_EXCEPTIONS
#  include <xsde/cxx/serializer/error.hxx>
#endif

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      // pre() and post() are overridable pre/post callbacks, i.e., the
      // derived serializer can override them without calling the base
      // version. _pre() and _post() are not overridable pre/post callbacks
      // in the sense that the derived serializer may override them but
      // has to call the base version. The call sequence is as shown below:
      //
      // pre (arg)
      // _pre ()
      // _post ()
      // post ()
      //
      struct serializer_base
      {
        virtual
        ~serializer_base ();

        serializer_base ();

#ifdef XSDE_REUSE_STYLE_TIEIN
        serializer_base (serializer_base* impl, void*);
#endif

        // The pre() signature varies depending on the serializer argument
        // type.
        //

        virtual void
        _pre ();

        virtual void
        _serialize_attributes ();

        virtual void
        _serialize_content ();

        virtual void
        _post ();

        virtual void
        post ();

        // Implementation callbacks for _pre and _post. The _pre and _post
        // callbacks should never be called directly. Instead, the *_impl
        // versions should be used. The _pre_impl and _post_impl functions
        // will eventually call _pre and _post respectively.
        //
        virtual void
        _pre_impl (context&);

        virtual void
        _post_impl ();

#ifdef XSDE_POLYMORPHIC
      public:
        // Dynamic type in the form "<name> <namespace>" with
        // the space and namespace part absent if the type does
        // not have a namespace.
        //
        virtual const char*
        _dynamic_type () const;
#endif

      public:
        context&
        _context ();

        // The XML generation functions below can only be called starting
        // from _pre() and ending with _post(). Because namespace declarations
        // should come after the start_element and before any attributes,
        // _pre is the appropriate place to call the namespace declaration
        // functions. If exceptions are disabled, these functions return
        // true on success and false otherwise.
        //
        // The set_type() function sets the xsi:type attribute. Its argument
        // is the type id in the form "<name> <namespace>" with the space
        // and namespace part absent if the type does not have a namespace.
        //
#ifdef XSDE_EXCEPTIONS
        void
        _start_element (const char* name);

        void
        _start_element (const char* ns, const char* name);

        void
        _end_element ();

        void
        _start_attribute (const char* name);

        void
        _start_attribute (const char* ns, const char* name);

        void
        _end_attribute ();

        void
        _attribute (const char* name, const char* value);

        void
        _attribute (const char* ns, const char* name, const char* value);

        void
        _characters (const char*);

        void
        _characters (const char*, size_t);

        void
        _declare_namespace (const char* ns, const char* prefix);

        void
        _declare_default_namespace (const char* ns);

        void
        _clear_default_namespace ();

        const char*
        _lookup_namespace_prefix (const char* ns);

#ifdef XSDE_POLYMORPHIC
        void
        _set_type (const char* type);
#endif
#else
        bool
        _start_element (const char* name);

        bool
        _start_element (const char* ns, const char* name);

        bool
        _end_element ();

        bool
        _start_attribute (const char* name);

        bool
        _start_attribute (const char* ns, const char* name);

        bool
        _end_attribute ();

        bool
        _attribute (const char* name, const char* value);

        bool
        _attribute (const char* ns, const char* name, const char* value);

        bool
        _characters (const char*);

        bool
        _characters (const char*, size_t);

        bool
        _declare_namespace (const char* ns, const char* prefix);

        bool
        _declare_default_namespace (const char* ns);

        bool
        _clear_default_namespace ();

        const char*
        _lookup_namespace_prefix (const char* ns);

#ifdef XSDE_POLYMORPHIC
        bool
        _set_type (const char* type);
#endif
#endif
        // Reset the serializer state after an error.
        //
        virtual void
        _reset ();

        // Error handling via codes. If the error is set while serializer
        // is in the context, the error is set in the context, instead
        // of the serializer. Since pre() and post() calls are not in
        // context, the serializer stores application and system errors
        // locally for this case.
        //

#ifndef XSDE_EXCEPTIONS
      public:
	error
        _error () const;

        // Set application error.
        //
        void
        _app_error (int);

        int
        _app_error () const;
#endif

        // Schema error.
        //
#ifdef XSDE_SERIALIZER_VALIDATION
      public:
        void
        _schema_error (context::schema_error_t);
#endif

        // XML error.
        //
#ifndef XSDE_EXCEPTIONS
      public:
        void
        _xml_error (context::xml_error_t);
#endif

        // System error.
        //
#ifndef XSDE_EXCEPTIONS
      public:
        context::sys_error_t
        _sys_error () const;

        void
        _sys_error (context::sys_error_t);
#endif

        // Implementation.
        //
#ifndef XSDE_EXCEPTIONS
      public:
        enum error_type_t
        {
          error_none = 0,
          error_app,
          error_sys
        };

        error_type_t
        _error_type () const;

        void
        _copy_error (context&) const;

      protected:
        error_type_t error_type_;

        union
        {
          int app;
          context::sys_error_t sys;
        } error_code_;
#endif

      protected:
        bool resetting_;
        context* context_;
        size_t depth_;

#ifdef XSDE_REUSE_STYLE_TIEIN
      protected:
        serializer_base* parent_;
        serializer_base* impl_;

        void
        _set_parent_chain ();

#ifndef XSDE_EXCEPTIONS
        const serializer_base*
        _ultimate_impl () const;
#endif
#endif
      };
    }
  }
}

#include <xsde/cxx/serializer/elements.ixx>

#endif  // XSDE_CXX_SERIALIZER_ELEMENTS_HXX
