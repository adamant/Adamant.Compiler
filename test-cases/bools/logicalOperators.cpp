#include "RuntimeLibrary.hpp"

// Type Declarations

// Function Declarations
auto True_() -> bit;
auto main_() -> void;

// Class Declarations

// Global Definitions

// Definitions

auto True_() -> bit
{
	return bit__true;
}

auto main_() -> void
{
	bit x_;
	x_ = bit__op(bit__arg(bit__true) && bit__arg(bit__false));
	x_ = bit__op(bit__arg(bit__true) || bit__arg(bit__false));
	x_ = bit__op__not(bit__true);
	x_ = bit__op(bit__arg(True_()) || bit__arg(True_()));
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
