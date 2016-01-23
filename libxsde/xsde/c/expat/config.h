#ifndef XSDE_C_EXPAT_CONFIG_H
#define XSDE_C_EXPAT_CONFIG_H

#include <xsde/config.h>


#if XSDE_BYTEORDER == 1234
#  define BYTEORDER 1234
#elif XSDE_BYTEORDER == 4321
#  define BYTEORDER 4321
#else
#  error XSDE_BYTEORDER is not defined or defined to an invalid value
#endif


#define XML_NS 1
#define XML_DTD 1
#define XML_CONTEXT_BYTES 1024

#define UNUSED(x) (void)x;

/* Windows
 *
 */
#if defined(XSDE_PLATFORM_WIN32) || defined (XSDE_PLATFORM_WINCE)

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN

#define HAVE_MEMMOVE 1

#endif /* XSDE_PLATFORM_WIN32 || XSDE_PLATFORM_WINCE */

/* POSIX
 *
 */
#ifdef XSDE_PLATFORM_POSIX
#define HAVE_MEMMOVE 1
#endif

#endif /* XSDE_C_EXPAT_CONFIG_H */
