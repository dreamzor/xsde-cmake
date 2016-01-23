// file      : xsde/allocator.c
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// This is the default implementation of the custom allocator functions.
// It is primarily useful for testing when XSD/e is configured with custom
// allocators. You can also replace this implementation with your own if
// you would like to test with that.
//

#include <stdlib.h>

#include <xsde/allocator.h>

void*
xsde_alloc (size_t n)
{
  return malloc (n);
}

void*
xsde_realloc (void* p, size_t n)
{
  return realloc (p, n);
}

void
xsde_free (void* p)
{
  free (p);
}
