// file      : xsde/cxx/parser/state.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      // parser_stack
      //
      inline parser_stack::
      parser_stack (parser_state& first)
          : stack_ (sizeof (parser_state), &first)
      {
      }

#ifdef XSDE_EXCEPTIONS
      inline void parser_stack::
#else
      inline stack::error parser_stack::
#endif
      push (parser_state& s)
      {
#ifdef XSDE_EXCEPTIONS
        stack_.push ();
#else
        if (stack::error e = stack_.push ())
          return e;
#endif

        *static_cast<parser_state*> (stack_.top ()) = s;

#ifndef XSDE_EXCEPTIONS
        return stack::error_none;
#endif
      }

      inline void parser_stack::
      pop ()
      {
        stack_.pop ();
      }

      inline parser_state& parser_stack::
      top ()
      {
        return *static_cast<parser_state*> (stack_.top ());
      }

      inline void parser_stack::
      clear ()
      {
        stack_.clear ();
      }
    }
  }
}
