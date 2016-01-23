// file      : xsde/cxx/serializer/validating/inheritance-map.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/config.hxx>

#include <string.h> // strcmp

#ifndef XSDE_EXCEPTIONS
#  include <assert.h> // assert
#  include <stdlib.h> // exit
#endif

#ifdef XSDE_CUSTOM_ALLOCATOR
#  include <xsde/cxx/allocator.hxx>
#endif

#include <xsde/cxx/serializer/validating/inheritance-map.hxx>
#include <xsde/cxx/serializer/validating/inheritance-map-load.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace validating
      {
        inheritance_map* inheritance_map_init::map = 0;
        size_t inheritance_map_init::count = 0;

        bool inheritance_map::
        check (const char* derived, const char* base) const
        {
          if (strcmp (derived, base) == 0)
            return true;

          const void* p = find (derived);

          if (p)
          {
            const char* b = *static_cast<const char* const*> (p);
            return strcmp (base, b) == 0 ? true : check (b, base);
          }

          return false;
        }

        // inheritance_map_init
        //
        inheritance_map_init::
        inheritance_map_init ()
        {
          if (count == 0)
          {
#ifndef XSDE_CUSTOM_ALLOCATOR
            map = new inheritance_map (XSDE_SERIALIZER_IMAP_BUCKETS);
#else
            map = static_cast<inheritance_map*> (
              alloc (sizeof (inheritance_map)));

#ifdef XSDE_EXCEPTIONS
            alloc_guard mg (map);
            new (map) inheritance_map (XSDE_SERIALIZER_IMAP_BUCKETS);
            mg.release ();
#else
            if (map)
              new (map) inheritance_map (XSDE_SERIALIZER_IMAP_BUCKETS);
#endif
#endif

#ifndef XSDE_EXCEPTIONS
            if (map == 0 || map->_error () != inheritance_map::error_none)
            {
              // This is static initialization so there is nothing we can do.
              // The best thing is to fail fast. abort() would have probably
              // been the better choice here but it is not available on some
              // platforms (notably, WinCE).
              //
              assert (false);
              exit (1);
            }
#endif
          }

          ++count;
        }

        inheritance_map_init::
        ~inheritance_map_init ()
        {
          if (--count == 0)
          {
#ifndef XSDE_CUSTOM_ALLOCATOR
            delete map;
#else
            map->~inheritance_map ();
            cxx::free (map);
#endif
          }
        }

        // inheritance_map_entry
        //
        inheritance_map_entry::
        inheritance_map_entry (const char* derived, const char* base)
        {
          inheritance_map& m = inheritance_map_instance ();
          m.insert (derived, base);

#ifndef XSDE_EXCEPTIONS
          if (m._error () != inheritance_map::error_none)
          {
            // This is static initialization so there is nothing we can do.
            // The best thing is to fail fast. abort() would have probably
            // been the better choice here but it is not available on some
            // platforms (notably, WinCE).
            //
            assert (false);
            exit (1);
          }
#endif
        }

        //
        //
        size_t
        serializer_imap_elements ()
        {
          return inheritance_map_instance ().size ();
        }
      }
    }
  }
}
