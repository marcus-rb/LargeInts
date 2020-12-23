/* ****** LargeIntPP library ******
 * 
 * LargeIntConfig.h header configuration file
 * 
 */

#pragma once

#define LARGEINT_BEGIN namespace LargeIntPP {
#define LARGEINT_END }

// Abbreviated namespace
#define LIPP LargeIntPP


// --- Use ONLY if IDE does not already include below preprocessor directives ---

#if 0 // SET TO 1 FOR WIN32 / X86 CONFIGURATION

#ifndef WIN32
#define WIN32
#endif

#endif

#if 0 // SET TO 1 FOR DEBUG CONFIGURATION

#ifndef _DEBUG
#define _DEBUG
#endif

#endif


// SET BASE UNIT FOR USE IN INTEGER ARRAY SETUP
#ifdef WIN32

typedef unsigned int LARGEINTBASE;

#else

typedef unsigned long long LARGEINTBASE;

#endif