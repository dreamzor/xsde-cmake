/* file      : xsde/c/compilers/ghs/pre.h
 * author    : Boris Kolpackov <boris@codesynthesis.com>
 * copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
 * license   : GNU GPL v2 + exceptions; see accompanying LICENSE file
 */

/*
 * Warning pragmas are only available in the new generation compiler.
 */

/* 111 - statement is unreachable */
#ifdef __EDG__
#  pragma ghs nowarning 111
#endif
