/* ----- LARGE INT C++ LIBRARY ----- *
 * A C++ Library to work with larger than 64-bit integers
 * First edit/inital file: December 13th 2020
 * Last update: December 13th 2020
 * 
 * Project amibition:
 * - Integrate 128 to 2048 bit integers that operate seeminlgy just like built in integral speeds. 
 * - Is most easily done by combining arrays of X bits. Maybe 64 bits for x64 and 32 bits for x86. 
 * 
 * Build and error messages:
 * - Check LargeIntConfig.h to see if you need 
 */

#include "LargeIntConfig.h"

LARGEINT_BEGIN // namespace LargeInt {

// PLATFORM WINDOWS 32-BIT
#ifdef WIN32 

#define BASE_WORD_SIZE 4

// PLATFORM WINDOWS 64-BIT
#else

#define BASE_WORD_SIZE 8

#endif



LARGEINT_END // end brace for namespace LargeInt ( "}" )