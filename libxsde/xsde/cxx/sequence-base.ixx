// file      : xsde/cxx/sequence-base.ixx
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
    inline sequence_base::
    sequence_base ()
        : data_ (0), size_ (0), capacity_ (0)
    {
    }

    inline sequence_base::
    ~sequence_base ()
    {
      if (data_)
#ifndef XSDE_CUSTOM_ALLOCATOR
        operator delete (data_);
#else
        cxx::free (data_);
#endif
    }

    inline bool sequence_base::
    empty () const
    {
      return size_ == 0;
    }

    inline size_t sequence_base::
    size () const
    {
      return size_;
    }

    inline size_t sequence_base::
    capacity () const
    {
      return capacity_;
    }

    inline void sequence_base::
    swap_ (sequence_base& x)
    {
      void* d = x.data_;
      size_t s = x.size_;
      size_t c = x.capacity_;

      x.data_ = data_;
      x.size_ = size_;
      x.capacity_ = capacity_;

      data_ = d;
      size_ = s;
      capacity_ = c;
    }
  }
}
