#include "RuntimeLibrary.hpp"

// Type Declarations
typedef struct Test__0 Test__0;

// Function Declarations
Test__0 *_Nonnull Test__0__0new__0(Test__0 *_Nonnull self);
inline Test__0 *_Nonnull new_Test__0();
auto main__1(system__console__Console__0 *_Nonnull const console__) -> void;

// Class Declarations

struct Test__0
{
	bool__00 value__;
	auto change__1(bool__00 const value__) -> void;
};

// Global Definitions

// Definitions

auto ::Test__0::change__1(bool__00 const value__) -> void
{
	auto self = this;
	self->value__ = value__;
}

Test__0 *_Nonnull Test__0__0new__0(Test__0 *_Nonnull self) { return self; }

inline Test__0 *_Nonnull new_Test__0()
{
	return Test__0__0new__0(new Test__0());
}

auto main__1(system__console__Console__0 *_Nonnull const console__) -> void
{
	Test__0 *_Nonnull const test__ = new_Test__0();
	test__->change__1(true__00);
}

// Entry Point Adapter
std::int32_t main(int argc, char const *const * argv)
{
	try
	{
		main__1(new system__console__Console__0());
		return 0;
	}
	catch(std::exception &ex)
	{
		std::printf("Program exited due to error:\n");
		std::printf("%s", ex.what());
		return 70;
	}
}
