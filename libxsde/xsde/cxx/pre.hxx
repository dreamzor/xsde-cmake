// file      : xsde/cxx/pre.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// VC++
//
#ifdef _MSC_VER
#  if (_MSC_VER >= 1400)
#    include <xsde/cxx/compilers/vc-8/pre.hxx>
#  elif (_MSC_VER >= 1300)
#    include <xsde/cxx/compilers/vc-7/pre.hxx>
#  elif (_MSC_VER >= 1200)
#    include <xsde/cxx/compilers/vc-6/pre.hxx>
#  endif
#endif

// Green Hills C++
//
#if defined(__ghs__) || defined(__ghs) || defined(ghs)
#  include <xsde/cxx/compilers/ghs/pre.hxx>
#endif
