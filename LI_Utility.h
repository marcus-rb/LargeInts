#pragma once

#include <type_traits>

#include "LargeIntConfig.h"
#include "LI_Core.h"

#define LI_UTIL_BEGIN namespace LargeIntUtility {
#define LI_UTIL_END }

#define LIPP_UTIL LargeIntPP::LargeIntUtility

LARGEINT_BEGIN // nested namespace LargeIntPP::LargeIntUtility
LI_UTIL_BEGIN

// various typetraits

template <typename T>
struct is_LIPP_base_integral : public std::bool_constant< 
	std::is_same_v<T, LIPP::byte>	||
	std::is_same_v<T, LIPP::word16> ||
	std::is_same_v<T, LIPP::word32> || 
	std::is_same_v<T, LIPP::word64>> {};

template <typename T>
concept LIPP_base_integral = is_LIPP_base_integral<T>::value;

// *** Metafunctions for MAX of an integer_type ***
template<typename T>
constexpr T MAX_OF_T = 0;
template<>
constexpr LIPP::byte MAX_OF_T<LIPP::byte> = MAX_BYTE;

template<>
constexpr LIPP::word16 MAX_OF_T<LIPP::word16> = MAX_WORD16;

template<>
constexpr LIPP::word32 MAX_OF_T<LIPP::word32> = MAX_WORD32;

template<>
constexpr LIPP::word64 MAX_OF_T<LIPP::word64> = MAX_WORD64;

LI_UTIL_END
LARGEINT_END