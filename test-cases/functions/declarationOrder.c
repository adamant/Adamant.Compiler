#include "RuntimeLibrary.h"

// Type Declarations

// Function Declarations
int32 mut main__0();
int32 mut Func__0();

// Class Declarations

// Global Definitions

// Definitions

int32 mut main__0()
{
	return Func__0();
}

int32 mut Func__0()
{
	return ((int32){42});
}

// Entry Point Adapter
int32_t main(int argc, char const ptr const ptr argv)
{
	return main__0().value;
}
