// file      : xsde/cxx/hybrid/sequence.txx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <new> // placement new

namespace xsde
{
  namespace cxx
  {
    namespace hybrid
    {
      //
      // fix_sequence
      //

      template <typename T>
      void fix_sequence<T>::
      clear ()
      {
        for (size_t i = 0;  i < size_; ++i)
          static_cast<T*> (data_)[i].~T ();

        size_ = 0;
      }

#ifdef XSDE_EXCEPTIONS
      template <typename T>
      void fix_sequence<T>::
      assign (const T* p, size_t n)
      {
        if (size_ != 0)
          clear ();

        reserve (n);

        for (; size_ < n; ++size_)
          new (static_cast<T*> (data_) + size_) T (p[size_]);
      }
#else
      template <typename T>
      sequence_base::error fix_sequence<T>::
      assign (const T* p, size_t n)
      {
        if (size_ != 0)
          clear ();

        if (error r = reserve (n))
          return r;

        for (; size_ < n; ++size_)
          new (static_cast<T*> (data_) + size_) T (p[size_]);

        return error_none;
      }
#endif

#ifdef XSDE_EXCEPTIONS
      template <typename T>
      void fix_sequence<T>::
      move_ (void* dst, void* src, size_t n)
      {
        T* d = static_cast<T*> (dst);
        T* s = static_cast<T*> (src);

        // The copy c-tor can throw in which case we need to destroy
        // whatever objects we already copied into d.
        //
        size_t i = 0;
        guard g (d, i);

        for (; i < n; i++)
          new (d + i) T (s[i]);

        g.release ();

        for (size_t j = 0; j < n; j++)
          s[j].~T ();
      }
#else
      template <typename T>
      void fix_sequence<T>::
      move_ (void* dst, void* src, size_t n)
      {
        T* d = static_cast<T*> (dst);
        T* s = static_cast<T*> (src);

        for (size_t i = 0; i < n; i++)
        {
          new (d + i) T (s[i]);
          s[i].~T ();
        }
      }
#endif

      template <typename T>
      void fix_sequence<T>::
      move_forward_ (void* p, size_t n)
      {
        // We are moving a sequence of elements one position to the left.
        // The tricky part is to make sure we are in at least destructable
        // state if things turn bad. We assume that there is a valid
        // element at position p.
        //
        T* d = static_cast<T*> (p);

        for (size_t i = 0; i < n; i++)
          d[i] = d[i + 1];

        d[n].~T ();
      }

#ifdef XSDE_EXCEPTIONS
      template <typename T>
      void fix_sequence<T>::
      move_backward_ (void* p, size_t n, size_t& size)
      {
        // We are moving a sequence of elements one position to the right.
        // The tricky part is to make sure we are in at least destructable
        // state if things turn bad.
        //
        T* d = static_cast<T*> (p);
        T* e = d + n;

        new (e) T;
        size++;

        for (size_t i = n; i > 0; i--)
          d[i] = d[i - 1];
      }
#else
      template <typename T>
      void fix_sequence<T>::
      move_backward_ (void* p, size_t n)
      {
        // We are moving a sequence of elements one position to the right.
        //
        T* d = static_cast<T*> (p);
        T* e = d + n;

        new (e) T;

        for (size_t i = n; i > 0; i--)
          d[i] = d[i - 1];
      }
#endif

      //
      // var_sequence
      //

      template <typename T>
      void var_sequence<T>::
      clear ()
      {
        for (size_t i = 0;  i < size_; ++i)
        {
          T* x = static_cast<T**> (data_)[i];

#ifndef XSDE_CUSTOM_ALLOCATOR
          delete x;
#else
          if (x)
            x->~T ();
          cxx::free (x);
#endif
        }

        size_ = 0;
      }

#ifdef XSDE_EXCEPTIONS
      template <typename T>
      void var_sequence<T>::
      copy (var_sequence& c) const
      {
        if (c.size_ != 0)
          c.clear ();

        c.reserve (size_);

        for (; c.size_ < size_; ++c.size_)
        {
          static_cast<T**> (c.data_)[c.size_] =
            static_cast<T**> (data_)[c.size_]->_clone ();
        }
      }
#else
      template <typename T>
      sequence_base::error var_sequence<T>::
      copy (var_sequence& c) const
      {
        if (c.size_ != 0)
          c.clear ();

        if (error r = c.reserve (size_))
          return r;

        for (; c.size_ < size_; ++c.size_)
        {
          T* x = static_cast<T**> (data_)[c.size_]->_clone ();

          if (x == 0)
            return error_no_memory;

          static_cast<T**> (c.data_)[c.size_] = x;
        }

        return error_none;
      }
#endif
    }
  }
}
