#include "RuntimeLibrary.hpp"

// Type Declarations

// Function Declarations
auto main_() -> void;

// Class Declarations

// Global Definitions

// Definitions

auto main_() -> void
{
	bit x_;
	x_ = code_point__op__less_than(code_point('a'), code_point('b'));
	x_ = code_point__op__less_than_or_equal(code_point('a'), code_point('b'));
	x_ = code_point__op__greater_than(code_point('a'), code_point('b'));
	x_ = code_point__op__greater_than_or_equal(code_point('a'), code_point('b'));
}

// Entry Point Adapter
std::int32_t main(int argc, char const *const * argv)
{
	try
	{
		main_();
		return 0;
	}
	catch(std::exception &ex)
	{
		std::printf("Program exited due to error:\n");
		std::printf("%s", ex.what());
		return 70;
	}
}
