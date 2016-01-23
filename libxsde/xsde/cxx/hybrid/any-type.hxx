// file      : xsde/cxx/hybrid/any-type.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_HYBRID_ANY_TYPE_HXX
#define XSDE_CXX_HYBRID_ANY_TYPE_HXX

#include <xsde/cxx/config.hxx>

#ifdef XSDE_STL
#  include <string>
#endif

#include <xsde/cxx/hybrid/sequence.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace hybrid
    {
      struct any_type
      {
        any_type ()
            : data_ (0)
        {
        }

        // Custom data.
        //
        typedef data_sequence custom_data_sequence;
        typedef custom_data_sequence::iterator custom_data_iterator;
        typedef custom_data_sequence::const_iterator custom_data_const_iterator;

#ifndef XSDE_EXCEPTIONS
        bool
#else
        void
#endif
        allocate_custom_data ();

        const custom_data_sequence&
        custom_data () const
        {
          return *data_;
        }

        custom_data_sequence&
        custom_data ()
        {
          return *data_;
        }

#ifndef XSDE_EXCEPTIONS
        bool
#else
        void
#endif
        _copy (any_type&) const;

#ifndef XSDE_POLYMORPHIC
        ~any_type ();

        any_type*
        _clone () const;
#else
        virtual
        ~any_type ();

        virtual any_type*
        _clone () const;

#ifdef XSDE_STL
        virtual const std::string&
        _dynamic_type () const;

        static const std::string&
        _static_type ();
#else
        virtual const char*
        _dynamic_type () const;

        static const char*
        _static_type ();
#endif
#endif

      private:
        data_sequence* data_;
      };
    }
  }
}

#endif  // XSDE_CXX_HYBRID_ANY_TYPE_HXX
