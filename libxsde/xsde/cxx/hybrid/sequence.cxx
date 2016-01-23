// file      : xsde/cxx/hybrid/sequence.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/hybrid/sequence.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace hybrid
    {
      //
      // data_sequence
      //

      void data_sequence::
      clear ()
      {
        if (destructor_)
        {
          for (size_t i = 0;  i < size_; ++i)
            destructor_ (static_cast<void**> (data_)[i], i);
        }

        size_ = 0;
      }

#ifdef XSDE_EXCEPTIONS
      void data_sequence::
      copy (data_sequence& c) const
      {
        if (c.size_ != 0)
          c.clear ();

        c.destructor_ = destructor_;
        c.clone_ = clone_;

        c.reserve (size_);

        for (; c.size_ < size_; ++c.size_)
        {
          static_cast<void**> (c.data_)[c.size_] =
            clone_ (static_cast<void**> (data_)[c.size_], c.size_);
        }
      }
#else
      sequence_base::error data_sequence::
      copy (data_sequence& c) const
      {
        if (c.size_ != 0)
          c.clear ();

        c.destructor_ = destructor_;
        c.clone_ = clone_;

        if (error r = c.reserve (size_))
          return r;

        for (; c.size_ < size_; ++c.size_)
        {
          void* x = clone_ (static_cast<void**> (data_)[c.size_], c.size_);

          if (x == 0)
            return error_no_memory;

          static_cast<void**> (c.data_)[c.size_] = x;
        }

        return error_none;
      }
#endif
    }
  }
}
