#include "RuntimeLibrary.h"

// Type ID Declarations
enum Type_ID
{
	never__0Type_ID = 0,
};
typedef enum Type_ID Type_ID;

// Type Declarations

// Function Declarations
void mut main__1(system__console__Console__0 mut ref const console__);

// Class Declarations

// Global Definitions

// Definitions

void mut main__1(system__console__Console__0 mut ref const console__)
{
	Strings__0 mut ref const strings__ = Strings__0__0new__0(allocate(sizeof(Strings__0)));
	add_string__2(strings__, ((string){{5},(uint8_t*)u8"Hello"}));
	add_string__2(strings__, ((string){{6},(uint8_t*)u8"World!"}));
	if (cond(int32__0op__not_equal(strings__->count__, ((int32){2}))))
	{
		console_write_line__2(console__, ((string){{18},(uint8_t*)u8"List length not 2!"}));
	}

	console_write_line__2(console__, string__0op__add(((string){{11},(uint8_t*)u8"strings[0]="}), Strings__0__0op__element(strings__, ((int32){0}))));
	for (string__0iter mut iter = Strings__0__0iterate(strings__); string__0next(&iter);)
	{
		string const s__ = string__0current(&iter);
		console_write_line__2(console__, s__);
	}

	console_write_line__1(console__);
	clear_strings__1(strings__);
	system__collections__List__1 mut ref const builders__ = system__collections__List__1__0new__0(allocate(sizeof(system__collections__List__1)));
	add_item__2(builders__, system__text__String_Builder__0__0new__1(allocate(sizeof(system__text__String_Builder__0)), ((string){{7},(uint8_t*)u8"sb[0]: "})));
	add_item__2(builders__, system__text__String_Builder__0__0new__1(allocate(sizeof(system__text__String_Builder__0)), ((string){{7},(uint8_t*)u8"sb[1]: "})));
	for (void_ptr__0iter mut iter = system__collections__List__1__0iterate(builders__); void_ptr__0next(&iter);)
	{
		system__text__String_Builder__0 mut ref const sb__ = void_ptr__0current(&iter);
		sb_append__2(sb__, ((string){{5},(uint8_t*)u8"value"}));
	}

	for (void_ptr__0iter mut iter = system__collections__List__1__0iterate(builders__); void_ptr__0next(&iter);)
	{
		system__text__String_Builder__0 mut ref const sb__ = void_ptr__0current(&iter);
		console_write_line__2(console__, sb_to_string__1(sb__));
	}

	clear_list__1(builders__);
}

// Entry Point Adapter
int32_t main(int argc, char const ptr const ptr argv)
{
	main__1(allocate(sizeof(system__console__Console__0)));
	return 0;
}
