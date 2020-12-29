/* ****** LargeIntPP library ******
 *
 * LI_Core.h header - lib typedefs, constants, etc.
 *
 */

#pragma once

#include <cstdint>

#include "LargeIntConfig.h"

// *** MACROS ***

#define SIZE_RATIO(x, y) (sizeof(x) / sizeof(y))
#define BITSIZE(T) (sizeof(T)*8)

#define BYTE_PTR(ptr) (const_cast<LIPP::byte*>(reinterpret_cast<const LIPP::byte*>(ptr)))

// *** NAMESPACES ***

#define INTERNAL_BEGIN namespace Internal {
#define INTERNAL_END }

#define LIPP_INTERNAL LIPP::Internal

LARGEINT_BEGIN

// *** TYPEDEFS ***

typedef uint8_t byte;
typedef uint16_t word16;
typedef uint32_t word32;
typedef uint64_t word64;

// *** CONSTANTS ***

constexpr byte MAX_BYTE = 255U;
constexpr word16 MAX_WORD16 = 65535U;
constexpr word32 MAX_WORD32 = 4'294'967'295U;
constexpr word64 MAX_WORD64 = 18'446'744'073'709'551'615ULL;

LARGEINT_END 