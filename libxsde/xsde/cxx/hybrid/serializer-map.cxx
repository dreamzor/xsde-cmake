// file      : xsde/cxx/hybrid/serializer-map.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <string.h> // strcmp

#include <xsde/cxx/hybrid/serializer-map.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace hybrid
    {
      serializer::serializer_base* serializer_map_impl::
      find (const void* v) const
      {
        const char* tid = static_cast<const char*> (v);

        // Binary search.
        //
        if (size_ == 0)
          return 0;

        int r = 1;
        size_t m = 0;
        size_t l = 0;
        size_t h = size_ - 1;

        while (l <= h)
        {
          m = l + (h - l)/2;
          r = strcmp (entries_[m].type_id, tid);

          if (r == 0 || l == h)
            break;

          if (r < 0)
            l = m + 1;
          else
            h = (m == 0 ? 0 : m - 1);
        }

        return r == 0 ? entries_[m].serializer : 0;
      }

      void serializer_map_impl::
      reset () const
      {
        if (resetting_)
          return;

        bool& r = const_cast<bool&> (resetting_);
        r = true;

        for (const entry* p = entries_; p != entries_ + size_; ++p)
          p->serializer->_reset ();

        r = false;
      }
    }
  }
}
