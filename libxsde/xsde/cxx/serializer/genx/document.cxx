// file      : xsde/cxx/serializer/genx/document.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/config.hxx>

#include <string.h> // strlen, strcmp

#ifdef XSDE_EXCEPTIONS
#  include <new> // std::bad_alloc
#endif

#ifdef XSDE_IOSTREAM
#  include <iostream>
#endif

#ifdef XSDE_EXCEPTIONS
#  include <xsde/cxx/serializer/exceptions.hxx>
#else
#  include <xsde/cxx/serializer/error.hxx>
#endif

#include <xsde/cxx/serializer/context.hxx>

#ifdef XSDE_POLYMORPHIC
#  include <xsde/cxx/serializer/substitution-map.hxx>
#endif

#include <xsde/cxx/serializer/genx/document.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace genx
      {
#ifdef XSDE_POLYMORPHIC
        static substitution_map_init substitution_map_init_;
#endif

        // writer
        //
        writer::
        ~writer ()
        {
        }

#ifdef XSDE_EXCEPTIONS
        void writer::
        write (const char* s)
        {
          write (s, strlen (s));
        }
#else
        bool writer::
        write (const char* s)
        {
          return write (s, strlen (s));
        }
#endif

        // document_simpl
        //
        const document_simpl::flags document_simpl::pretty_print = 0x01;

	document_simpl::
	~document_simpl ()
	{
	  // Prevents auto-generation of this dtor.
        }

        document_simpl::
#ifdef XSDE_POLYMORPHIC
        document_simpl (serializer_base& serializer,
                        const char* name,
                        bool,
                        const char* st)
#else
        document_simpl (serializer_base& serializer, const char* name)
#endif
            : serializer_ (serializer)
        {
#ifdef XSDE_POLYMORPHIC
          root_static_type_ = st;
#endif
          init_root_name (0, name);
        }

        document_simpl::
#ifdef XSDE_POLYMORPHIC
        document_simpl (serializer_base& serializer,
                        const char* ns,
                        const char* name,
                        bool,
                        const char* st)
#else
        document_simpl (serializer_base& serializer,
                        const char* ns,
                        const char* name)
#endif
            : serializer_ (serializer)
        {
#ifdef XSDE_POLYMORPHIC
          root_static_type_ = st;
#endif
          init_root_name (ns, name);
        }

#ifdef XSDE_STL
        document_simpl::
#ifdef XSDE_POLYMORPHIC
        document_simpl (serializer_base& serializer,
                        const std::string& name,
                        bool,
                        const char* st)
#else
        document_simpl (serializer_base& serializer, const std::string& name)
#endif
            : serializer_ (serializer)
        {
#ifdef XSDE_POLYMORPHIC
          root_static_type_ = st;
#endif
          init_root_name (0, name.c_str ());
        }

        document_simpl::
#ifdef XSDE_POLYMORPHIC
        document_simpl (serializer_base& serializer,
                        const std::string& ns,
                        const std::string& name,
                        bool,
                        const char* st)
#else
        document_simpl (serializer_base& serializer,
                        const std::string& ns,
                        const std::string& name)
#endif
            : serializer_ (serializer)
        {
#ifdef XSDE_POLYMORPHIC
          root_static_type_ = st;
#endif
          init_root_name (ns.c_str (), name.c_str ());
        }
#endif // XSDE_STL


        void document_simpl::
        init_root_name (const char* ns, const char* name)
        {
          // Leave root_ns_ uninitialized if ns is not specified.
          //
          if (ns != 0 && *ns != '\0')
          {
#ifdef XSDE_EXCEPTIONS
            root_ns_.assign (ns);
#else
            if (root_ns_.assign (ns))
            {
              error_ = error (sys_error::no_memory);
              return;
            }
#endif
          }

#ifdef XSDE_EXCEPTIONS
          root_name_.assign (name);
#else
          if (root_name_.assign (name))
            error_ = error (sys_error::no_memory);
#endif
        }

        void document_simpl::
        add_prefix (const char* p, const char* ns)
        {
#if defined (XSDE_STL)
          prefixes_.push_back (p);
          prefix_namespaces_.push_back (ns);
#else
#if defined (XSDE_EXCEPTIONS)
          prefixes_.push_back_copy (p);
          prefix_namespaces_.push_back_copy (ns);
#else
          if (prefixes_.push_back_copy (p) ||
              prefix_namespaces_.push_back_copy (ns))
            error_ = error (sys_error::no_memory);
#endif
#endif
        }

        void document_simpl::
        add_default_prefix (const char* ns)
        {
#if defined (XSDE_STL)
          prefixes_.push_back ("");
          prefix_namespaces_.push_back (ns);
#else
#if defined (XSDE_EXCEPTIONS)
          prefixes_.push_back_copy ("");
          prefix_namespaces_.push_back_copy (ns);
#else
          if (prefixes_.push_back_copy ("") ||
              prefix_namespaces_.push_back_copy (ns))
            error_ = error (sys_error::no_memory);
#endif
#endif
        }

        void document_simpl::
        add_schema (const char* ns, const char* l)
        {
#if defined (XSDE_STL)
          schemas_.push_back (l);
          schema_namespaces_.push_back (ns);
#else
#if defined (XSDE_EXCEPTIONS)
          schemas_.push_back_copy (l);
          schema_namespaces_.push_back_copy (ns);
#else
          if (schemas_.push_back_copy (l) ||
              schema_namespaces_.push_back_copy (ns))
            error_ = error (sys_error::no_memory);
#endif
#endif
        }

        void document_simpl::
        add_no_namespace_schema (const char* l)
        {
#if defined (XSDE_STL)
          schemas_.push_back (l);
          schema_namespaces_.push_back ("");
#else
#if defined (XSDE_EXCEPTIONS)
          schemas_.push_back_copy (l);
          schema_namespaces_.push_back_copy ("");
#else
          if (schemas_.push_back_copy (l) ||
              schema_namespaces_.push_back_copy (""))
            error_ = error (sys_error::no_memory);
#endif
#endif
        }

        //
        //
        void document_simpl::
        reset ()
        {
#ifndef XSDE_EXCEPTIONS
          error_ = error ();
#endif
          if (xml_serializer_)
            genxReset (xml_serializer_);

          serializer_._reset ();
        }

        // istream
        //
#ifdef XSDE_IOSTREAM

#ifdef XSDE_EXCEPTIONS
        static void
        ostream_write (void* p, const char* s, size_t n)
        {
          std::ostream* os = reinterpret_cast<std::ostream*> (p);
          os->write (s, static_cast<std::streamsize> (n));

          if (os->bad ())
            throw std::ios_base::failure ("write failed");
        }

        static void
        ostream_flush (void* p)
        {
          std::ostream* os = reinterpret_cast<std::ostream*> (p);
          os->flush ();

          if (os->bad ())
            throw std::ios_base::failure ("flush failed");
        }
#else
        static bool
        ostream_write (void* p, const char* s, size_t n)
        {
          std::ostream* os = reinterpret_cast<std::ostream*> (p);
          os->write (s, static_cast<std::streamsize> (n));
          return !os->bad ();
        }

        static bool
        ostream_flush (void* p)
        {
          std::ostream* os = reinterpret_cast<std::ostream*> (p);
          os->flush ();
          return !os->bad ();
        }
#endif

        void document_simpl::
        serialize (std::ostream& os, flags f)
        {
          serialize (&ostream_write, &ostream_flush, &os, f);
        }
#endif // XSDE_IOSTREAM

        //
        //
#ifdef XSDE_EXCEPTIONS
        static void
        write_thunk (void* p, const char* s)
        {
          reinterpret_cast<writer*> (p)->write (s);
        }

        static void
        write_bound_thunk (void* p, const char* s, size_t n)
        {
          reinterpret_cast<writer*> (p)->write (s, n);
        }

        static void
        flush_thunk (void* p)
        {
          reinterpret_cast<writer*> (p)->flush ();
        }
#else
        static bool
        write_thunk (void* p, const char* s)
        {
          return reinterpret_cast<writer*> (p)->write (s);
        }

        static bool
        write_bound_thunk (void* p, const char* s, size_t n)
        {
          return reinterpret_cast<writer*> (p)->write (s, n);
        }

        static bool
        flush_thunk (void* p)
        {
          return reinterpret_cast<writer*> (p)->flush ();
        }
#endif

        void document_simpl::
        serialize (writer& w, flags f)
        {
          serialize (&write_thunk, &write_bound_thunk, &flush_thunk, &w, f);
        }

        // Genx write functions.
        //
        struct writer_info
        {
          void* user_data;
          document_simpl::write_func write;
          document_simpl::write_bound_func write_bound;
          document_simpl::flush_func flush;
        };

        extern "C" genxStatus
        genx_write (void* p, constUtf8 us)
        {
          const char* s = reinterpret_cast<const char*> (us);
          writer_info* wi = reinterpret_cast<writer_info*> (p);

          if (wi->write != 0)
          {
#ifdef XSDE_EXCEPTIONS
            wi->write (wi->user_data, s);
#else
            if (!wi->write (wi->user_data, s))
              return GENX_IO_ERROR;
#endif
          }
          else
          {
#ifdef XSDE_EXCEPTIONS
            wi->write_bound (wi->user_data, s, strlen (s));
#else
            if (!wi->write_bound (wi->user_data, s, strlen (s)))
              return GENX_IO_ERROR;
#endif
          }

          return GENX_SUCCESS;
        }

        extern "C" genxStatus
        genx_write_bound (void* p, constUtf8 start, constUtf8 end)
        {
          size_t size = static_cast<size_t> (end - start);
          const char* s = reinterpret_cast<const char*> (start);
          writer_info* wi = reinterpret_cast<writer_info*> (p);

#ifdef XSDE_EXCEPTIONS
          wi->write_bound (wi->user_data, s, size);
#else
          if (!wi->write_bound (wi->user_data, s, size))
            return GENX_IO_ERROR;
#endif

          return GENX_SUCCESS;
        }

        extern "C" genxStatus
        genx_flush (void* p)
        {
          writer_info* wi = reinterpret_cast<writer_info*> (p);

#ifdef XSDE_EXCEPTIONS
          wi->flush (wi->user_data);
#else
          if (!wi->flush (wi->user_data))
            return GENX_IO_ERROR;
#endif

          return GENX_SUCCESS;
        }

        void document_simpl::
        serialize (write_func wf, write_bound_func wbf, flush_func ff,
                   void* user_data, flags f)
        {
          if (xml_serializer_ == 0)
          {
            xml_serializer_ = genxNew (0, 0, 0);

            if (xml_serializer_ == 0)
            {
#ifdef XSDE_EXCEPTIONS
              throw std::bad_alloc ();
#else
              error_ = error (sys_error::no_memory);
              return;
#endif
            }
          }

          writer_info wi;
          wi.user_data = user_data;
          wi.write = wf;
          wi.write_bound = wbf;
          wi.flush = ff;

          genxSetUserData (xml_serializer_, &wi);

          if (f & pretty_print)
            genxSetPrettyPrint (xml_serializer_, 2);

          genxSender sender;
          sender.send = &genx_write;
          sender.sendBounded = &genx_write_bound;
          sender.flush = &genx_flush;

          genxStatus e = genxStartDocSender (xml_serializer_, &sender);

          if (e != GENX_SUCCESS)
          {
            filter_xml_error (e);
            return;
          }

          serialize (xml_serializer_);

#ifndef XSDE_EXCEPTIONS
          if (error_)
            return;
#endif

          e = genxEndDocument (xml_serializer_);

          if (e != GENX_SUCCESS)
            filter_xml_error (e);
        }

        //
        //
        static const char xsi[] = "http://www.w3.org/2001/XMLSchema-instance";

        void document_simpl::
        serialize (genxWriter s)
        {
          context ctx (s);

#ifndef XSDE_POLYMORPHIC

#ifdef XSDE_EXCEPTIONS
          ctx.start_element (root_ns_.data (), root_name_.data ());
#else
          if (!ctx.start_element (root_ns_.data (), root_name_.data ()))
          {
            error_ = error (ctx.xml_error ());
            return;
          }
#endif
#else // XSDE_POLYMORPHIC
          const char* ns = root_ns_.data ();
          const char* n = root_name_.data ();
          const char* dt = 0;

          if (root_static_type_ != 0)
          {
            dt = serializer_._dynamic_type ();

            // Call to check sets ns and n if successful.
            //
            if (strcmp (dt, root_static_type_) == 0 ||
                substitution_map_instance ().check (ns, n, dt, 0))
              dt = 0;
          }

#ifdef XSDE_EXCEPTIONS
          ctx.start_element (ns, n);
#else
          if (!ctx.start_element (ns, n))
          {
            error_ = error (ctx.xml_error ());
            return;
          }
#endif
#endif // XSDE_POLYMORPHIC

          // Add namespace prefixes.
          //
          for (size_t i = 0; i < prefixes_.size (); ++i)
          {
#ifdef XSDE_STL
            const char* p = prefixes_[i].c_str ();
            const char* ns = prefix_namespaces_[i].c_str ();
#else
            const char* p = prefixes_[i];
            const char* ns = prefix_namespaces_[i];
#endif

#ifdef XSDE_EXCEPTIONS
            ctx.declare_namespace (ns, p);
#else
            if (!ctx.declare_namespace (ns, p))
              break;
#endif
          }

#ifndef XSDE_EXCEPTIONS
          if (ctx.error_type ())
          {
            error_ = error (ctx.xml_error ());
            return;
          }
#endif

          // Add the schema location attributes.
          //
          if (schemas_.size () != 0)
          {
#ifdef XSDE_EXCEPTIONS
            ctx.declare_namespace (xsi, "xsi");
#else
            if (!ctx.declare_namespace (xsi, "xsi"))
            {
              error_ = error (ctx.xml_error ());
              return;
            }
#endif
            // First add the xsi:schemaLocation attribute.
            //
            bool start = false;

            for (size_t j = 0; j < schemas_.size (); ++j)
            {
#ifdef XSDE_STL
              const char* l = schemas_[j].c_str ();
              const char* ns = schema_namespaces_[j].c_str ();
#else
              const char* l = schemas_[j];
              const char* ns = schema_namespaces_[j];
#endif
              if (ns[0] != '\0')
              {
                if (!start)
                {
#ifdef XSDE_EXCEPTIONS
                  ctx.start_attribute (xsi, "schemaLocation");
#else
                  if (!ctx.start_attribute (xsi, "schemaLocation"))
                    break;
#endif
                  start = true;
                }
                else
                {
#ifdef XSDE_EXCEPTIONS
                  ctx.characters (" ", 1);
#else
                  if (!ctx.characters (" ", 1))
                    break;
#endif
                }

#ifdef XSDE_EXCEPTIONS
                ctx.characters (ns);
                ctx.characters (" ", 1);
                ctx.characters (l);
#else
                if (!ctx.characters (ns) ||
                    !ctx.characters (" ", 1) ||
                    !ctx.characters (l))
                  break;
#endif
              }
            }

#ifndef XSDE_EXCEPTIONS
            if (ctx.error_type ())
            {
              error_ = error (ctx.xml_error ());
              return;
            }
#endif

            if (start)
            {
#ifdef XSDE_EXCEPTIONS
              ctx.end_attribute ();
#else
              if (!ctx.end_attribute ())
              {
                error_ = error (ctx.xml_error ());
                return;
              }
#endif
            }

            // Now add the xsi:noNamespaceSchemaLocation attribute.
            //
            start = false;

            for (size_t k = 0; k < schemas_.size (); ++k)
            {
#ifdef XSDE_STL
              const char* l = schemas_[k].c_str ();
              const char* ns = schema_namespaces_[k].c_str ();
#else
              const char* l = schemas_[k];
              const char* ns = schema_namespaces_[k];
#endif
              if (ns[0] == '\0')
              {
                if (!start)
                {
#ifdef XSDE_EXCEPTIONS
                  ctx.start_attribute (xsi, "noNamespaceSchemaLocation");
#else
                  if (!ctx.start_attribute (xsi, "noNamespaceSchemaLocation"))
                    break;
#endif
                  start = true;
                }
                else
                {
#ifdef XSDE_EXCEPTIONS
                  ctx.characters (" ", 1);
#else
                  if (!ctx.characters (" ", 1))
                    break;
#endif
                }

#ifdef XSDE_EXCEPTIONS
                ctx.characters (l);
#else
                if (!ctx.characters (l))
                  break;
#endif
              }
            }

#ifndef XSDE_EXCEPTIONS
            if (ctx.error_type ())
            {
              error_ = error (ctx.xml_error ());
              return;
            }
#endif

            if (start)
            {
#ifdef XSDE_EXCEPTIONS
              ctx.end_attribute ();
#else
              if (!ctx.end_attribute ())
              {
                error_ = error (ctx.xml_error ());
                return;
              }
#endif
            }
          }

          // Call the root type serializer to serialize the content.
          //

#if !defined (XSDE_SERIALIZER_VALIDATION) && defined (XSDE_EXCEPTIONS)

#ifdef XSDE_POLYMORPHIC
          // Set xsi:type if necessary.
          //
          if (dt != 0)
            ctx.set_type (dt);
#endif
          serializer_._pre_impl (ctx);
          serializer_._serialize_attributes ();
          serializer_._serialize_content ();
          serializer_._post_impl ();

#else // !defined (XSDE_SERIALIZER_VALIDATION) && defined (XSDE_EXCEPTIONS)

#ifdef XSDE_POLYMORPHIC
          // Set xsi:type if necessary.
          //
          if (dt != 0)
            ctx.set_type (dt);

#ifndef XSDE_EXCEPTIONS
          if (!ctx.error_type ())
#endif
#endif // XSDE_POLYMORPHIC

            serializer_._pre_impl (ctx);

          if (!ctx.error_type ())
            serializer_._serialize_attributes ();

          if (!ctx.error_type ())
            serializer_._serialize_content ();

          if (!ctx.error_type ())
            serializer_._post_impl ();

          if (context::error_type_t et = ctx.error_type ())
          {
            switch (et)
            {
#ifndef XSDE_EXCEPTIONS
            case context::error_app:
              {
                error_ = error (ctx.app_error ());
                break;
              }
#endif
#ifdef XSDE_SERIALIZER_VALIDATION
            case context::error_schema:
              {
#ifdef XSDE_EXCEPTIONS
                throw schema (ctx.schema_error ());
#else
                error_ = error (ctx.schema_error ());
                break;
#endif
              }
#endif
#ifndef XSDE_EXCEPTIONS
            case context::error_xml:
              {
                filter_xml_error (ctx.xml_error ());
                break;
              }
            case context::error_sys:
              {
                error_ = error (ctx.sys_error ());
                break;
              }
#endif
            default:
              break;
            }
            return;
          }
#endif // !XSDE_SERIALIZER_VALIDATION && XSDE_EXCEPTIONS


#ifdef XSDE_EXCEPTIONS
          ctx.end_element ();
#else
          if (!ctx.end_element ())
          {
            error_ = error (ctx.xml_error ());
            return;
          }
#endif
        }

        void document_simpl::
        filter_xml_error (genxStatus e)
        {
          switch (e)
          {
          case GENX_ALLOC_FAILED:
            {
#ifdef XSDE_EXCEPTIONS
              throw std::bad_alloc ();
#else
              error_ = error (sys_error::no_memory);
              break;
#endif
            }
          case GENX_IO_ERROR:
            {
#ifdef XSDE_EXCEPTIONS
              // This should never happen with consistent exception
              // handling usage since the write/flush functions
              // throw exceptions to indicate write failures.
              //
              throw xml (e);
#else
              error_ = error (sys_error::write_failed);
              break;
#endif
            }
          default:
            {
#ifdef XSDE_EXCEPTIONS
              throw xml (e);
#else
              error_ = error (e);
              break;
#endif
            }
          }
        }
      }
    }
  }
}
