// file      : xsde/cxx/serializer/genx/document.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_SERIALIZER_GENX_DOCUMENT_HXX
#define XSDE_CXX_SERIALIZER_GENX_DOCUMENT_HXX

#include <xsde/cxx/config.hxx>

#include <stddef.h> // size_t

#include <xsde/c/genx/genx.h>

#ifdef XSDE_IOSTREAM
#  include <iosfwd>
#endif

#include <xsde/cxx/string.hxx>

#ifdef XSDE_STL
#  include <xsde/cxx/string-sequence-stl.hxx>
#else
#  include <xsde/cxx/string-sequence.hxx>
#endif

#include <xsde/cxx/serializer/elements.hxx>

#ifndef XSDE_EXCEPTIONS
#  include <xsde/cxx/serializer/error.hxx>
#endif

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace genx
      {
        // Simple auto pointer for genxWriter object.
        //
        struct serializer_auto_ptr
        {
          ~serializer_auto_ptr ();

          explicit
          serializer_auto_ptr (genxWriter = 0);

          serializer_auto_ptr&
          operator= (genxWriter);

        public:
          operator genxWriter ()
          {
            return serializer_;
          }

        private:
          serializer_auto_ptr (const serializer_auto_ptr&);

          serializer_auto_ptr&
          operator= (const serializer_auto_ptr&);

        private:
          genxWriter serializer_;
        };

        // Writer interface.
        //
        struct writer
        {
          virtual
          ~writer ();

          // The first write function is called to write a '\0'-terminated
          // string. Its default implementation calls the second versions:
          // write (s, strlen (s)). If exceptions are enabled, throw to
          // indicate a write failure. Otherwise return true if write was
          // successful, false otherwise.
          //
#ifdef XSDE_EXCEPTIONS
          virtual void
          write (const char* s);

          virtual void
          write (const char* s, size_t n) = 0;

          virtual void
          flush () = 0;
#else
          virtual bool
          write (const char* s);

          virtual bool
          write (const char* s, size_t n) = 0;

          virtual bool
          flush () = 0;
#endif
        };

        //
        //
        class document_simpl
        {
        public:
	  virtual
          ~document_simpl ();

#ifdef XSDE_POLYMORPHIC
          // Note that the static_type string is not deep-copied.
          //
          document_simpl (serializer_base&,
                          const char* root_element_name,
                          bool polymorphic = false,
                          const char* root_static_type = 0);

          document_simpl (serializer_base&,
                          const char* root_element_namespace,
                          const char* root_element_name,
                          bool polymorphic = false,
                          const char* root_static_type = 0);

#ifdef XSDE_STL
          document_simpl (serializer_base&,
                          const std::string& root_element_name,
                          bool polymorphic = false,
                          const char* root_static_type = 0);

          document_simpl (serializer_base&,
                          const std::string& root_element_namespace,
                          const std::string& root_element_name,
                          bool polymorphic = false,
                          const char* root_static_type = 0);
#endif

#else // XSDE_POLYMORPHIC

          document_simpl (serializer_base&,
                          const char* root_element_name);

          document_simpl (serializer_base&,
                          const char* root_element_namespace,
                          const char* root_element_name);

#ifdef XSDE_STL
          document_simpl (serializer_base&,
                          const std::string& root_element_name);

          document_simpl (serializer_base&,
                          const std::string& root_element_namespace,
                          const std::string& root_element_name);
#endif
#endif // XSDE_POLYMORPHIC

        public:
          // Namespace and schema location.
          //
          void
          add_prefix (const char* prefix, const char* namespace_);

          void
          add_default_prefix (const char* namespace_);

          void
          add_schema (const char* namespace_, const char* location);

          void
          add_no_namespace_schema (const char* location);

#ifdef XSDE_STL
          void
          add_prefix (const std::string& prefix,
                      const std::string& namespace_);

          void
          add_default_prefix (const std::string& namespace_);

          void
          add_schema (const std::string& namespace_,
                      const std::string& location);

          void
          add_no_namespace_schema (const std::string& location);
#endif

        public:
          void
          reset ();

        public:
          // Serialization flags.
          //
          typedef unsigned short flags;

          static const flags pretty_print;

#ifdef XSDE_IOSTREAM
        public:
          // Serialize to std::ostream. The std::ios_base::failure
          // exception is used to report io errors (badbit and failbit)
          // if XSDE_EXCEPTIONS is defined. Otherwise error codes are
          // used.
          //
          void
          serialize (std::ostream&, flags = 0);
#endif

        public:
          // Serialize by calling writer::write() and writer::flush() to
          // output XML.
          //
          void
          serialize (writer&, flags = 0);

          // Serialize by calling the write and flush functions. If the
          // unbounded write function is not provided, the bounded version
          // is called: write_bound_func (s, strlen (s)). user_data is
          // passed as a first argument to these functions. If exceptions
          // are enabled, throw to indicate a write failure. Otherwise return
          // true if write was successful, false otherwise.
          //

#ifdef XSDE_EXCEPTIONS
          typedef void (*write_func) (void*, const char*);
          typedef void (*write_bound_func) (void*, const char*, size_t);
          typedef void (*flush_func) (void*);
#else
          typedef bool (*write_func) (void*, const char*);
          typedef bool (*write_bound_func) (void*, const char*, size_t);
          typedef bool (*flush_func) (void*);
#endif

          void
          serialize (write_bound_func,
                     flush_func,
                     void* user_data,
                     flags = 0);

          void
          serialize (write_func,
                     write_bound_func,
                     flush_func,
                     void* user_data,
                     flags = 0);

        public:
          // Low-level, genx-specific serialization. With this method
          // it is your responsibility to call genxStartDoc*() and
          // genxEndDocument().
          //
          void
          serialize (genxWriter);

#ifndef XSDE_EXCEPTIONS
        public:
          const error&
          _error () const;
#endif

        protected:
          void
          filter_xml_error (genxStatus);

        protected:
          serializer_auto_ptr xml_serializer_;
          serializer_base& serializer_;

          string root_name_;
          string root_ns_;

#ifdef XSDE_POLYMORPHIC
          const char* root_static_type_;
#endif

          string_sequence prefixes_;
          string_sequence prefix_namespaces_;

          string_sequence schemas_;
          string_sequence schema_namespaces_;

#ifndef XSDE_EXCEPTIONS
          error error_;
#endif

        private:
          void
          init_root_name (const char* ns, const char* name);
        };
      }
    }
  }
}

#include <xsde/cxx/serializer/genx/document.ixx>

#endif  // XSDE_CXX_SERIALIZER_GENX_DOCUMENT_HXX
