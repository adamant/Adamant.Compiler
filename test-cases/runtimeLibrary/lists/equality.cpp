#include "RuntimeLibrary.hpp"

// Type Declarations

// Function Declarations
void main__0();

// Class Declarations

// Global Definitions

// Definitions

void main__0()
{
	system__collections__List__1<int32> const *_Nonnull const values__ = system__collections__List__1__0new__0<int32>(allocate(sizeof(system__collections__List__1<int32>)));
	equal_op(values__, values__);
	not_equal_op(values__, values__);
}

// Entry Point Adapter
int32_t main(int argc, char const *const * argv)
{
	main__0();
	return 0;
}