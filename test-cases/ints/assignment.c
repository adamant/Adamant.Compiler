#include "RuntimeLibrary.h"

// Type Declarations

// Function Declarations
int32 mut main__0();

// Class Declarations

// Global Definitions

// Definitions

int32 mut main__0()
{
	int32 mut result__;
	result__ = ((int32){40});
	op__add_assign(&(result__), ((int32){3}));
	op__sub_assign(&(result__), ((int32){1}));
	return result__;
}

// Entry Point Adapter
int32_t main(int argc, char const ptr const ptr argv)
{
	return main__0().value;
}
