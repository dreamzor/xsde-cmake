// file      : xsde/cxx/parser/state.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_PARSER_STATE_HXX
#define XSDE_CXX_PARSER_STATE_HXX

#include <xsde/cxx/config.hxx>

#include <xsde/cxx/stack.hxx>
#include <xsde/cxx/parser/elements.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      // Optimized state stack for non-recursive case (one element).
      //
      struct parser_stack
      {
        parser_stack (parser_state& first);

#ifdef XSDE_EXCEPTIONS
        void
#else
        stack::error
#endif
        push (parser_state&);

        void
        pop ();

        parser_state&
        top ();

        void
        clear ();

      private:
        stack stack_;
      };
    }
  }
}


#include <xsde/cxx/parser/state.ixx>

#endif  // XSDE_CXX_PARSER_STATE_HXX
