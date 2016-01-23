// file      : xsde/cxx/hashmap.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsde
{
  namespace cxx
  {
    // const_iterator
    //
    inline hashmap_const_iterator hashmap_const_iterator::
    operator++ (int)
    {
      hashmap_const_iterator r (*this);
      ++(*this);
      return r;
    }

    inline bool
    operator== (const hashmap_const_iterator& i,
                const hashmap_const_iterator& j)
    {
      return i.map_ == j.map_ &&
        i.bucket_ == j.bucket_ &&
        i.element_ == j.element_;
    }

    inline bool
    operator!= (const hashmap_const_iterator& i,
                const hashmap_const_iterator& j)
    {
      return !(i == j);
    }

    // hashmap
    //

#ifndef XSDE_EXCEPTIONS
    inline hashmap::error hashmap::
    _error () const
    {
      return error_;
    }
#endif

    inline bool hashmap::
    empty () const
    {
      return ecount_ == 0;
    }

    inline size_t hashmap::
    size () const
    {
      return ecount_;
    }

    inline const hashmap::bucket* hashmap::
    find (size_t h) const
    {
      return *(buckets_ + h % bcount_);
    }

    inline hashmap::const_iterator hashmap::
    begin () const
    {
      return const_iterator (*this, ecount_ ? 0 : bcount_);
    }

    inline hashmap::const_iterator hashmap::
    end () const
    {
      return const_iterator (*this, bcount_);
    }

    // Fowler/Noll/Vo (FNV) hash (type FNV-1a)
    //
#if XSDE_ARCH_WIDTH == 32
    inline size_t hashmap::
    hash (const char* s)
    {
      size_t r = static_cast<size_t> (2166136261UL);
      for (; *s != 0; ++s)
      {
        r ^= static_cast<size_t> (*s);
        r *= static_cast<size_t> (16777619UL);
      }
      return r;
    }

    inline size_t hashmap::
    hash (const char* s, size_t n)
    {
      size_t r = static_cast<size_t> (2166136261UL);
      for (; n > 0; --n)
      {
        r ^= static_cast<size_t> (*s++);
        r *= static_cast<size_t> (16777619UL);
      }
      return r;
    }

    inline size_t hashmap::
    hash (size_t h, const char* s)
    {
      for (; *s != 0; ++s)
      {
        h ^= static_cast<size_t> (*s);
        h *= static_cast<size_t> (16777619UL);
      }
      return h;
    }

    inline size_t hashmap::
    hash (size_t h, const char* s, size_t n)
    {
      for (; n > 0; --n)
      {
        h ^= static_cast<size_t> (*s++);
        h *= static_cast<size_t> (16777619UL);
      }
      return h;
    }

#elif XSDE_ARCH_WIDTH == 64

    inline size_t hashmap::
    hash (const char* s)
    {
      size_t r = static_cast<size_t> (14695981039346656037ULL);
      for (; *s != 0; ++s)
      {
        r ^= static_cast<size_t> (*s);
        r *= static_cast<size_t> (1099511628211ULL);
      }
      return r;
    }

    inline size_t hashmap::
    hash (const char* s, size_t n)
    {
      size_t r = static_cast<size_t> (14695981039346656037ULL);
      for (; n > 0; --n)
      {
        r ^= static_cast<size_t> (*s++);
        r *= static_cast<size_t> (1099511628211ULL);
      }
      return r;
    }

    inline size_t hashmap::
    hash (size_t h, const char* s)
    {
      for (; *s != 0; ++s)
      {
        h ^= static_cast<size_t> (*s);
        h *= static_cast<size_t> (1099511628211ULL);
      }
      return h;
    }

    inline size_t hashmap::
    hash (size_t h, const char* s, size_t n)
    {
      for (; n > 0; --n)
      {
        h ^= static_cast<size_t> (*s++);
        h *= static_cast<size_t> (1099511628211ULL);
      }
      return h;
    }
#else
#error there is no suitable hash function for this architecture width
#endif // XSDE_ARCH_WIDTH
  }
}
