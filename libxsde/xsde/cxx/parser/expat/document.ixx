// file      : xsde/cxx/parser/expat/document.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsde
{
  namespace cxx
  {
    namespace parser
    {
      namespace expat
      {
        // parser_auto_ptr
        //
        inline parser_auto_ptr::
        ~parser_auto_ptr ()
        {
          if (parser_ != 0)
            XML_ParserFree (parser_);
        }

        inline parser_auto_ptr::
        parser_auto_ptr (XML_Parser parser)
            : parser_ (parser)
        {
        }

        inline parser_auto_ptr& parser_auto_ptr::
        operator= (XML_Parser parser)
        {
          if (parser_ != 0)
            XML_ParserFree (parser_);

          parser_ = parser;
          return *this;
        }


        // document_pimpl
        //
#ifndef XSDE_EXCEPTIONS
        inline const error& document_pimpl::
        _error () const
        {
          return error_;
        }
#endif
      }
    }
  }
}
