#include "RuntimeLibrary.h"

// Type Declarations

// Function Declarations
auto Main_(::System_::Console_::Console_ *const console_) -> void;

// Class Declarations

// Definitions

auto Main_(::System_::Console_::Console_ *const console_) -> void
{
	::System_::Collections_::List_<string> *const strings_ = new ::System_::Collections_::List_<string>();
	strings_->Add_(string("Hello"));
	strings_->Add_(string("World!"));
	if (strings_->Length_() != 2)
	{
		console_->WriteLine_(string("List length not 2!"));
	}

	console_->WriteLine_(strings_->Get_(0));
	for (string const s_ : *(strings_))
	{
		console_->Write_(s_);
	}

	console_->WriteLine_();
	::System_::Collections_::List_<::System_::Text_::String_Builder_ *> *const builders_ = new ::System_::Collections_::List_<::System_::Text_::String_Builder_ *>();
	builders_->Add_(new ::System_::Text_::String_Builder_(string("sb[0]: ")));
	builders_->Add_(new ::System_::Text_::String_Builder_(string("sb[1]: ")));
	for (::System_::Text_::String_Builder_ *const sb_ : *(builders_))
	{
		sb_->Append_(string("value"));
	}

	for (::System_::Text_::String_Builder_ const *const sb_ : *(builders_))
	{
		console_->WriteLine_(sb_->ToString_());
	}
}

// Entry Point Adapter
int main(int argc, char const *const * argv)
{
	Main_(new ::System_::Console_::Console_());
	return 0;
}
