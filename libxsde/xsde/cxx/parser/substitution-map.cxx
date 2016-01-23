// file      : xsde/cxx/parser/substitution-map.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/config.hxx>

#include <string.h> // strlen, strcmp, strncmp, strchr

#ifndef XSDE_EXCEPTIONS
#  include <assert.h> // assert
#  include <stdlib.h> // exit
#endif

#ifdef XSDE_CUSTOM_ALLOCATOR
#  include <xsde/cxx/allocator.hxx>
#endif

#include <xsde/cxx/parser/substitution-map.hxx>
#include <xsde/cxx/parser/substitution-map-callback.hxx>
#include <xsde/cxx/parser/substitution-map-load.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      substitution_map* substitution_map_init::map = 0;
      size_t substitution_map_init::count = 0;

      bool substitution_map::
      check_ (const ro_string& ns,
              const ro_string& name,
              const char* root,
              const char** type) const
      {
        bool r = false;

        if (const value* v = find_ (ns, name))
        {
          if (strcmp (root, v->root_) == 0)
            r = true;
          else
            r = check_ (v->root_, root);

          if (r && type != 0 && *type == 0)
            *type = v->type_;
        }

        // Call the callback.
        //
        if (!r && callback_ != 0)
        {
          const char* t;
          const char* p = strchr (root, ' ');

          ro_string rname (p ? root : 0, p ? p - root : 0);
          ro_string rns (p ? p + 1 : root);

          r = callback_ (rns, rname, ns, name, t);

          if (r && type != 0 && *type == 0)
            *type = t;
        }

        return r;
      }

      bool substitution_map::
      check_ (const ro_string& ns,
              const ro_string& name,
              const char* root_ns,
              const char* root_name,
              const char** type) const
      {
        bool r = false;

        if (const value* v = find_ (ns, name))
        {
          if (root_ns == 0)
            r = strcmp (v->root_, root_name) == 0;
          else
          {
            size_t n = strlen (root_name);

            r = strncmp (v->root_, root_name, n) == 0 && v->root_[n] == ' ' &&
              strcmp (v->root_ + n + 1, root_ns) == 0;
          }

          if (!r)
            r = check_ (v->root_, root_ns, root_name);

          if (r && type != 0 && *type == 0)
            *type = v->type_;
        }

        // Call the callback.
        //
        if (!r && callback_ != 0)
        {
          const char* t;
          ro_string rns (root_ns);
          ro_string rname (root_name);

          r = callback_ (rns, rname, ns, name, t);

          if (r && type != 0 && *type == 0)
            *type = t;
        }

        return r;
      }

      bool substitution_map::
      check_ (const char* member, const char* root) const
      {
        const value* v = static_cast<const value*> (find (member));

        if (v == 0)
          return false;

        return strcmp (root, v->root_) == 0 ? true : check_ (v->root_, root);
      }

      bool substitution_map::
      check_ (const char* member,
              const char* root_ns,
              const char* root_name) const
      {
        const value* v = static_cast<const value*> (find (member));

        if (v == 0)
          return false;

        bool r;

        if (root_ns == 0)
          r = strcmp (v->root_, root_name) == 0;
        else
        {
          size_t n = strlen (root_name);

          r = strncmp (v->root_, root_name, n) == 0 && v->root_[n] == ' ' &&
            strcmp (v->root_ + n + 1, root_ns) == 0;
        }

        return r ? true : check_ (v->root_, root_ns, root_name);
      }

      const substitution_map::value* substitution_map::
      find_ (const ro_string& ns, const ro_string& name) const
      {
        bool q = !ns.empty ();
        size_t h = hash (name.data (), name.size ());

        if (q)
        {
          h = hash (h, " ", 1);
          h = hash (h, ns.data (), ns.size ());
        }

        const bucket* p = find (h);

        if (p == 0)
          return 0;

        // Search for the entry in the bucket.
        //
        const size_t el_size = sizeof (element) + sizeof (value);
        const char* b = reinterpret_cast<const char*> (p) + sizeof (bucket);
        const char* e = b + p->size_ * el_size;

        for (; b < e; b += el_size)
        {
          const element* e = reinterpret_cast<const element*> (b);

          if (e->hash_ == h)
          {
            if (!q)
            {
              if (strlen (e->key_) == name.size () &&
                  strncmp (e->key_, name.data (), name.size ()) == 0)
                break;
            }
            else
            {
              size_t n = name.size ();

              if (strncmp (e->key_, name.data (), n) == 0 &&
                  e->key_[n] == ' ' &&
                  strlen (e->key_ + n + 1) == ns.size () &&
                  strncmp (e->key_ + n + 1, ns.data (), ns.size ()) == 0)
                break;
            }
          }
        }

        if (b == e)
          return 0;

        return reinterpret_cast<const value*> (b + sizeof (element));
      }

      // substitution_map_init
      //
      substitution_map_init::
      substitution_map_init ()
      {
        if (count == 0)
        {
#ifndef XSDE_CUSTOM_ALLOCATOR
          map = new substitution_map (XSDE_PARSER_SMAP_BUCKETS);
#else
          map = static_cast<substitution_map*> (
            alloc (sizeof (substitution_map)));

#ifdef XSDE_EXCEPTIONS
          alloc_guard mg (map);
          new (map) substitution_map (XSDE_PARSER_SMAP_BUCKETS);
          mg.release ();
#else
          if (map)
            new (map) substitution_map (XSDE_PARSER_SMAP_BUCKETS);
#endif
#endif

#ifndef XSDE_EXCEPTIONS
          if (map == 0 || map->_error () != substitution_map::error_none)
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

      substitution_map_init::
      ~substitution_map_init ()
      {
        if (--count == 0)
        {
#ifndef XSDE_CUSTOM_ALLOCATOR
          delete map;
#else
          map->~substitution_map ();
          cxx::free (map);
#endif
        }
      }

      // substitution_map_entry
      //
      substitution_map_entry::
      substitution_map_entry (const char* member,
                              const char* root,
                              const char* type)
      {
        substitution_map& m = substitution_map_instance ();
        m.insert (member, root, type);

#ifndef XSDE_EXCEPTIONS
        if (m._error () != substitution_map::error_none)
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

      // Callback.
      //
      void
      parser_smap_callback (
        bool (*callback) (
          const ro_string& root_ns,
          const ro_string& root_name,
          const ro_string& member_ns,
          const ro_string& member_name,
          const char*& type))
      {
        substitution_map_instance ().callback (callback);
      }

      // Load.
      //
      size_t
      parser_smap_elements ()
      {
        return substitution_map_instance ().size ();
      }
    }
  }
}
