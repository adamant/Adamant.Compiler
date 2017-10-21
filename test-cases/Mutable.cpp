#include "RuntimeLibrary.h"

// Type Declarations

// Function Declarations
auto Func_(int x_, int const y_) -> ::System_::Text_::String_Builder_ *;
auto Main_(::System_::Console_::Console_ *const console_) -> void;

// Class Declarations

// Definitions

auto Func_(int x_, int const y_) -> ::System_::Text_::String_Builder_ *
{
	x_ += 1;
	int const i_ = x_ + 2;
	int j_ = y_ - 23;
	j_ = i_;
	::System_::Text_::String_Builder_ *const stringA_ = new ::System_::Text_::String_Builder_(string("Hello"));
	::System_::Text_::String_Builder_ const * stringB_;
	stringB_ = stringA_;
	return stringA_;
}

auto Main_(::System_::Console_::Console_ *const console_) -> void
{
	console_->WriteLine_(Func_(1, 2)->ToString_());
}

// Entry Point Adapter
int main(int argc, char const *const * argv)
{
	Main_(new ::System_::Console_::Console_());
	return 0;
}
