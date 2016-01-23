// file      : xsde/cxx/parser/validating/parser.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace validating
      {

        // empty_content
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline empty_content::
        empty_content ()
        {
        }

        inline empty_content::
        empty_content (empty_content* impl, void*)
            : parser_base (impl, 0)
        {
        }
#endif

        // simple_content
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline simple_content::
        simple_content ()
        {
        }

        inline simple_content::
        simple_content (simple_content* impl, void*)
            : empty_content (impl, 0)
        {
        }
#endif

        // complex_content
        //
        inline complex_content::
        complex_content ()
            : depth_ (0), parser_stack_ (previous_)
        {
        }

#ifdef XSDE_REUSE_STYLE_TIEIN
        inline complex_content::
        complex_content (complex_content* impl, void*)
            : empty_content (impl, 0), depth_ (0), parser_stack_ (previous_)
        {
        }
#endif

        // all_stack
        //

        inline all_stack::
        all_stack (size_t n, unsigned char* first)
            : stack_ (n, first)
        {
        }

#ifdef XSDE_EXCEPTIONS
        inline void all_stack::
#else
        inline stack::error all_stack::
#endif
        push ()
        {
#ifdef XSDE_EXCEPTIONS
          stack_.push ();
#else
          if (stack::error e = stack_.push ())
            return e;
#endif
          unsigned char* p = static_cast<unsigned char*> (stack_.top ());

          for (size_t i = 0; i < stack_.element_size (); ++i)
            p[i] = 0;

#ifndef XSDE_EXCEPTIONS
          return stack::error_none;
#endif
        }

        inline void all_stack::
        pop ()
        {
          stack_.pop ();
        }

        inline unsigned char* all_stack::
        top ()
        {
          return static_cast<unsigned char*> (stack_.top ());
        }

        inline void all_stack::
        clear ()
        {
          stack_.clear ();
        }


        // list_base
        //
#ifdef XSDE_REUSE_STYLE_TIEIN
        inline list_base::
        list_base ()
        {
        }

        inline list_base::
        list_base (list_base* impl, void*)
            : simple_content (impl, 0)
        {
        }
#endif
      }
    }
  }
}
