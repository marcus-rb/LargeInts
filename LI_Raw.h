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
//		[ ] Conversion from smaller largeint to largeInt. Eg from 128 to 256 bit conversion or cast
//		[ ] Equality operations

LARGEINT_BEGIN // namespace LargeIntPP {

// LargeInt Base class
template <LIPP_UTIL::LIPP_base_integral T, size_t S>
class IntegerArray {

public:

	using base_type = T;
	using base_ptr = T*;
	using base_ref = T&;
	using const_base_ptr = const T*;

	// *** Constructors ***
	IntegerArray(void) noexcept {}

	template <LIPP_UTIL::LIPP_base_integral T2>
	IntegerArray(T2 initial_value) noexcept {

		for (size_t i = 0; i < sizeof(T2); i++) {
			*(BYTE_PTR(m_InternalState) + i) = *(BYTE_PTR(&initial_value) + i);
		}

		#pragma warning (disable : 6294)
		for (size_t i = sizeof(T2); i < S * sizeof(T); i++) {
			*(BYTE_PTR(m_InternalState) + i) = 0;
		}
		#pragma warning (default : 6294)
	}

	// *** Info methods, utility, etc ***
	const base_ptr Raw() const {
		return m_InternalState;
	}

	template <LIPP_UTIL::Integer NewT>
	NewT CastToInteger() {
		return *(reinterpret_cast<NewT*>(m_InternalState));
	}

	// *** Bitwise operators ***

	IntegerArray operator>>(size_t amount) { // Right bit-shift
		return ShiftR(amount);
	}
	IntegerArray& operator>>=(size_t amount) {
		return ShiftR_IP(amount);
	}

	IntegerArray operator<<(size_t amount) {
		return ShiftL(amount);
	}
	IntegerArray& operator<<=(size_t amount) {
		return ShiftL_IP(amount);
	}

	IntegerArray operator|(const IntegerArray& other) {
		return BitOr(*this, other);
	}
	IntegerArray& operator|=(const IntegerArray& other) {
		return BitOrEq(other);
	}

	IntegerArray operator&(const IntegerArray& other) {
		return BitAnd(*this, other);
	};
	IntegerArray& operator&=(const IntegerArray& other) {
		return BitAndEq(other);
	}

	IntegerArray operator^(const IntegerArray& other) {
		return BitXor(*this, other);
	};
	IntegerArray& operator^=(const IntegerArray& other) {
		return BitXorEq(other);
	}

	IntegerArray operator~() {
		return BitNot(*this);
	}

	// *** Comparison ***
	bool operator==(const IntegerArray& other) {
		return Equal(other);
	}

	bool operator!=(const IntegerArray& other) {
		return !Equal(other);
	}

	bool operator>(const IntegerArray& other) {
		return Greater(other);
	}

	bool operator<(const IntegerArray& other) {
		return Less(other);
	}

	bool operator>=(const IntegerArray& other) {
		return GreaterOrEqual(other);
	}

	bool operator<=(const IntegerArray& other) {
		return LessOrEqual(other);
	}

	// *** Arithmetic ***
	IntegerArray operator+(const IntegerArray& other) {
		return Add(other);
	}

	IntegerArray operator-(const IntegerArray& other) {
		return Subtract(other);
	}

	IntegerArray operator*(const IntegerArray& other) {
		return Multiply(other);
	}

	IntegerArray operator/(const IntegerArray& other) {
		return Divide(other);
	}

private:
	// *** Bitwise ops ***

	// * SHIFTS *
	IntegerArray& ShiftL_IP(size_t amount) {
		
		if (amount > BITSIZE(T)) {
			size_t remainder = amount % BITSIZE(T);
			LIPP_UTIL::MoveRight<T, S>((amount - remainder) / BITSIZE(T), m_InternalState);
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
		IntegerArray temp = *this;
		return temp.ShiftL_IP(amount);
	}

	IntegerArray& ShiftR_IP(size_t amount) {
		if (amount > BITSIZE(T)) {
			size_t remainder = amount % BITSIZE(T);
			LIPP_UTIL::MoveLeft<T, S>((amount - remainder) / BITSIZE(T), m_InternalState);
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
		IntegerArray temp = *this;
		return temp.ShiftR_IP(amount);
	}

	// * BIT OR *
	IntegerArray BitOr(const IntegerArray& lhs, const IntegerArray& rhs) {
		IntegerArray temp = *this;

		for (size_t i = 0; i < S; i++) {
			temp.m_InternalState[i] = lhs.m_InternalState[i] | rhs.m_InternalState[i];
		}

		return temp;
	}

	IntegerArray& BitOrEq(const IntegerArray& other) {
		for (size_t i = 0; i < S; i++)
			m_InternalState[i] |= other.m_InternalState[i];

		return *this;
	}

	// * BIT AND *
	IntegerArray BitAnd(const IntegerArray& lhs, const IntegerArray& rhs) {
		IntegerArray temp = *this;

		for (size_t i = 0; i < S; i++) {
			temp.m_InternalState[i] = lhs.m_InternalState[i] & rhs.m_InternalState[i];
		}

		return temp;
	}

	IntegerArray& BitAndEq(const IntegerArray& other) {
		for (size_t i = 0; i < S; i++) {
			m_InternalState[i] &= other.m_InternalState[i];
		}

		return *this;
	}

	// * XOR *
	IntegerArray BitXor(const IntegerArray& lhs, const IntegerArray& rhs) {
		IntegerArray temp = *this;

		for (size_t i = 0; i < S; i++) {
			temp.m_InternalState[i] = lhs.m_InternalState[i] ^ rhs.m_InternalState[i];
		}

		return temp;
	}

	IntegerArray& BitXorEq(const IntegerArray& other) {
		for (size_t i = 0; i < S; i++)
			m_InternalState[i] ^= other.m_InternalState[i];

		return *this;
	}

	// * NOT *
	IntegerArray BitNot(IntegerArray operand) {
		for (size_t i = 0; i < S; i++)
			operand.m_InternalState[i] = ~operand.m_InternalState[i];

		return operand;
	}
	
	// *** Comparison ***

	bool Equal(const IntegerArray& other) {
		for (size_t i = 0; i < S; i++) {
			if (m_InternalState[i] != other.m_InternalState[i])
				return false;
		}

		return true;
	};

	bool NotEqual(const IntegerArray& other) {
		return !Equal(other);
	}

	bool Greater(const IntegerArray& other) {
		for (size_t i = S; i > 0; i--) {
				if (m_InternalState[i - 1] > other.m_InternalState[i - 1]) {
					return true;
				}
		}
		return false;
	};

	bool Less(const IntegerArray& other) {
		for (size_t i = S; i > 0; i--) {
			if (m_InternalState[i - 1] < other.m_InternalState[i - 1]) {
				return true;
			}
		}
		return false;
	};

	bool GreaterOrEqual(const IntegerArray& other) {
		return !Less(other);
	};

	bool LessOrEqual(const IntegerArray& other) {
		return !Greater(other);
	};

	// *** Arithmetic ***

	IntegerArray Add(const IntegerArray& other) {
		
		IntegerArray Result(0u);

		const_base_ptr data1 = m_InternalState;
		const_base_ptr data2 = other.m_InternalState;

		base_type OverflowCarry = 0; // Used for carrying bits through in between data storage units. 
		constexpr size_t UnitSize = sizeof(base_type);

		for (size_t i = 0; i < S; i++) {

			base_type Operand1 = *(data1 + i);
			base_type Operand2 = *(data2 + i);
			base_type LargestInCycle = LIPP_UTIL::Largest(Operand1, Operand2);

			// if transfering the overflow on this round causes undefined behaviour on built in types we must carry the overflow
			// to the next round
			while (Operand1 <= LIPP_UTIL::MAX_OF_T<base_type> && OverflowCarry > 0) {
				OverflowCarry--;
				Operand1++;
			}

			while (Operand2 != 0) {
				base_type Carry = Operand1 & Operand2;
				Operand1 ^= Operand2;
				Operand2 = Carry << 1;
			}

			if (LargestInCycle > Operand1) {
				OverflowCarry++;
			}

			Result.m_InternalState[i] = Operand1;

		}

		return Result;

	}

	IntegerArray Subtract(const IntegerArray& other) {

	}

	IntegerArray Multiply(const IntegerArray& other) {

	}

	IntegerArray Divide(const IntegerArray& other) {

	}

private:
	T m_InternalState[S];

};

#if 0
template <size_t S>
class IntegerArray<LIPP::word64, S> {
private:

	IntegerArray Add(const IntegerArray& other) {
		LIPP::word64 buffer;

		for (size_t S; i > 0; i--) {

		}
	}
};

#endif

LARGEINT_END // close brace } for namespace LargeIntPP