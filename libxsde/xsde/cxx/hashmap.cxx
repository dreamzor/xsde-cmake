// file      : xsde/cxx/hashmap.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <string.h> // memset, memcpy, strlen, strcmp, strncmp

#include <xsde/cxx/hashmap.hxx>

#ifdef XSDE_CUSTOM_ALLOCATOR
#  include <xsde/cxx/allocator.hxx>
#endif

namespace xsde
{
  namespace cxx
  {
    // const_iterator
    //
    hashmap_const_iterator::
    hashmap_const_iterator (const hashmap& map, size_t b)
        : map_ (&map), bucket_ (b), element_ (0)
    {
      // Get it to the first actual element if any.
      //
      for (; bucket_ < map_->bcount_; ++bucket_)
      {
        hashmap::bucket* p = map_->buckets_[bucket_];
        if (p && p->size_)
          break;
      }
    }

    const void* hashmap_const_iterator::
    operator* () const
    {
      typedef hashmap::bucket bucket;
      typedef hashmap::element element;

      bucket* p = map_->buckets_[bucket_];
      const char* b = reinterpret_cast<const char*> (p) + sizeof (bucket);
      b += element_ * (sizeof (element) + map_->esize_);
      return b + sizeof (element);
    }

    hashmap_const_iterator& hashmap_const_iterator::
    operator++ ()
    {
      if (bucket_ < map_->bcount_)
      {
        hashmap::bucket* p = map_->buckets_[bucket_];

        if (p->size_ > element_ + 1)
          ++element_;
        else
        {
          element_ = 0;

          for (++bucket_; bucket_ < map_->bcount_; ++bucket_)
          {
            p = map_->buckets_[bucket_];
            if (p && p->size_)
              break;
          }
        }
      }

      return *this;
    }

    // hashmap
    //
    hashmap::
    ~hashmap ()
    {
#ifndef XSDE_EXCEPTIONS
      if (buckets_ != 0)
      {
#endif
        for (size_t i = 0; i < bcount_; ++i)
        {
          if (buckets_[i])
#ifndef XSDE_CUSTOM_ALLOCATOR
            operator delete (buckets_[i]);
#else
            cxx::free (buckets_[i]);
#endif
        }

#ifndef XSDE_CUSTOM_ALLOCATOR
        delete[] buckets_;
#else
        cxx::free (buckets_); // POD.
#endif

#ifndef XSDE_EXCEPTIONS
      }
#endif
    }


    hashmap::
    hashmap (size_t bcount, size_t esize)
        : esize_ (esize), ecount_ (0), bcount_ (bcount), buckets_ (0)
    {
#ifndef XSDE_EXCEPTIONS
      error_ = error_none;
#endif

#ifndef XSDE_CUSTOM_ALLOCATOR
      buckets_ = new bucket*[bcount_];
#else
      buckets_ = static_cast<bucket**> (alloc (bcount_ * sizeof (bucket*)));
#endif

#ifndef XSDE_EXCEPTIONS
      if (buckets_ == 0)
      {
        error_ = error_no_memory;
        return;
      }
#endif
      memset (buckets_, 0, sizeof (bucket*) * bcount_);
    }

    void hashmap::
    insert (const char* key, void* value)
    {
      size_t h = hash (key);
      bucket*& p = *(buckets_ + h % bcount_);

      if (p == 0)
      {
        // No elements in this bucket yet. Start with capacity for 2
        // elements.
        //
#ifndef XSDE_CUSTOM_ALLOCATOR
        p = static_cast<bucket*> (
          operator new (sizeof (bucket) + 2 * (sizeof (element) + esize_)));
#else
        p = static_cast<bucket*> (
          alloc (sizeof (bucket) + 2 * (sizeof (element) + esize_)));
#endif

#ifndef XSDE_EXCEPTIONS
        if (p == 0)
        {
          error_ = error_no_memory;
          return;
        }
#endif
        p->size_ = 0;
        p->capacity_ = 2;
      }

      if (p->size_ == p->capacity_)
      {
        // No more space in this bucket. Create a bigger bucket.
        //
        size_t c = p->size_ * 2;

#ifndef XSDE_CUSTOM_ALLOCATOR
        bucket* n = static_cast<bucket*> (
          operator new (sizeof (bucket) + c * (sizeof (element) + esize_)));
#else
        bucket* n = static_cast<bucket*> (
          alloc (sizeof (bucket) + c * (sizeof (element) + esize_)));
#endif

#ifndef XSDE_EXCEPTIONS
        if (n == 0)
        {
          error_ = error_no_memory;
          return;
        }
#endif
        n->size_ = p->size_;
        n->capacity_ = c;

        char* src = reinterpret_cast<char*> (p) + sizeof (bucket);
        char* dst = reinterpret_cast<char*> (n) + sizeof (bucket);

        memcpy (dst, src, p->size_ * (sizeof (element) + esize_));

#ifndef XSDE_CUSTOM_ALLOCATOR
        operator delete (p);
#else
        cxx::free (p);
#endif
        p = n;
      }

      char* data = reinterpret_cast<char*> (p) + sizeof (bucket) +
        p->size_ * (sizeof (element) + esize_);

      element* e = reinterpret_cast<element*> (data);
      e->hash_ = h;
      e->key_ = key;

      memcpy (data + sizeof (element), value, esize_);

      p->size_++;
      ecount_++;
    }

    const void* hashmap::
    find (const char* key) const
    {
      size_t h = hash (key);
      const bucket* p = *(buckets_ + h % bcount_);

      if (p)
      {
        const char* b = reinterpret_cast<const char*> (p) + sizeof (bucket);
        const char* e = b + p->size_ * (sizeof (element) + esize_);

        for (; b < e; b += sizeof (element) + esize_)
        {
          const element* e = reinterpret_cast<const element*> (b);

          if (e->hash_ == h && strcmp (e->key_, key) == 0)
            return b + sizeof (element);
        }
      }

      return 0;
    }

    size_t hashmap::
    max_bucket_size () const
    {
      size_t r = 0;
      for (size_t i = 0; i < bcount_; ++i)
      {
        if (buckets_[i] != 0 && buckets_[i]->size_ > r)
          r = buckets_[i]->size_;
      }
      return r;
    }
  }
}
