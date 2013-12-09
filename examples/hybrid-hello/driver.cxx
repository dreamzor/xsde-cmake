// file      : examples/cxx/hybrid/hello/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <iostream>

#include "hello.hxx"
#include "hello-pimpl.hxx"

using namespace std;

int
main (int argc, char* argv[])
{
  const char* input;

  if (argc < 2)
  {
    input = "STDIN";
    cerr << "XML file not specified, reading from STDIN" << endl;
  }
  else
    input = argv[1];

  try
  {
    // Parse.
    //
    hello_paggr hello_p;

    xml_schema::document_pimpl doc_p (hello_p.root_parser (),
                                      hello_p.root_name ());
    hello_p.pre ();

    if (argc < 2)
      doc_p.parse (cin);
    else
      doc_p.parse (argv[1]);

    hello* h = hello_p.post ();

    // Print what we've got.
    //
    for (hello::name_const_iterator i = h->name ().begin ();
         i != h->name ().end ();
         ++i)
    {
      cout << h->greeting () << ", " << *i << "!" << endl;
    }

    delete h;
  }
  catch (const xml_schema::parser_exception& e)
  {
    cerr << input << ":" << e.line () << ":" << e.column () << ": "
         << e.text () << endl;
    return 1;
  }
  catch (const std::ios_base::failure&)
  {
    cerr << input << ": unable to open or read failure" << endl;
    return 1;
  }

  return 0;
}
