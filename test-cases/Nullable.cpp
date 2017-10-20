#include "RuntimeLibrary.h"

// Type Declarations

// Function Declarations
auto Func_(::Maybe<string> const x_, ::Maybe<unsigned int> const y_) -> ::Maybe<int>;
auto Main_(::System_::Console_::Console_ *const console_) -> void;

// Class Declarations

// Definitions

auto Func_(::Maybe<string> const x_, ::Maybe<unsigned int> const y_) -> ::Maybe<int>
{
	::Maybe<int> const z_ = ::None;
	::System_::Text_::String_Builder_ const *const s_ = ::None;
	return ::None;
}

auto Main_(::System_::Console_::Console_ *const console_) -> void
{
	Func_(::None, ::None);
}

// Entry Point Adapter
int main(int argc, char const *const * argv)
{
	Main_(new ::System_::Console_::Console_());
	return 0;
}
