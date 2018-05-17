#include "RuntimeLibrary.hpp"

// Type Declarations
typedef struct Test__0 Test__0;

// Function Declarations
Test__0 *_Nonnull Test__0__0new__0(Test__0 *_Nonnull self);
inline Test__0 *_Nonnull new_Test__0();
auto main__0() -> int__00;

// Class Declarations

struct Test__0
{
	int__00 value__;
};

// Global Definitions

// Definitions

Test__0 *_Nonnull Test__0__0new__0(Test__0 *_Nonnull self)
{
	self->value__ = int__00(0);
	return self;
}

inline Test__0 *_Nonnull new_Test__0()
{
	return Test__0__0new__0(new Test__0());
}

auto main__0() -> int__00
{
	Test__0 const *_Nonnull const t__ = new_Test__0();
	return t__->value__;
}

// Entry Point Adapter
std::int32_t main(int argc, char const *const * argv)
{
	try
	{
		return main__0().value;
	}
	catch(std::exception &ex)
	{
		std::printf("Program exited due to error:\n");
		std::printf("%s", ex.what());
		return 70;
	}
}
