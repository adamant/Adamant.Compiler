#include "RuntimeLibrary.h"
#include <map>

string::string()
	: Length(0), Buffer(0)
{
}

string::string(char c, int repeat)
	: Length(repeat)
{
	char* buffer = new char[repeat];
	for (int i = 0; i < repeat; i++)
		buffer[i] = c;

	Buffer = buffer;
}

string::string(const char* s)
	: Length(std::strlen(s)), Buffer(s)
{
}

string::string(int length, const char* s)
	: Length(length), Buffer(s)
{
}

char const * string::cstr() const
{
	auto buffer = new char[Length + 1];
	std::memcpy(buffer, Buffer, Length);
	buffer[Length] = 0;
	return buffer;
}

string string::Substring(int start, int length) const
{
	return string(length, Buffer + start);
}

string string::Replace(string oldValue, string newValue) const
{
	string buffer = "";
	int limit = Length - oldValue.Length + 1;
	int lastIndex = 0;
	for(int i=0; i < limit; i++)
		if (Substring(i, oldValue.Length) == oldValue)
		{
			buffer = buffer + Substring(lastIndex, i-lastIndex) + newValue;
			i += oldValue.Length; // skip over the value we just matched
			lastIndex = i;
			i--; // we need i-- to offset the i++ that is about to happen
		}

	buffer = buffer + Substring(lastIndex, Length - lastIndex);
	return buffer;
}

int string::LastIndexOf(char c) const
{
	for(int i=Length-1; i>=0; i--)
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
	int newLength = Length + value.Length;
	char* chars = new char[newLength];
	size_t offset = sizeof(char)*Length;
	std::memcpy(chars, Buffer, offset);
	std::memcpy(chars + offset, value.Buffer, value.Length);
	return string(newLength, chars);
}

string string::operator+(const char& value) const
{
	int newLength = Length + 1;
	char* chars = new char[newLength];
	size_t offset = sizeof(char)*Length;
	std::memcpy(chars, Buffer, offset);
	chars[Length] = value;
	return string(newLength, chars);
}

bool string::operator==(const string &other) const
{
	if (Length != other.Length)
		return false;

	for (int i = 0; i < Length; i++)
		if (Buffer[i] != other.Buffer[i])
			return false;

	return true;
}

bool operator < (string const& lhs, string const& rhs)
{
    return std::strcmp(lhs.cstr(), rhs.cstr()) < 0;
}

std::map<string, string> resourceValues;

string const & ResourceManager::GetString(string resourceName)
{
	return resourceValues.at(resourceName);
}
void ResourceManager::AddResource(string name, string value)
{
	resourceValues.insert(std::make_pair(name, value));
}

ResourceManager *const resource_manager = new ResourceManager();

namespace System
{
	namespace Console
	{
		void Console::Write(string value)
		{
			std::printf("%.*s", value.Length, value.Buffer);
		}

		void Console::WriteLine(string value)
		{
			std::printf("%.*s\n", value.Length, value.Buffer);
		}

		void Console::WriteLine()
		{
			std::printf("\n");
		}

		Arguments::Arguments(int argc, char const *const * argv)
			: Count(argc-1)
		{
			args = new string[Count];
			for (int i = 0; i < Count; i++)
				args[i] = string(argv[i+1]);
		}
	}

	namespace IO
	{
		FileReader::FileReader(const string& fileName)
		{
			std::FILE* foo;
			auto fname = fileName.cstr();
			file = std::fopen(fname, "rb");
			delete[] fname;
		}

		string FileReader::ReadToEndSync()
		{
			std::fseek(file, 0, SEEK_END);
			auto length = std::ftell(file);
			std::fseek(file, 0, SEEK_SET);
			auto buffer = new char[length];
			length = std::fread(buffer, sizeof(char), length, file);
			return string(length, buffer);
		}

		void FileReader::Close()
		{
			std::fclose(file);
		}

		FileWriter::FileWriter(const string& fileName)
		{
			auto fname = fileName.cstr();
			file = std::fopen(fname, "wb"); // TODO check error
			delete[] fname;
		}

		void FileWriter::Write(const string& value)
		{
			std::fwrite(value.Buffer, sizeof(char), value.Length, file);
		}

		void FileWriter::Close()
		{
			std::fclose(file);
		}
	}

	namespace Text
	{
		StringBuilder::StringBuilder(string const & value)
			: buffer(value)
		{
		}

		StringBuilder::StringBuilder()
			: buffer("")
		{
		}

		void StringBuilder::Append(string const & value)
		{
			buffer = buffer + value;
		}

		void StringBuilder::AppendLine(string const & value)
		{
			buffer = buffer + value + string("\n");
		}

		void StringBuilder::AppendLine()
		{
			buffer = buffer + string("\n");
		}
	}
}