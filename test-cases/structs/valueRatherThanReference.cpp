#include "RuntimeLibrary.hpp"

// Type Declarations
typedef struct Reference_Type__0 Reference_Type__0;
typedef struct Value_Type__0 Value_Type__0;

// Function Declarations
Reference_Type__0 *_Nonnull Reference_Type__0__0new__0(Reference_Type__0 *_Nonnull self);
Value_Type__0 Value_Type__0__0new__0();
void main__0();

// Class Declarations

struct Reference_Type__0
{
};

struct Value_Type__0
{
};

// Global Definitions

// Definitions

Reference_Type__0 *_Nonnull Reference_Type__0__0new__0(Reference_Type__0 *_Nonnull self) { return self; }

Value_Type__0 Value_Type__0__0new__0() { return (Value_Type__0){}; }

void main__0()
{
	Reference_Type__0 const *_Nonnull const r__ = Reference_Type__0__0new__0(allocate(sizeof(Reference_Type__0)));
	Value_Type__0 const v__ = Value_Type__0__0new__0();
}

// Entry Point Adapter
int32_t main(int argc, char const *const * argv)
{
	main__0();
	return 0;
}
