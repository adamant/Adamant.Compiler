#include "RuntimeLibrary.hpp"

// Type Declarations
enum class day_of_week_;

// Function Declarations
auto main__0() -> void;

// Class Declarations

enum class day_of_week_
{
	Sunday_ = 0,
	Monday_ = 1,
	Tuesday_,
	Wednesday_,
	Thursday_,
	Friday_,
	Saturday_,
};

// Global Definitions

// Definitions

auto main__0() -> void
{
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
