// file      : xsde/cxx/compilers/ghs/pre.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Warning pragmas are only available in the new generation compiler.
//
// 997 - virtual function hidden
//
#ifdef __EDG__
#  pragma ghs nowarning 997
#endif
