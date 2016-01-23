// file      : xsde/cxx/config.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_CONFIG_HXX
#define XSDE_CXX_CONFIG_HXX

#include <xsde/config.h>

// Macro to suppress unused variable warning.
//
#define XSDE_UNUSED(x) (void)x

// Using strtof appears to be highly non-portable.
//
#undef XSDE_STRTOF

// The snprintf function on Win32 and WinCE is called _snprintf.
//
#ifdef XSDE_SNPRINTF
#  if defined(XSDE_PLATFORM_WIN32) || defined(XSDE_PLATFORM_WINCE)
#    define snprintf _snprintf
#  endif
#endif

#endif // XSDE_CXX_CONFIG_HXX
