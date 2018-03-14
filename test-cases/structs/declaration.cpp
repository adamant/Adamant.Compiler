#include "RuntimeLibrary.h"

// Type Declarations
struct Test_;

// Function Declarations
auto Main_() -> void;

// Class Declarations

struct Test_
{
public:
	Test_ * operator->() { return this; }
	Test_ const * operator->() const { return this; }
	Test_ & operator* () { return *this; }
	Test_ const & operator* () const { return *this; }
	p_string name_;
	Test_(p_string const name_);
	auto method_() const -> p_string;
};

// Global Definitions

// Definitions

::Test_::Test_(p_string const name_)
{
	this->name_ = name_;
}

auto ::Test_::method_() const -> p_string
{
	return name_;
}

auto Main_() -> void
{
	::Test_ const t_ = ::Test_(p_string("Bob"));
	t_.method_();
}

// Entry Point Adapter
std::int32_t main(int argc, char const *const * argv)
{
	try
	{
		Main_();
		return 0;
	}
	catch(std::exception &ex)
	{
		std::printf("Program exited due to error:\n");
		std::printf("%s", ex.what());
		return 70;
	}
}