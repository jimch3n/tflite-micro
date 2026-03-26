#ifndef KP_DEBUG_H
#define KP_DEBUG_H

// kp_debug (knowles printf debug) is a helpful debugging tool -- it is
// essentially a conditional printf command and if KP_DEBUG is not #defined, it
// has no effect on compiled code.
//
// When KP_DEBUG is defined, and the first arguement to kp_debug() is true, then
// the printf part does its thing.  If the first arguement is false, nothing is
// printed.  For example, if KP_DEBUG is #defined:
//
// kp_debug(1, "hello world\n");  // prints hello world to stdout
// kp_debug(1, "answer=%d\n", 42); // prints answer=42
// kp_debug(0, "goodbye\n"); // nothing is printed
//
// If KP_DEBUG is not defined, then above lines have no effect on compiled code.
//
// As such, kp_debug.h is akin to assert.h in that a preprocessor directive is
// used -- in this case KP_DEBUG must be defined for kp_debug statements to
// impact compiled code. Note kp_debug works in reverse to assert's preprocessor
// directive NDEBUG.

#include <stdio.h>

#ifdef KP_DEBUG
// NOTE: must use "__VA_ARGS__" identifier here for C99 compatibility (MSVC)
// Also see: https://msdn.microsoft.com/en-us/library/ms177415.aspx
#define kp_debug(cond, ...) if(cond) {printf(__VA_ARGS__);} 
#define  LOGD(...) { printf("DEBUG: "); printf(__VA_ARGS__); printf("\n"); fflush(stdout);}
#define  LOGE(...) { printf("ERROR: "); printf(__VA_ARGS__); printf("\n");}
#else
// define kp_debug as a null macro so it has no code impact
#define kp_debug(...) ((void)0)
#define  LOGD(...) {;}
#define  LOGE(...) {;}
#endif

#define  LOGI(...) { printf("INFO: "); printf(__VA_ARGS__); printf("\n");}

#endif  /* KP_DEBUG_H */
