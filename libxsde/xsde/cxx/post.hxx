// file      : xsde/cxx/post.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// VC++
//
#ifdef _MSC_VER
#  if (_MSC_VER >= 1400)
#    include <xsde/cxx/compilers/vc-8/post.hxx>
#  elif (_MSC_VER >= 1300)
#    include <xsde/cxx/compilers/vc-7/post.hxx>
#  elif (_MSC_VER >= 1200)
#    include <xsde/cxx/compilers/vc-6/post.hxx>
#  endif
#endif

// Green Hills C++
//
#if defined(__ghs__) || defined(__ghs) || defined(ghs)
#  include <xsde/cxx/compilers/ghs/post.hxx>
#endif
