#include "RuntimeLibrary.h"

// Type ID Declarations
enum Type_ID
{
	never__0Type_ID = 0,
};
typedef enum Type_ID Type_ID;

// Type Declarations

// Function Declarations
void mut main__0();

// Class Declarations

// Global Definitions

// Definitions

void mut main__0()
{
	code_point mut result__;
	result__ = string__0__0op__element(((string){{5},(uint8_t*)u8"hello"}), ((int32){0}));
	result__ = string__0__0op__element(((string){{7},(uint8_t*)u8"goodbye"}), ((int32){4}));
}

// Entry Point Adapter
int32_t main(int argc, char const ptr const ptr argv)
{
	main__0();
	return 0;
}
