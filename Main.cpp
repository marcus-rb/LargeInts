// Note: /permissive- is disabled, however /Zc:referenceBinding an d/Zc:rvalueCast is not. This means /Zc:strictStrings is disabled
#include <iostream>

#include "LI_Raw.h"


int main() {
	using namespace LIPP;

	// UNIT TESTI NG OF CLASS INTEGER ARRAY

	// CONFIG

#define SHIFTS
#define DEFAULT

	// SETUP

	LIPP_UTIL::STATUS_CODE CHECK;

	#define LOGLAST(message) LIPP_UTIL::LogTask(message, CHECK); 


#ifdef DEFAULT

	LIPP::IntegerArray <LIPP::byte, 4> IntArray1(2546u);
	word32 IntArrayComp1 = 2546;

	CHECK = LIPP_UTIL::MemoryCompare(&IntArray1, &IntArrayComp1, 4);

	LOGLAST("Construction from integer");

#endif
// -------------------------------------
#ifdef SHIFTS

	IntegerArray <LIPP::word16, 4> ShiftArray1(3254632u);
	word64 ShiftArray1Comp = 3254632u;

	// shift right - below size of base unit (16)
	IntegerArray ShiftArrayRight1 = ShiftArray1 >> 6;
	word64 ShiftArrayRight1Comp = ShiftArray1Comp >> 6;

	CHECK = LIPP_UTIL::MemoryCompare(&ShiftArrayRight1, &ShiftArrayRight1Comp, 8);
	LOGLAST("Rightshift, less than base size");

	// shift right - more than size of base unit (16)
	IntegerArray ShiftArrayRight2 = ShiftArray1 >> 19;
	word64 ShiftArrayRight2Comp = ShiftArray1Comp >> 19;

	CHECK = LIPP_UTIL::MemoryCompare(&ShiftArrayRight2, &ShiftArrayRight2Comp, 8);
	LOGLAST("Rightshift, more than base size");

#endif

	std::cin.get();
}