// file      : xsde/cxx/parser/elements.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_ELEMENTS_HXX
#define XSDE_CXX_PARSER_ELEMENTS_HXX

#include <xsde/cxx/config.hxx>
#include <xsde/cxx/ro-string.hxx>

#ifdef XSDE_PARSER_VALIDATION
#  include <xsde/cxx/schema-error.hxx>
#endif

#ifndef XSDE_EXCEPTIONS
#  include <xsde/cxx/sys-error.hxx>
#  include <xsde/cxx/parser/error.hxx>
#endif

#include <xsde/cxx/parser/context.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      // pre() and post() are overridable pre/post callbacks, i.e., the
      // derived parser can override them without calling the base version.
      // _pre() and _post() are not overridable pre/post callbacks in the
      // sense that the derived parser may override them but has to call
      // the base version. The call sequence is as shown below:
      //
      // pre ()
      // _pre ()
      // _post ()
      // post ()
      //
      struct parser_base
      {
        virtual
        ~parser_base ();

        parser_base ();

#ifdef XSDE_REUSE_STYLE_TIEIN
        parser_base (parser_base* impl, void*);
#endif

      public:
        virtual void
        pre ();

        virtual void
        _pre ();

        // The type argument is a type name and namespace from the
        // xsi:type attribute in the form "<name> <namespace>" with
        // the space and namespace part absent if the type does not
        // have a namespace or 0 if xsi:type is not present.
        //
#ifdef XSDE_POLYMORPHIC
        virtual void
        _start_element (const ro_string& ns,
                        const ro_string& name,
                        const char* type) = 0;
#else
        virtual void
        _start_element (const ro_string& ns,
                        const ro_string& name) = 0;
#endif

        virtual void
        _end_element (const ro_string& ns,
                      const ro_string& name) = 0;

        virtual void
        _attribute (const ro_string& ns,
                    const ro_string& name,
                    const ro_string& value) = 0;

        virtual void
        _characters (const ro_string&) = 0;

        virtual void
        _post ();

        // The post() signature varies depending on the parser return
        // type.
        //

      public:
        // The following functions are called when wildcard content is
        // encountered. Override them to handle mixed content models,
        // any/anyAttribute, and anyType/anySimpleType. By default
        // these functions do nothing.
        //
#ifdef XSDE_POLYMORPHIC
        virtual void
        _start_any_element (const ro_string& ns,
                            const ro_string& name,
                            const char* type);
#else
        virtual void
        _start_any_element (const ro_string& ns,
                            const ro_string& name);
#endif

        virtual void
        _end_any_element (const ro_string& ns,
                          const ro_string& name);

        virtual void
        _any_attribute (const ro_string& ns,
                        const ro_string& name,
                        const ro_string& value);

        virtual void
        _any_characters (const ro_string&);

      public:
        // Implementation callbacks for _pre and _post. The _pre and _post
        // callbacks should never be called directly. Instead, the *_impl
        // versions should be used. By default _pre_impl and _post_impl
        // simply call _pre and _post respectively.
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

        // Reset the parser state after an error.
        //
        virtual void
        _reset ();

        // Error handling via codes. If the error is set while parser
        // is in the context, the error is set in the context, instead
        // of the parser. Since pre() and post() calls are not in
        // context, the parser stores application and system errors
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
#ifdef XSDE_PARSER_VALIDATION
      public:
        void
        _schema_error (context::schema_error_t);
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

      private:
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

#ifdef XSDE_REUSE_STYLE_TIEIN
      protected:
        parser_base* parent_;
        parser_base* impl_;

        void
        _set_parent_chain ();

#ifndef XSDE_EXCEPTIONS
        const parser_base*
        _ultimate_impl () const;
#endif
#endif

      protected:
        parser_state previous_;
      };
    }
  }
}

#include <xsde/cxx/parser/elements.ixx>

#endif  // XSDE_CXX_PARSER_ELEMENTS_HXX
