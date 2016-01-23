/* file      : xsde/c/pre.h
 * author    : Boris Kolpackov <boris@codesynthesis.com>
 * copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
 * license   : GNU GPL v2 + exceptions; see accompanying LICENSE file
 */

#ifdef _MSC_VER
#  if (_MSC_VER >= 1400)
#    include <xsde/c/compilers/vc-8/pre.h>
#  endif
#endif

#if defined(__ghs__) || defined(__ghs) || defined(ghs)
#  include <xsde/c/compilers/ghs/pre.h>
#endif
