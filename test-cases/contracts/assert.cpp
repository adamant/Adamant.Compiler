#include "RuntimeLibrary.h"

// Type Declarations

// Function Declarations
auto Main_() -> void;

// Class Declarations

// Global Definitions

// Definitions

auto Main_() -> void
{
	p_int const x_ = p_int(5);
	p_int const y_ = p_int(5);
	p_int const z_ = p_int(6);
	assert_(x_.op_equal(y_), p_string("x=").op_add(x_)->op_add(p_string(" y="))->op_add(y_));
	assert_(y_.op_equal(z_), p_string("y=").op_add(y_)->op_add(p_string(" z="))->op_add(z_));
}

// Entry Point Adapter
std::int32_t main(int argc, char const *const * argv)
{
	try
	{
		Main_();
		return 0;
	}
	catch(std::exception &ex)
	{
		std::printf("Program exited due to error:\n");
		std::printf("%s", ex.what());
		return 70;
	}
}