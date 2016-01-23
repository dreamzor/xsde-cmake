// file      : xsde/cxx/hybrid/sequence.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_HYBRID_SEQUENCE_HXX
#define XSDE_CXX_HYBRID_SEQUENCE_HXX

#include <xsde/cxx/config.hxx>

#include <stddef.h> // size_t, ptrdiff_t

#ifdef XSDE_STL_ITERATOR
#  include <iterator>
#endif

#include <xsde/cxx/sequence-base.hxx>

#ifdef XSDE_STL
#  include <xsde/cxx/string-sequence-stl.hxx>
#else
#  include <xsde/cxx/string-sequence.hxx>
#endif

#ifdef XSDE_CUSTOM_ALLOCATOR
#  include <xsde/cxx/allocator.hxx>
#endif

namespace xsde
{
  namespace cxx
  {
    namespace hybrid
    {
      // Sequence with fixed-length POD elements.
      //
      template <typename T>
      class pod_sequence: public sequence_base
      {
      public:
        typedef T         value_type;
        typedef T*        pointer;
        typedef const T*  const_pointer;
        typedef T&        reference;
        typedef const T&  const_reference;

        typedef size_t    size_type;
        typedef ptrdiff_t difference_type;

        typedef T*        iterator;
        typedef const T*  const_iterator;

      public:
        iterator
        begin ();

        const_iterator
        begin () const;

        iterator
        end ();

        const_iterator
        end () const;

        T&
        front ();

        const T&
        front () const;

        T&
        back ();

        const T&
        back () const;

        T&
        operator[] (size_t);

        const T&
        operator[] (size_t) const;

      public:
        size_t
        max_size () const;

        void
        clear ();

        void
        pop_back ();

        iterator
        erase (iterator);

#ifndef XSDE_EXCEPTIONS
        error
#else
        void
#endif
        push_back (const T&);

#ifndef XSDE_EXCEPTIONS
        error
        insert (iterator, const T&);

        error
        insert (iterator, const T&, iterator& result);
#else
        iterator
        insert (iterator, const T&);
#endif

#ifndef XSDE_EXCEPTIONS
        error
#else
        void
#endif
        reserve (size_t);

#ifndef XSDE_EXCEPTIONS
        error
#else
        void
#endif
        assign (const T*, size_t);

        void
        swap (pod_sequence&);

#ifndef XSDE_EXCEPTIONS
        error
#else
        void
#endif
        copy (pod_sequence&) const;
      };

      // Sequence with fixed-length elements.
      //
      template <typename T>
      class fix_sequence: public sequence_base
      {
      public:
        typedef T         value_type;
        typedef T*        pointer;
        typedef const T*  const_pointer;
        typedef T&        reference;
        typedef const T&  const_reference;

        typedef size_t    size_type;
        typedef ptrdiff_t difference_type;

        typedef T*        iterator;
        typedef const T*  const_iterator;

      public:
        ~fix_sequence ();

      public:
        iterator
        begin ();

        const_iterator
        begin () const;

        iterator
        end ();

        const_iterator
        end () const;

        T&
        front ();

        const T&
        front () const;

        T&
        back ();

        const T&
        back () const;

        T&
        operator[] (size_t);

        const T&
        operator[] (size_t) const;

      public:
        size_t
        max_size () const;

        void
        clear ();

        void
        pop_back ();

        iterator
        erase (iterator);

#ifndef XSDE_EXCEPTIONS
        error
#else
        void
#endif
        push_back (const T&);

#ifndef XSDE_EXCEPTIONS
        error
        insert (iterator, const T&);

        error
        insert (iterator, const T&, iterator& result);
#else
        iterator
        insert (iterator, const T&);
#endif

#ifndef XSDE_EXCEPTIONS
        error
#else
        void
#endif
        reserve (size_t);

#ifndef XSDE_EXCEPTIONS
        error
#else
        void
#endif
        assign (const T*, size_t);

        void
        swap (fix_sequence&);

#ifndef XSDE_EXCEPTIONS
        error
#else
        void
#endif
        copy (fix_sequence&) const;

      private:
        static void
        move_ (void* dst, void* src, size_t n);

        static void
        move_forward_ (void* p, size_t n);

#ifdef XSDE_EXCEPTIONS
        static void
        move_backward_ (void* p, size_t n, size_t& size);
#else
        static void
        move_backward_ (void* p, size_t n);
#endif

#ifdef XSDE_EXCEPTIONS
        struct guard
        {
          guard (T* p, size_t& n) : p_ (p), n_ (n) {}

          ~guard ()
          {
            if (p_)
              for (; n_ > 0; --n_)
                p_[n_ - 1].~T ();
          }

          void
          release () { p_ = 0; }

        private:
          T* p_;
          size_t& n_;
        };
#endif
      };

      // Sequence with variable-length elements.
      //
      template <typename T>
      class var_iterator
      {
      public:
        typedef T  value_type;
        typedef T& reference;
        typedef T* pointer;

        typedef ptrdiff_t difference_type;

#ifdef XSDE_STL_ITERATOR
        typedef std::random_access_iterator_tag iterator_category;
#endif

      public:
        var_iterator ()
            : i_ (0)
        {
        }

        explicit
        var_iterator (T** i)
            : i_ (i)
        {
        }

      public:
        // Forward iterator requirements.
        //
        T&
        operator* () const
        {
          return **i_;
        }

        T*
        operator-> () const
        {
          return *i_;
        }

        var_iterator&
        operator++ ()
        {
          ++i_;
          return *this;
        }

        var_iterator
        operator++ (int)
        {
          var_iterator r (*this);
          ++i_;
          return r;
        }

        // Bidirectional iterator requirements.
        //
        var_iterator&
        operator-- ()
        {
          --i_;
          return *this;
        }

        var_iterator
        operator-- (int)
        {
          var_iterator r (*this);
          --i_;
          return r;
        }

        // Random access iterator requirements.
        //
        T&
        operator[] (ptrdiff_t n) const
        {
          return *(i_[n]);
        }

        var_iterator&
        operator+= (ptrdiff_t n)
        {
          i_ += n;
          return *this;
        }

        var_iterator
        operator+ (ptrdiff_t n) const
        {
          return var_iterator (i_ + n);
        }

        var_iterator&
        operator-= (ptrdiff_t n)
        {
          i_ -= n;
          return *this;
        }

        var_iterator
        operator- (ptrdiff_t n) const
        {
          return var_iterator (i_ - n);
        }

      public:
        T** i_;
      };

      template <typename T>
      class var_const_iterator
      {
      public:
        typedef const T  value_type;
        typedef const T& reference;
        typedef const T* pointer;

        typedef ptrdiff_t difference_type;

#ifdef XSDE_STL_ITERATOR
        typedef std::random_access_iterator_tag iterator_category;
#endif

      public:
        var_const_iterator ()
            : i_ (0)
        {
        }

        var_const_iterator (var_iterator<T> j)
            : i_ (const_cast<const T**> (j.i_))
        {
        }

        explicit
        var_const_iterator (const T** i)
            : i_ (i)
        {
        }

        var_const_iterator&
        operator= (var_const_iterator j)
        {
          i_ = j.i_;
          return *this;
        }

        var_const_iterator&
        operator= (var_iterator<T> j)
        {
          i_ = const_cast<const T**> (j.i_);
          return *this;
        }

      public:
        // Forward iterator requirements.
        //
        const T&
        operator* () const
        {
          return **i_;
        }

        const T*
        operator-> () const
        {
          return *i_;
        }

        var_const_iterator&
        operator++ ()
        {
          ++i_;
          return *this;
        }

        var_const_iterator
        operator++ (int)
        {
          var_const_iterator r (*this);
          ++i_;
          return r;
        }

        // Bidirectional iterator requirements.
        //
        var_const_iterator&
        operator-- ()
        {
          --i_;
          return *this;
        }

        var_const_iterator
        operator-- (int)
        {
          var_const_iterator r (*this);
          --i_;
          return r;
        }

        // Random access iterator requirements.
        //
        const T&
        operator[] (ptrdiff_t n) const
        {
          return *(i_[n]);
        }

        var_const_iterator&
        operator+= (ptrdiff_t n)
        {
          i_ += n;
          return *this;
        }

        var_const_iterator
        operator+ (ptrdiff_t n) const
        {
          return var_const_iterator (i_ + n);
        }

        var_const_iterator&
        operator-= (ptrdiff_t n)
        {
          i_ -= n;
          return *this;
        }

        var_const_iterator
        operator- (ptrdiff_t n) const
        {
          return var_const_iterator (i_ - n);
        }

      public:
        const T** i_;
      };

      // Forward iterator requirements.
      //
      template <typename T>
      inline bool
      operator== (var_iterator<T> i, var_iterator<T> j)
      {
        return i.i_ == j.i_;
      }

      template <typename T>
      inline bool
      operator== (var_const_iterator<T> i, var_const_iterator<T> j)
      {
        return i.i_ == j.i_;
      }

      template <typename T>
      inline bool
      operator== (var_iterator<T> i, var_const_iterator<T> j)
      {
        // eVC++ 4.0 needs the cast.
        //
        return const_cast<const T**> (i.i_) == j.i_;
      }

      template <typename T>
      inline bool
      operator== (var_const_iterator<T> i, var_iterator<T> j)
      {
        return i.i_ == const_cast<const T**> (j.i_);
      }

      template <typename T>
      inline bool
      operator!= (var_iterator<T> i, var_iterator<T> j)
      {
        return i.i_ != j.i_;
      }

      template <typename T>
      inline bool
      operator!= (var_const_iterator<T> i, var_const_iterator<T> j)
      {
        return i.i_ != j.i_;
      }

      template <typename T>
      inline bool
      operator!= (var_iterator<T> i, var_const_iterator<T> j)
      {
        return const_cast<const T**> (i.i_) != j.i_;
      }

      template <typename T>
      inline bool
      operator!= (var_const_iterator<T> i, var_iterator<T> j)
      {
        return i.i_ != const_cast<const T**> (j.i_);
      }

      // Random access iterator requirements
      //
      template <typename T>
      inline bool
      operator< (var_iterator<T> i, var_iterator<T> j)
      {
        return i.i_ < j.i_;
      }

      template <typename T>
      inline bool
      operator< (var_const_iterator<T> i, var_const_iterator<T> j)
      {
        return i.i_ < j.i_;
      }

      template <typename T>
      inline bool
      operator< (var_iterator<T> i, var_const_iterator<T> j)
      {
        return const_cast<const T**> (i.i_) < j.i_;
      }

      template <typename T>
      inline bool
      operator< (var_const_iterator<T> i, var_iterator<T> j)
      {
        return i.i_ < const_cast<const T**> (j.i_);
      }

      template <typename T>
      inline bool
      operator> (var_iterator<T> i, var_iterator<T> j)
      {
        return i.i_ > j.i_;
      }

      template <typename T>
      inline bool
      operator> (var_const_iterator<T> i, var_const_iterator<T> j)
      {
        return i.i_ > j.i_;
      }

      template <typename T>
      inline bool
      operator> (var_iterator<T> i, var_const_iterator<T> j)
      {
        return const_cast<const T**> (i.i_) > j.i_;
      }

      template <typename T>
      inline bool
      operator> (var_const_iterator<T> i, var_iterator<T> j)
      {
        return i.i_ > const_cast<const T**> (j.i_);
      }

      template <typename T>
      inline bool
      operator<= (var_iterator<T> i, var_iterator<T> j)
      {
        return i.i_ <= j.i_;
      }

      template <typename T>
      inline bool
      operator<= (var_const_iterator<T> i, var_const_iterator<T> j)
      {
        return i.i_ <= j.i_;
      }

      template <typename T>
      inline bool
      operator<= (var_iterator<T> i, var_const_iterator<T> j)
      {
        return const_cast<const T**> (i.i_) <= j.i_;
      }

      template <typename T>
      inline bool
      operator<= (var_const_iterator<T> i, var_iterator<T> j)
      {
        return i.i_ <= const_cast<const T**> (j.i_);
      }

      template <typename T>
      inline bool
      operator>= (var_iterator<T> i, var_iterator<T> j)
      {
        return i.i_ >= j.i_;
      }

      template <typename T>
      inline bool
      operator>= (var_const_iterator<T> i, var_const_iterator<T> j)
      {
        return i.i_ >= j.i_;
      }

      template <typename T>
      inline bool
      operator>= (var_iterator<T> i, var_const_iterator<T> j)
      {
        return const_cast<const T**> (i.i_) >= j.i_;
      }

      template <typename T>
      inline bool
      operator>= (var_const_iterator<T> i, var_iterator<T> j)
      {
        return i.i_ >= const_cast<const T**> (j.i_);
      }

      template <typename T>
      inline ptrdiff_t
      operator- (var_iterator<T> i, var_iterator<T> j)
      {
        return i.i_ - j.i_;
      }

      template <typename T>
      inline ptrdiff_t
      operator- (var_const_iterator<T> i, var_const_iterator<T> j)
      {
        return i.i_ - j.i_;
      }

      template <typename T>
      inline ptrdiff_t
      operator- (var_iterator<T> i, var_const_iterator<T> j)
      {
        return const_cast<const T**> (i.i_) - j.i_;
      }

      template <typename T>
      inline ptrdiff_t
      operator- (var_const_iterator<T> i, var_iterator<T> j)
      {
        return i.i_ - const_cast<const T**> (j.i_);
      }

      template <typename T>
      inline var_iterator<T>
      operator+ (ptrdiff_t n, var_iterator<T> i)
      {
        return var_iterator<T> (i.i_ + n);
      }

      template <typename T>
      inline var_iterator<T>
      operator+ (ptrdiff_t n, var_const_iterator<T> i)
      {
        return var_const_iterator<T> (i.i_ + n);
      }

      //
      //
      template <typename T>
      class var_sequence: public sequence_base
      {
      public:
        typedef T         value_type;
        typedef T*        pointer;
        typedef const T*  const_pointer;
        typedef T&        reference;
        typedef const T&  const_reference;

        typedef size_t    size_type;
        typedef ptrdiff_t difference_type;

        typedef var_iterator<T> iterator;
        typedef var_const_iterator<T> const_iterator;

      public:
        ~var_sequence ();

      public:
        iterator
        begin ();

        const_iterator
        begin () const;

        iterator
        end ();

        const_iterator
        end () const;

        T&
        front ();

        const T&
        front () const;

        T&
        back ();

        const T&
        back () const;

        T&
        operator[] (size_t);

        const T&
        operator[] (size_t) const;

      public:
        size_t
        max_size () const;

        void
        clear ();

        void
        pop_back ();

        iterator
        erase (iterator);

#ifndef XSDE_EXCEPTIONS
        error
#else
        void
#endif
        push_back (T*);

#ifndef XSDE_EXCEPTIONS
        error
        insert (iterator, T*);

        error
        insert (iterator, T*, iterator& result);
#else
        iterator
        insert (iterator, T*);
#endif

        // Detach an object from the sequence at a given position.
        // The object pointer at this position in the sequence is
        // set to 0.
        //
        T*
        detach (iterator);

        // Attach an object to the sequence at a given position.
        //
        void
        attach (iterator, T*);

#ifndef XSDE_EXCEPTIONS
        error
#else
        void
#endif
        reserve (size_t);

        void
        swap (var_sequence&);

#ifndef XSDE_EXCEPTIONS
        error
#else
        void
#endif
        copy (var_sequence&) const;

#ifdef XSDE_EXCEPTIONS
      public:
        struct guard
        {
          ~guard ()
          {
#ifndef XSDE_CUSTOM_ALLOCATOR
            delete p_;
#else
            cxx::free (p_);
#endif
          }

          guard (T* p) : p_ (p) {}

          void
          release () { p_ = 0; }

        private:
          T* p_;
        };
#endif
      };

      // Custom data sequence.
      //
      class data_sequence: public sequence_base
      {
      public:
        typedef void*         value_type;
        typedef void**        pointer;
        typedef const void**  const_pointer;
        typedef void*         reference;
        typedef const void*   const_reference;

        typedef size_t        size_type;
        typedef ptrdiff_t     difference_type;

        typedef void** iterator;
        typedef const void* const* const_iterator;

      public:
        ~data_sequence ();
        data_sequence ();

        typedef void (*destroy_func) (void* data, size_t pos);
        typedef void* (*clone_func) (void* data, size_t pos);

        void
        destructor (destroy_func);

        void
        clone (clone_func);

      public:
        iterator
        begin ();

        const_iterator
        begin () const;

        iterator
        end ();

        const_iterator
        end () const;

        void*
        front ();

        const void*
        front () const;

        void*
        back ();

        const void*
        back () const;

        void*
        operator[] (size_t);

        const void*
        operator[] (size_t) const;

      public:
        size_t
        max_size () const;

        void
        clear ();

        void
        pop_back ();

        iterator
        erase (iterator);

#ifndef XSDE_EXCEPTIONS
        error
#else
        void
#endif
        push_back (void*);

#ifndef XSDE_EXCEPTIONS
        error
        insert (iterator, void*);

        error
        insert (iterator, void*, iterator& result);
#else
        iterator
        insert (iterator, void*);
#endif

#ifndef XSDE_EXCEPTIONS
        error
#else
        void
#endif
        reserve (size_t);

        void
        swap (data_sequence&);

#ifndef XSDE_EXCEPTIONS
        error
#else
        void
#endif
        copy (data_sequence&) const;

      private:
        destroy_func destructor_;
        clone_func clone_;
      };
    }
  }
}

#include <xsde/cxx/hybrid/sequence.ixx>
#include <xsde/cxx/hybrid/sequence.txx>

#endif  // XSDE_CXX_HYBRID_SEQUENCE_HXX
