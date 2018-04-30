#include "RuntimeLibrary.hpp"

// Type Declarations

// Function Declarations
auto Func_(i32 x_, i32 const y_) -> ::System_::Text_::String_Builder_ *_Nonnull;
auto Main_(::System_::Console_::Console_ *_Nonnull const console_) -> void;

// Class Declarations

// Global Definitions

// Definitions

auto Func_(i32 x_, i32 const y_) -> ::System_::Text_::String_Builder_ *_Nonnull
{
	x_.op_add_assign(i32(1));
	i32 const i_ = x_.op_add(i32(2));
	i32 j_ = y_.op_subtract(i32(23));
	j_ = i_;
	::System_::Text_::String_Builder_ *_Nonnull const stringA_ = (new ::System_::Text_::String_Builder_())->construct(p_string("Hello"));
	::System_::Text_::String_Builder_ const *_Nonnull stringB_;
	stringB_ = stringA_;
	return stringA_;
}

auto Main_(::System_::Console_::Console_ *_Nonnull const console_) -> void
{
	console_->WriteLine_(Func_(i32(1), i32(2))->ToString_());
}

// Entry Point Adapter
std::int32_t main(int argc, char const *const * argv)
{
	try
	{
		Main_(new ::System_::Console_::Console_());
		return 0;
	}
	catch(std::exception &ex)
	{
		std::printf("Program exited due to error:\n");
		std::printf("%s", ex.what());
		return 70;
	}
}