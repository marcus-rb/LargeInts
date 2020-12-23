// Note: /permissive- is disabled, however /Zc:referenceBinding an d/Zc:rvalueCast is not. This means /Zc:strictStrings is disabled
#include <iostream>

#include "LI_Raw.h"

template <typename T>
class int32 {
public:

	int32(int arg) noexcept {
		for (int i = 0; i < SIZE_RATIO(int, T); i++) {
			m_data[i] = *((T*)&arg + i);
		}
	}

private:
	T m_data[sizeof(int) / sizeof(T)];
};

int main() {

	using namespace LIPP;

	LIPP::IntegerArray<LIPP::word16, 4> test(32745u); // left shifting this by 1 should give {1, 254}
	word32 testInt = 32745;

	word32 test2 = testInt << 3;
	IntegerArray testArray = test << 3;


	std::cin.get();
}