#pragma once

#include <type_traits>

#include "LargeIntConfig.h"
#include "LI_Core.h"

#define LI_UTIL_BEGIN namespace Utility {
#define LI_UTIL_END }

#define LIPP_UTIL LargeIntPP::Utility

LARGEINT_BEGIN // nested namespace LargeIntPP::Utility
LI_UTIL_BEGIN

// debug utility

enum STATUS_CODE {
	STATUS_SUCCESS, STATUS_FAIL
};

STATUS_CODE MakeStatus(bool code) {
	return code ? STATUS_CODE::STATUS_SUCCESS : STATUS_CODE::STATUS_FAIL;
}

#pragma warning(disable : 26812)

std::ostream& operator<<(std::ostream& stream, const STATUS_CODE& input) {
	if (!input) {
		stream << "SUCCESS";
	}
	else {
		stream << "FAIL";
	}
	return stream;
}

#pragma warning(default : 26812)

void LogTask(const char* taskname, STATUS_CODE code) {
	std::cout << taskname << ": " << code << std::endl;
}

template <typename T1, typename T2>
STATUS_CODE MemoryCompare(T1* ptr1, T2* ptr2, size_t byte_size) {
	STATUS_CODE result = STATUS_SUCCESS;

	for (size_t i = 0; i < byte_size; i++) {
		if ( *(BYTE_PTR(ptr1) + i) != *(BYTE_PTR(ptr2) + i) )
			result = STATUS_FAIL;
	}

	return result;
}


// operating on data
template <typename T, size_t ArraySize>
inline void MoveLeft(size_t amount, T* data) {
	for (size_t i = 0; i < ArraySize - amount - 1; i++)
		*(data + i) = *(data + i + amount);

	for (size_t i = ArraySize - amount; i < ArraySize; i++)
		*(data + i) = 0;
}

template <typename T, size_t ArraySize>
inline void MoveRight(size_t amount, T* data) {
	for (size_t i = 0; i < ArraySize - amount; i++)
		*(data + ArraySize - 1 - i) = *(data + ArraySize - 1 - i - amount);

	for (size_t i = 0; i < amount; i++) 
		*(data + i) = 0;

}

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