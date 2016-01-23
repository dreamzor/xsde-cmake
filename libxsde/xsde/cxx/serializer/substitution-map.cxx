// file      : xsde/cxx/serializer/substitution-map.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/config.hxx>

#include <string.h> // strlen, strcmp, strncmp

#ifndef XSDE_EXCEPTIONS
#  include <assert.h> // assert
#  include <stdlib.h> // exit
#endif

#ifdef XSDE_CUSTOM_ALLOCATOR
#  include <xsde/cxx/allocator.hxx>
#endif

#include <xsde/cxx/serializer/substitution-map.hxx>
#include <xsde/cxx/serializer/substitution-map-callback.hxx>
#include <xsde/cxx/serializer/substitution-map-load.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      substitution_map* substitution_map_init::map = 0;
      size_t substitution_map_init::count = 0;

      substitution_map::
      ~substitution_map ()
      {
        for (const_iterator i (begin ()), e (end ()); i != e; ++i)
        {
          hashmap* p = *static_cast<hashmap**> (const_cast<void*> (*i));
#ifndef XSDE_CUSTOM_ALLOCATOR
          delete p;
#else
          if (p)
            p->~hashmap ();
          cxx::free (p);
#endif
        }
      }

      void substitution_map::
      insert (const char* root,
              const char* member_ns,
              const char* member_name,
              const char* member_type)
      {
        hashmap* m;

        if (const void* p = find (root))
          m = *static_cast<hashmap**> (const_cast<void*> (p));
        else
        {
#ifndef XSDE_CUSTOM_ALLOCATOR
          m = new hashmap (XSDE_SERIALIZER_SMAP_BUCKET_BUCKETS,
                           sizeof (value));
#else
          m = static_cast<hashmap*> (alloc (sizeof (hashmap)));

#ifdef XSDE_EXCEPTIONS
          alloc_guard mg (m);
          new (m) hashmap (XSDE_SERIALIZER_SMAP_BUCKET_BUCKETS,
                           sizeof (value));
          mg.release ();
#else
          if (m)
            new (m) hashmap (XSDE_SERIALIZER_SMAP_BUCKET_BUCKETS,
                             sizeof (value));
#endif
#endif

#ifndef XSDE_EXCEPTIONS
          if (m == 0 || m->_error () != hashmap::error_none)
          {
            error_ = error_no_memory;
            return;
          }
#endif
          hashmap::insert (root, &m);

#ifndef XSDE_EXCEPTIONS
          if (_error () != error_none)
            return;
#endif
        }

        value v;
        v.ns_ = member_ns;
        v.name_ = member_name;
        m->insert (member_type, &v);

#ifndef XSDE_EXCEPTIONS
        if (m->_error () != hashmap::error_none)
          error_ = error_no_memory;
#endif
      }

      bool substitution_map::
      check_ (const char*& ns,
              const char*& name,
              const char* type,
              const void* obj,
              bool top) const
      {
        // Call the callback first to allow the user to provide a custom
        // substitution group mapping.
        //
        if (top && callback_ != 0)
        {
          if (callback_ (type, obj, ns, name))
            return true;
        }

        size_t h = hash (name);

        if (ns)
        {
          h = hash (h, " ", 1);
          h = hash (h, ns);
        }

        const bucket* p = find (h);

        if (p != 0)
        {
          // Search for the entry in the bucket.
          //
          const size_t el_size = sizeof (element) + sizeof (hashmap*);
          const char* b = reinterpret_cast<const char*> (p) + sizeof (bucket);
          const char* e = b + p->size_ * el_size;

          size_t nl = ns ? strlen (name) : 0;

          for (; b < e; b += el_size)
          {
            const element* e = reinterpret_cast<const element*> (b);

            if (e->hash_ == h)
            {
              if (ns == 0)
              {
                if (strcmp (e->key_, name) == 0)
                  break;
              }
              else
              {
                if (strncmp (e->key_, name, nl) == 0 &&
                    e->key_[nl] == ' ' &&
                    strcmp (e->key_ + nl + 1, ns) == 0)
                  break;
              }
            }
          }

          if (b != e)
          {
            const hashmap* map = *reinterpret_cast<const hashmap* const*> (
              b + sizeof (element));

            // See if we have a direct substitution.
            //
            if (const value* v = static_cast<const value*> (map->find (type)))
            {
              ns = v->ns_;
              name = v->name_;
              return true;
            }

            // Otherwise we have to iterate over possible substitutions and
            // see if any of them can in turn be substituted with something
            // that we can use.
            //
            for (const_iterator i (map->begin ()), end (map->end ());
                 i != end; ++i)
            {
              const value* v = static_cast<const value*> (*i);

              const char* tns = v->ns_;
              const char* tn = v->name_;

              if (check_ (tns, tn, type, obj, false))
              {
                ns = tns;
                name = tn;
                return true;
              }
            }
          }
        }

        return false;
      }

      // substitution_map_init
      //
      substitution_map_init::
      substitution_map_init ()
      {
        if (count == 0)
        {
#ifndef XSDE_CUSTOM_ALLOCATOR
          map = new substitution_map (XSDE_SERIALIZER_SMAP_BUCKETS);
#else
          map = static_cast<substitution_map*> (
            alloc (sizeof (substitution_map)));

#ifdef XSDE_EXCEPTIONS
          alloc_guard mg (map);
          new (map) substitution_map (XSDE_SERIALIZER_SMAP_BUCKETS);
          mg.release ();
#else
          if (map)
            new (map) substitution_map (XSDE_SERIALIZER_SMAP_BUCKETS);
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
      substitution_map_entry (const char* root,
                              const char* member_ns,
                              const char* member_name,
                              const char* member_type)
      {
        substitution_map& m = substitution_map_instance ();
        m.insert (root, member_ns, member_name, member_type);

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
      serializer_smap_callback (
        bool (*callback) (
          const char* type,
          const void* obj,
          const char*& ns,
          const char*& name))
      {
        substitution_map_instance ().callback (callback);
      }

      // Load.
      //
      size_t
      serializer_smap_elements ()
      {
        return substitution_map_instance ().size ();
      }

      size_t
      serializer_smap_bucket_elements ()
      {
        size_t r = 0;

        substitution_map& m = substitution_map_instance ();

        for (substitution_map::const_iterator i (m.begin ()), e (m.end ());
             i != e; ++i)
        {
          const hashmap* h = *static_cast<const hashmap* const*> (*i);

          if (h->size () > r)
            r = h->size ();
        }

        return r;
      }
    }
  }
}
