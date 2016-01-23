// file      : xsde/cxx/parser/map.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/parser/map.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      // parser_map
      //
      parser_map::
      ~parser_map ()
      {
      }

      // parser_map_impl
      //
      void parser_map_impl::
      reset () const
      {
        if (resetting_)
          return;

        bool& r = const_cast<bool&> (resetting_);
        r = true;

        for (hashmap::const_iterator i (map_.begin ()), e (map_.end ());
             i != e; ++i)
        {
          parser_base* p = *static_cast<parser_base* const*> (*i);
          p->_reset ();
        }

        r = false;
      }
    }
  }
}
