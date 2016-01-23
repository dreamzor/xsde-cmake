// file      : xsde/cxx/parser/non-validating/nmtokens-stl.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/config.hxx>

#ifdef XSDE_CUSTOM_ALLOCATOR
#  include <xsde/cxx/allocator.hxx>
#endif

#include <xsde/cxx/parser/non-validating/nmtokens-stl.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace non_validating
      {
        nmtokens_pimpl::
        ~nmtokens_pimpl ()
        {
          if (!base_ && seq_)
          {
#ifndef XSDE_CUSTOM_ALLOCATOR
            delete seq_;
#else
            seq_->~string_sequence ();
            cxx::free (seq_);
#endif
          }
        }

        void nmtokens_pimpl::
        _reset ()
        {
          nmtokens_pskel::_reset ();

          if (!base_ && seq_)
          {
#ifndef XSDE_CUSTOM_ALLOCATOR
            delete seq_;
#else
            seq_->~string_sequence ();
            cxx::free (seq_);
#endif
            seq_ = 0;
          }

          parser_._reset ();
        }

        nmtokens_pimpl::
        nmtokens_pimpl (bool base)
            : base_ (base), seq_ (0)
        {
        }

        void nmtokens_pimpl::
        pre_impl (string_sequence* seq)
        {
          seq_ = seq;
        }

        void nmtokens_pimpl::
        _pre ()
        {
          if (seq_ == 0)
          {
#ifndef XSDE_CUSTOM_ALLOCATOR
            seq_ = new string_sequence ();
#else
            seq_ = static_cast<string_sequence*> (
              alloc (sizeof (string_sequence)));

#ifdef XSDE_EXCEPTIONS
            alloc_guard ag (seq_);
            new (seq_) string_sequence ();
            ag.release ();
#else
            if (seq_)
              new (seq_) string_sequence ();
#endif
#endif

#ifndef XSDE_EXCEPTIONS
            if (seq_ == 0)
            {
              _sys_error (sys_error::no_memory);
              return;
            }
#endif
          }

          nmtokens_pskel::_pre ();
        }

        string_sequence* nmtokens_pimpl::
        post_nmtokens ()
        {
          string_sequence* r = seq_;
          seq_ = 0;
          return r;
        }

        void nmtokens_pimpl::
        _xsde_parse_item (const ro_string& s)
        {
          parser_.pre ();
          parser_._pre_impl (_context ());
          parser_._characters (s);
          parser_._post_impl ();
          seq_->push_back (parser_.post_nmtoken ());
        }
      }
    }
  }
}
