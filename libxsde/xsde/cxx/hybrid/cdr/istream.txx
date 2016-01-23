// file      : xsde/cxx/hybrid/cdr/istream.txx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifdef XSDE_CUSTOM_ALLOCATOR
#  include <xsde/cxx/allocator.hxx>
#endif

namespace xsde
{
  namespace cxx
  {
    namespace hybrid
    {
#ifdef XSDE_EXCEPTIONS

      template <typename T>
      void
      operator>> (icdrstream& s, pod_sequence<T>& x)
      {
        size_t n;
        icdrstream::as_size as_size (n);
        s >> as_size;

        x.clear ();

        if (n > 0)
        {
          x.reserve (n);

          T i;
          while (n--)
          {
            s >> i;
            x.push_back (i);
          }
        }
      }

      template <typename T>
      void
      operator>> (icdrstream& s, fix_sequence<T>& x)
      {
        size_t n;
        icdrstream::as_size as_size (n);
        s >> as_size;

        x.clear ();

        if (n > 0)
        {
          x.reserve (n);

          while (n--)
          {
            T i;
            s >> i;
            x.push_back (i);
          }
        }
      }

      template <typename T>
      void
      operator>> (icdrstream& s, var_sequence<T>& x)
      {
        size_t n;
        icdrstream::as_size as_size (n);
        s >> as_size;

        x.clear ();

        if (n > 0)
        {
          x.reserve (n);

          while (n--)
          {
#ifndef XSDE_CUSTOM_ALLOCATOR
            T* p = new T;
#else
            T* p = static_cast<T*> (alloc (sizeof (T)));
            alloc_guard pg (p);
            new (p) T;
            pg.release ();
#endif
            typename var_sequence<T>::guard g (p);
            s >> *p;
            g.release ();
            x.push_back (p);
          }
        }
      }

#else // XSDE_EXCEPTIONS

      template <typename T>
      bool
      operator>> (icdrstream& s, pod_sequence<T>& x)
      {
        size_t n;
        icdrstream::as_size as_size (n);

        if (!(s >> as_size))
          return false;

        x.clear ();

        if (n > 0)
        {
          if (x.reserve (n))
            return false;

          T i;
          while (n--)
          {
            if (!(s >> i) || x.push_back (i))
              return false;
          }
        }

        return true;
      }

      template <typename T>
      bool
      operator>> (icdrstream& s, fix_sequence<T>& x)
      {
        size_t n;
        icdrstream::as_size as_size (n);

        if (!(s >> as_size))
          return false;

        x.clear ();

        if (n > 0)
        {
          if (x.reserve (n))
            return false;

          while (n--)
          {
            T i;
            if (!(s >> i) || x.push_back (i))
              return false;
          }
        }

        return true;
      }

      template <typename T>
      bool
      operator>> (icdrstream& s, var_sequence<T>& x)
      {
        size_t n;
        icdrstream::as_size as_size (n);

        if (!(s >> as_size))
          return false;

        x.clear ();

        if (n > 0)
        {
          if (x.reserve (n))
            return false;

          while (n--)
          {
#ifndef XSDE_CUSTOM_ALLOCATOR
            T* p = new T;

            if (p == 0)
              return false;
#else
            void* v = alloc (sizeof (T));

            if (v == 0)
              return false;

            T* p = new (v) T; // c-tor cannot fail
#endif

            if (!(s >> *p))
            {
#ifndef XSDE_CUSTOM_ALLOCATOR
              delete p;
#else
              p->~T ();
              cxx::free (p);
#endif
              return false;
            }

            if (x.push_back (p))
              return false;
          }
        }

        return true;
      }

#endif // XSDE_EXCEPTIONS
    }
  }
}
