#include "RuntimeLibrary.h"

// Type ID Declarations
enum Type_ID
{
	never__0Type_ID = 0,
};
typedef enum Type_ID Type_ID;

// Type Declarations

// Function Declarations
int32 mut main__0();

// Class Declarations

// Global Definitions

// Definitions

int32 mut main__0()
{
	if (cond(FALSE))
	{
		return ((int32){0});
	}
	else if (cond(FALSE))
	{
		return ((int32){42});
	}
	else if (cond(FALSE))
	{
		return ((int32){10});
	}
	else
	{
		return ((int32){0});
	}
}

// Entry Point Adapter
int32_t main(int argc, char const ptr const ptr argv)
{
	return main__0().value;
}
