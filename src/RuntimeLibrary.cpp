#include "RuntimeLibrary.h"
#include <map>

string::string()
	: Length_(0), Buffer(0)
{
}

string::string(char c, int repeat)
	: Length_(repeat)
{
	char* buffer = new char[repeat];
	for (int i = 0; i < repeat; i++)
		buffer[i] = c;

	Buffer = buffer;
}

string::string(const char* s)
	: Length_(std::strlen(s)), Buffer(s)
{
}

string::string(int length, const char* s)
	: Length_(length), Buffer(s)
{
}

char const * string::cstr() const
{
	auto buffer = new char[Length_ + 1];
	std::memcpy(buffer, Buffer, Length_);
	buffer[Length_] = 0;
	return buffer;
}

string string::Substring_(int start, int length) const
{
	return string(length, Buffer + start);
}

string string::Replace_(string oldValue, string newValue) const
{
	string buffer = "";
	int limit = Length_ - oldValue.Length_ + 1;
	int lastIndex = 0;
	for(int i=0; i < limit; i++)
		if (Substring_(i, oldValue.Length_) == oldValue)
		{
			buffer = buffer + Substring_(lastIndex, i-lastIndex) + newValue;
			i += oldValue.Length_; // skip over the value we just matched
			lastIndex = i;
			i--; // we need i-- to offset the i++ that is about to happen
		}

	buffer = buffer + Substring_(lastIndex, Length_ - lastIndex);
	return buffer;
}

int string::LastIndexOf_(char c) const
{
	for(int i=Length_-1; i>=0; i--)
		if(Buffer[i]==c)
			return i;

	return -1;
}

char string::operator[] (const int index) const
{
	return Buffer[index];
}

string string::operator+(const string& value) const
{
	int newLength = Length_ + value.Length_;
	char* chars = new char[newLength];
	size_t offset = sizeof(char)*Length_;
	std::memcpy(chars, Buffer, offset);
	std::memcpy(chars + offset, value.Buffer, value.Length_);
	return string(newLength, chars);
}

string string::operator+(const char& value) const
{
	int newLength = Length_ + 1;
	char* chars = new char[newLength];
	size_t offset = sizeof(char)*Length_;
	std::memcpy(chars, Buffer, offset);
	chars[Length_] = value;
	return string(newLength, chars);
}

bool string::operator==(const string &other) const
{
	if (Length_ != other.Length_)
		return false;

	for (int i = 0; i < Length_; i++)
		if (Buffer[i] != other.Buffer[i])
			return false;

	return true;
}

bool operator < (string const& lhs, string const& rhs)
{
    return std::strcmp(lhs.cstr(), rhs.cstr()) < 0;
}

std::map<string, string> resourceValues;

string const & ResourceManager::GetString_(string resourceName)
{
	return resourceValues.at(resourceName);
}
void ResourceManager::AddResource(string name, string value)
{
	resourceValues.insert(std::make_pair(name, value));
}

ResourceManager *const resource_manager_ = new ResourceManager();

namespace System_
{
	namespace Console_
	{
		void Console_::Write_(string value)
		{
			std::printf("%.*s", value.Length_, value.Buffer);
		}

		void Console_::WriteLine_(string value)
		{
			std::printf("%.*s\n", value.Length_, value.Buffer);
		}

		void Console_::WriteLine_()
		{
			std::printf("\n");
		}

		Arguments_::Arguments_(int argc, char const *const * argv)
			: Count_(argc-1)
		{
			args = new string[Count_];
			for (int i = 0; i < Count_; i++)
				args[i] = string(argv[i+1]);
		}
	}

	namespace IO_
	{
		File_Reader_::File_Reader_(const string& fileName)
		{
			std::FILE* foo;
			auto fname = fileName.cstr();
			file = std::fopen(fname, "rb");
			delete[] fname;
		}

		string File_Reader_::ReadToEndSync_()
		{
			std::fseek(file, 0, SEEK_END);
			auto length = std::ftell(file);
			std::fseek(file, 0, SEEK_SET);
			auto buffer = new char[length];
			length = std::fread(buffer, sizeof(char), length, file);
			return string(length, buffer);
		}

		void File_Reader_::Close_()
		{
			std::fclose(file);
		}

		File_Writer_::File_Writer_(const string& fileName)
		{
			auto fname = fileName.cstr();
			file = std::fopen(fname, "wb"); // TODO check error
			delete[] fname;
		}

		void File_Writer_::Write_(const string& value)
		{
			std::fwrite(value.Buffer, sizeof(char), value.Length_, file);
		}

		void File_Writer_::Close_()
		{
			std::fclose(file);
		}
	}

	namespace Text_
	{
		String_Builder_::String_Builder_(string const & value)
			: buffer(value)
		{
		}

		String_Builder_::String_Builder_()
			: buffer("")
		{
		}

		void String_Builder_::Append_(string const & value)
		{
			buffer = buffer + value;
		}

		void String_Builder_::Append_(String_Builder_ const * value)
		{
			buffer = buffer + value->buffer;
		}

		void String_Builder_::AppendLine_(string const & value)
		{
			buffer = buffer + value + string("\n");
		}

		void String_Builder_::AppendLine_()
		{
			buffer = buffer + string("\n");
		}
	}
}
