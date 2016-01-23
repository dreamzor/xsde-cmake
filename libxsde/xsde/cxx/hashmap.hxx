// file      : xsde/cxx/hashmap.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_HASHMAP_HXX
#define XSDE_CXX_HASHMAP_HXX

#include <stddef.h> // size_t

#include <xsde/cxx/config.hxx>

namespace xsde
{
  namespace cxx
  {
    class hashmap;

    class hashmap_const_iterator
    {
    public:
      hashmap_const_iterator (const hashmap& map, size_t bucket);

      // Forward iterator requirements.
      //
      const void*
      operator* () const;

      hashmap_const_iterator&
      operator++ ();

      hashmap_const_iterator
      operator++ (int);

      friend bool
      operator== (const hashmap_const_iterator& i,
                  const hashmap_const_iterator& j);
    private:
      const hashmap* map_;
      size_t bucket_;
      size_t element_;
    };

    bool
    operator!= (const hashmap_const_iterator& i,
                const hashmap_const_iterator& j);

    // Special-purpose, light-weight C-string to POD hashmap. Some of
    // its characteristics:
    //
    // - number of buckets does not grow (no re-hashing)
    // - removal of items is not supported
    // - key and value (POD) are not deep-copied
    // - empty bucket is cheap (1 pointer)
    //
    class hashmap
    {
    public:
#ifndef XSDE_EXCEPTIONS
      enum error
      {
        error_none,
        error_no_memory
      };

      error
      _error () const;
#endif

    public:
      ~hashmap ();
      hashmap (size_t buckets, size_t element_size);

    private:
      hashmap (hashmap&);
      hashmap& operator= (hashmap&);

    public:
      void
      insert (const char* key, void* value);

      const void*
      find (const char* key) const;

    public:
      bool
      empty () const;

      size_t
      size () const;

      // Return the maximum number of elements in a single bucket.
      //
      size_t
      max_bucket_size () const;

    public:
      typedef hashmap_const_iterator const_iterator;

      const_iterator
      begin () const;

      const_iterator
      end () const;

    public:
      static size_t
      hash (const char*);

      static size_t
      hash (const char*, size_t n);

      static size_t
      hash (size_t hash, const char*);

      static size_t
      hash (size_t hash, const char*, size_t n);

    protected:
      // Keep these types POD.
      //
      struct bucket
      {
        size_t size_;
        size_t capacity_;
      };

      struct element
      {
        size_t hash_;
        const char* key_;
      };

    protected:
      const bucket*
      find (size_t hash) const;

    private:
      friend class hashmap_const_iterator;

      size_t esize_;  // element size
      size_t ecount_; // element count
      size_t bcount_; // bucket count
      bucket** buckets_;

#ifndef XSDE_EXCEPTIONS
    protected:
      error error_;
#endif
    };
  }
}

#include <xsde/cxx/hashmap.ixx>

#endif // XSDE_CXX_HASHMAP_HXX
