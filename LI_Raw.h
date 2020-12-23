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
	IntegerArray operator>>(size_t amount) {
		return ShiftR(amount);
	}

	IntegerArray operator<<(size_t amount) {
		return ShiftL(amount);
	}

private:
	// *** Bitwise ops ***
	IntegerArray ShiftL(size_t amount) {
		IntegerArray temp = *this;

		for (size_t i = 0; i < S - 1; i++) {
			temp.m_InternalState[i] <<= amount;
			temp.m_InternalState[i] |= ((LIPP_UTIL::MAX_OF_T<T> >> amount) & temp.m_InternalState[i + 1]) << amount;
		}
		temp.m_InternalState[S - 1] <<= amount;
		return temp;
	}

	IntegerArray ShiftR(size_t amount) {
		IntegerArray temp = *this;

		for (size_t i = 0; i < S - 1; i++) {
			temp.m_InternalState[i] >>= amount;
			temp.m_InternalState[i] |= (LIPP_UTIL::MAX_OF_T<T>) >> ((sizeof(T) << 3) - amount);
		}

		temp.m_InternalState[S - 1] >>= amount;

		#if 0
		for (size_t i = S - 1; i > 0; i--) {
			temp.m_InternalState[i] >>= amount;
			temp.m_InternalState[i] |= (LIPP_UTIL::MAX_OF_T<T>) >> ((sizeof(T) << 3) - amount);
		}
		#endif
		// last. No carry from previous set of bits
		//temp.m_InternalState[0] >>= amount;
		return temp;
	}

	IntegerArray BitOr(const IntegerArray& other) {

	}

	IntegerArray BitAnd(const IntegerArray& other) {

	}

	IntegerArray BitXor(const IntegerArray& other) {

	}

	IntegerArray BitNot() {

	}
	
	// *** Arithmetic ***

private:
	T m_InternalState[S];
};

LARGEINT_END // close brace } for namespace LargeIntPP