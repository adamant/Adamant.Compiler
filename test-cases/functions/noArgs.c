#include "RuntimeLibrary.h"

// Type Declarations

// Function Declarations
int32 Func__0();
int32 main__0();

// Class Declarations

// Global Definitions

// Definitions

int32 Func__0()
{
	return ((int32){42});
}

int32 main__0()
{
	return Func__0();
}

// Entry Point Adapter
int32_t main(int argc, char const *const * argv)
{
	return main__0().value;
}