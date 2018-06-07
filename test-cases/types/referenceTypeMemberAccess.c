#include "RuntimeLibrary.h"

// Type ID Declarations
enum Type_ID
{
	never__0Type__ID = 0,
	Test__0__0Type_ID,
};
typedef enum Type_ID Type_ID;

// Type Declarations
typedef struct Test__0 Test__0;

// Function Declarations
Test__0 mut ref mut Test__0__0new__0(Test__0 mut ref const self);
int32 mut main__0();

// Class Declarations

struct Test__0
{
	Type_ID type_id;
	int32 mut value__;
};

// Global Definitions

// Definitions

Test__0 mut ref mut Test__0__0new__0(Test__0 mut ref const self)
{
	self->type_id = Test__0__0Type_ID;
	self->value__ = ((int32){0});
	return self;
}

int32 mut main__0()
{
	Test__0 const ref const t__ = Test__0__0new__0(allocate(sizeof(Test__0)));
	return t__->value__;
}

// Entry Point Adapter
int32_t main(int argc, char const ptr const ptr argv)
{
	return main__0().value;
}
