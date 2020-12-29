#pragma once

/* --- LargeInt Raw header ---
 * 
 * Provides arithmetic on the underlying datastructure
 * used to store LargeInt-types
 * 
 */

#include "LargeIntConfig.h"
#include "LI_Utility.h"

// TODO
// [ ] Generic array type with necessary functionality
//		[ ]
//		[ ] 

LARGEINT_BEGIN // namespace LargeIntPP {

// LargeInt Base class
template <LIPP_UTIL::LIPP_base_integral T, size_t S>
class IntegerArray {

public:
	// *** Constructors ***
	IntegerArray(void) noexcept {}

	template <LIPP_UTIL::LIPP_base_integral T2>
	IntegerArray(T2 initial_value) noexcept {

		// mindfuck magic
		for (size_t i = 0; i < S*sizeof(T) / sizeof( T2 ); i++)
			m_InternalState[i] = *((T*)&initial_value + i);

		for (size_t i = S * sizeof(T) / sizeof(T2); i < S; i++)
			m_InternalState[i] = 0;

	}

	// *** Info methods, etc ***
	const T* Raw() const {
		return m_InternalState;
	}

	// *** Bitwise operators ***
	IntegerArray operator>>(size_t amount) { // Right bit-shift
		return ShiftR(amount);
	}

	IntegerArray operator<<(size_t amount) { // Left bit-shift
		return ShiftL(amount);
	}

	IntegerArray& operator<<=(size_t amount) {
		return ShiftL_IP(amount);
	}

private:
	// *** Helper functions ***

	// maybe these two can be a part of LIPP_UTIL
	inline void MoveLeft(size_t amount, T* data) {
		for (size_t i = 0; i < S - amount - 1; i++)
			*(data + i) = *(data + i + amount);

		for (size_t i = S - amount; i < S; i++)
			*(data + i) = 0;
	}

	inline void MoveRight(size_t amount, T* data) {

		for (size_t i = 0; i < S - amount; i++)
			*(data + S - 1 - i) = *(data + S - 1 - i - amount);

		for (size_t i = 0; i < amount; i++) {
			*(data + i) = 0;
		}

	}

	// *** Bitwise ops ***

	IntegerArray& ShiftL_IP(size_t amount) {
		
		if (amount > BITSIZE(T)) {
			size_t remainder = amount % BITSIZE(T);
			MoveRight((amount - remainder) / BITSIZE(T), m_InternalState);
			amount = remainder;
		}

		for (size_t i = S - 1; i > 0; i--) {
			m_InternalState[i] <<= amount;
			m_InternalState[i] |= ((~(LIPP_UTIL::MAX_OF_T<T> >> amount)) & m_InternalState[i - 1]) >> (BITSIZE(T) - amount);
		}

		m_InternalState[0] <<= amount;

		return *this;
	}

	IntegerArray ShiftL(size_t amount) {
		IntegerArray* temp = this;
		return temp->ShiftL_IP(amount);
	}

	IntegerArray& ShiftR_IP(size_t amount) {
		if (amount > BITSIZE(T)) {
			size_t remainder = amount % BITSIZE(T);
			MoveLeft((amount - remainder) / BITSIZE(T), m_InternalState);
			amount = remainder;
		}

		for (size_t i = 0; i < S - 1; i++) {
			m_InternalState[i] >>= amount;
			m_InternalState[i] |= ((~(LIPP_UTIL::MAX_OF_T<T> << amount)) & m_InternalState[i + 1]) << (BITSIZE(T) - amount);
		}

		m_InternalState[S - 1] >>= amount;

		return *this;
	}

	IntegerArray ShiftR(size_t amount) {

		IntegerArray* temp = this;

		return temp->ShiftR_IP(amount);
	}

	IntegerArray BitOr(const IntegerArray& lhs, const IntegerArray& rhs) {
		IntegerArray temp = *this;

		for (size_t i = 0; i < S; i++) {
			temp.m_InternalState[i] = lhs.m_InternalState[i] | rhs.m_InternalState[i];
		}

		return temp;
	}

	IntegerArray BitAnd(const IntegerArray& lhs, const IntegerArray& rhs) {
		IntegerArray temp = *this;

		for (size_t i = 0; i < S; i++) {
			temp.m_InternalState[i] = lhs.m_InternalState[i] & rhs.m_InternalState[i];
		}

		return temp;
	}

	IntegerArray BitXor(const IntegerArray& lhs, const IntegerArray& rhs) {
		IntegerArray temp = *this;

		for (size_t i = 0; i < S; i++) {
			temp.m_InternalState[i] = lhs.m_InternalState[i] ^ rhs.m_InternalState[i];
		}

		return temp;
	}

	IntegerArray BitNot(const IntegerArray operand) {
		for (size_t i = 0; i < S; i++)
			operand.m_InternalState[i] = ~operand.m_InternalState[i];

		return operand;
	}
	
	// *** Arithmetic ***

private:
	T m_InternalState[S];

};

LARGEINT_END // close brace } for namespace LargeIntPP