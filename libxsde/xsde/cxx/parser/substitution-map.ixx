// file      : xsde/cxx/parser/substitution-map.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      inline substitution_map::
      substitution_map (size_t buckets)
          : hashmap (buckets, sizeof (value)), callback_ (0)
      {
      }

      inline void substitution_map::
      insert (const char* member,
              const char* root,
              const char* type)
      {
        value v;
        v.root_ = root;
        v.type_ = type;
        hashmap::insert (member, &v);
      }

      inline void substitution_map::
      callback (callback_func c)
      {
        callback_ = c;
      }

      inline bool substitution_map::
      check (const ro_string& member_ns,
             const ro_string& member_name,
             const char* root,
             const char*& type) const
      {

        return !empty () || callback_ != 0
          ? check_ (member_ns, member_name, root, &type)
          : false;
      }

      inline bool substitution_map::
      check (const ro_string& member_ns,
             const ro_string& member_name,
             const char* root_ns,
             const char* root_name,
             const char*& type) const
      {
        return !empty () || callback_ != 0
          ? check_ (member_ns, member_name, root_ns, root_name, &type)
          : false;
      }

      inline bool substitution_map::
      check (const ro_string& member_ns,
             const ro_string& member_name,
             const char* root) const
      {

        return !empty () || callback_ != 0
          ? check_ (member_ns, member_name, root, 0)
          : false;
      }

      inline substitution_map&
      substitution_map_instance ()
      {
        return *substitution_map_init::map;
      }
    }
  }
}
