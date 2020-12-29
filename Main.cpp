// Note: /permissive- is disabled, however /Zc:referenceBinding an d/Zc:rvalueCast is not. This means /Zc:strictStrings is disabled
#include <iostream>

#include "LI_Raw.h"


int main() {
	using namespace LIPP;

	// UNIT TESTING OF CLASS INTEGER ARRAY

	// CONFIG

	#define DEFAULT 1
	#define SHIFTS 1
	#define BITOPS 1

	// SETUP

	LIPP_UTIL::STATUS_CODE CHECK;

	#define LOGLAST(message) LIPP_UTIL::LogTask(message, CHECK)
	#define LOGSEC(sec) std::cout << "\n===== " << sec << " =====" << std::endl
	#define COMPARE(op1, op2, size) CHECK = LIPP_UTIL::MemoryCompare(&op1, &op2, size)

#if DEFAULT == 1
		LOGSEC("DEFAULT");

		LIPP::IntegerArray <LIPP::byte, 8> IntArray1(MAX_WORD64);
		word64 IntArrayComp1 = MAX_WORD64;

		COMPARE(IntArray1, IntArrayComp1, 4);
		LOGLAST("Construction from integer");
#endif
// -------------------------------------
#if SHIFTS == 1

	LOGSEC("SHIFTS");

	#define LEFTSHIFTS 1
	#define RIGHTSHIFTS 1

	IntegerArray <LIPP::word16, 4> ShiftArray1(3222632u);
	word64 ShiftArray1Comp = 3222632u;

	#if RIGHTSHIFTS == 1

	// shift right - below size of base unit (16)
	IntegerArray ShiftArrayRight1 = ShiftArray1 >> 6;
	word64 ShiftArrayRight1Comp = ShiftArray1Comp >> 6;

	COMPARE(ShiftArrayRight1, ShiftArrayRight1Comp, 8);
	LOGLAST("Right shift, less than base size");

	// shift right - more than size of base unit (16)
	IntegerArray ShiftArrayRight2 = ShiftArray1 >> 19;
	word64 ShiftArrayRight2Comp = ShiftArray1Comp >> 19;

	COMPARE(ShiftArrayRight2, ShiftArrayRight2Comp, 8);
	LOGLAST("Right shift, more than base size");

	#endif


	#if LEFTSHIFTS == 1

	// shift left - below size of base unit (16)
	IntegerArray ShiftArrayLeft1 = ShiftArray1 << 6;
	word64 ShiftArrayLeft1Comp = ShiftArray1Comp << 6;

	COMPARE(ShiftArrayLeft1, ShiftArrayLeft1Comp, 8);
	LOGLAST("Left shift, less than base size");

	IntegerArray ShiftArrayLeft2 = ShiftArray1 << 19;
	word64 ShiftArrayLeft2Comp = ShiftArray1Comp << 19;

	COMPARE(ShiftArrayLeft2, ShiftArrayLeft2Comp, 8);
	LOGLAST("Left shift, more than base size");

	#endif

#endif

#if BITOPS == 1
	
	#define BITOR 1
	#define BITAND 1
	#define BITXOR 1
	#define BITNOT 1

	LOGSEC("BITWISE OPERATIONS");

	IntegerArray<LIPP::byte, 4> BitOps1(0b10101010010111101101110101110u);
	IntegerArray<LIPP::byte, 4> BitOps2(0b10001111101111110111111011111u);
	word32 BitOps1Comp = 0b10101010010111101101110101110u;
	word32 BitOps2Comp = 0b10001111101111110111111011111u;

	// |, |=, &, &=, ^, ^=, ~
	#if BITOR == 1
	
	IntegerArray BitOpsOr = BitOps1 | BitOps2;
	word32 BitOpsOrComp = BitOps1Comp | BitOps2Comp;
	COMPARE(BitOpsOr, BitOpsOrComp, 4);
	LOGLAST("Bitwise or");
	

	IntegerArray BitOpsOrEqual = BitOps1;
	BitOpsOrEqual |= BitOps2;

	COMPARE(BitOpsOrComp, BitOpsOrEqual, 4);
	LOGLAST("Bitwise or equals");

	#endif

	#if BITAND == 1

	IntegerArray BitOpsAnd = BitOps1 & BitOps2;
	word32 BitOpsAndComp = BitOps1Comp & BitOps2Comp;

	COMPARE(BitOpsAnd, BitOpsAndComp, 4);
	LOGLAST("Bitwise and");

	IntegerArray BitOpsAndEqual = BitOps1;
	BitOpsAndEqual &= BitOps2;

	COMPARE(BitOpsAndEqual, BitOpsAndComp, 4);
	LOGLAST("Bitwise and equal");

	#endif

	#if BITXOR == 1

	IntegerArray BitOpsXor = BitOps1 ^ BitOps2;
	word32 BitOpsXorComp = BitOps1Comp ^ BitOps2Comp;

	COMPARE(BitOpsXor, BitOpsXorComp, 4);
	LOGLAST("Bit xor");

	IntegerArray BitOpsXorEqual = BitOps1;
	BitOpsXorEqual ^= BitOps2;

	COMPARE(BitOpsXorEqual, BitOpsXorComp, 4);
	LOGLAST("Bit xor equals");

	#endif

	#if BITNOT == 1

	IntegerArray BitOpsNot = ~BitOps1;
	word32 BitOpsNotComp = ~BitOps1Comp;

	COMPARE(BitOpsNot, BitOpsNotComp, 4);
	LOGLAST("Bitwise not");

	#endif

#endif

	std::cin.get();
}