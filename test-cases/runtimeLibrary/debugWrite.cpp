#include "RuntimeLibrary.hpp"

// Type Declarations

// Function Declarations
auto main__0() -> void;

// Class Declarations

// Global Definitions

// Definitions

auto main__0() -> void
{
	debug_write__1(string("prefix: "));
	debug_write_line__1(string("value"));
	debug_write_line__0();
	debug_write_line__1(string("eom"));
}

// Entry Point Adapter
std::int32_t main(int argc, char const *const * argv)
{
	try
	{
		main__0();
		return 0;
	}
	catch(std::exception &ex)
	{
		std::printf("Program exited due to error:\n");
		std::printf("%s", ex.what());
		return 70;
	}
}
