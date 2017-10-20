// On windows this disables warnings about using fopen_s instead of fopen
// It must be defined before including the headers.  The includes have been moved
// here to avoid leaking this into the program being compiled.  This required the
// use of void* instead of FILE* in some places.
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <cstdio>

struct string
{
public:
	int Length_;
	char const * Buffer;

	string();
	string(char c, int repeat);
	string(char const * s);
	string(int length, char const * s);
	char const * cstr() const;
	string Substring_(int start, int length) const;
	string Substring_(int start) const { return Substring_(start, Length_-start); }
	string Replace_(string oldValue, string newValue) const;
	int LastIndexOf_(char c) const;
	char operator[] (int const index) const;
	string operator+(string const & value) const;
	string operator+(char const & value) const;
	string const * operator->() const { return this; }
	string const & operator* () const { return *this; }
	bool operator==(string const & other) const;
	bool operator!=(string const & other) const { return !(*this == other); }
	friend bool operator<(string const & lhs, string const & rhs);

	typedef char const * const_iterator;
	const_iterator begin() const { return &Buffer[0]; }
	const_iterator end() const { return &Buffer[Length_]; }
};

class ResourceManager
{
public:
	string const & GetString_(string resourceName);
	void AddResource(string name, string value);
};

extern ResourceManager *const resource_manager_;

class NoneType
{
public:
	template<class T>
	operator T*() const { return static_cast<T*>(0); }
};
static const NoneType None = NoneType();

template<typename T>
struct Maybe
{
private:
	T data;
	bool hasValue;

public:
	Maybe(T const & value) : data(value), hasValue(true) {}
	Maybe(::NoneType const & none) : hasValue(false) {}
	T& operator->() { return data; }
	T const & operator->() const
	{
		if(!hasValue) throw "Access to null Maybe value";
		return data;
	}
	T  & operator* ()
	{
		if(!hasValue) throw "Access to null Maybe value";
		return data;
	}
	T const & operator* () const
	{
		if(!hasValue) throw "Access to null Maybe value";
		return data;
	}
	bool operator==(T const & other) const
	{
		return hasValue && data == other;
	}
	bool operator!=(T const & other) const
	{
		return hasValue && data != other;
	}
};

namespace System_
{
	namespace Collections_
	{
		template<typename T>
		class List_
		{
		private:
			T* values;
			int length;
			int capacity;

		public:
			typedef T const * const_iterator;

			List_() : values(0), length(0), capacity(0) { }
			void Add_(T value);
			int Length_() const { return length; }
			const_iterator begin() const { return values; }
			const_iterator end() const { return &values[length]; }
			T const & Get_(int const index) const { return values[index]; }
		};

		template<typename T>
		void List_<T>::Add_(T value)
		{
			if(length >= capacity)
			{
				int newCapacity = capacity == 0 ? 16 : capacity * 2;
				T* newValues = new T[newCapacity];
				std::memcpy(newValues, values, length * sizeof(T));
				values = newValues;
				capacity = newCapacity;
			}
			values[length] = value;
			length++;
		}
	}

	namespace Console_
	{
		class Console_
		{
		public:
			void Write_(string value);
			void WriteLine_(string value);
			void WriteLine_();
		};

		class Arguments_
		{
		private:
			string* args;
		public:
			typedef string const * const_iterator;
			const int Count_;

			Arguments_(int argc, char const *const * argv);
			const_iterator begin() const { return &args[0]; }
			const_iterator end() const { return &args[Count_]; }
			string const & Get_(int const index) const { return args[index]; }
		};
	}

	namespace IO_
	{
		class File_Reader_
		{
		private:
			std::FILE* file;

		public:
			File_Reader_(const string& fileName);
			string ReadToEndSync_();
			void Close_();
		};

		class File_Writer_
		{
		private:
			std::FILE* file;

		public:
			File_Writer_(const string& fileName);
			void Write_(const string& value);
			void Close_();
		};
	}

	namespace Text_
	{
		class String_Builder_
		{
		private:
			string buffer;
		public:
			String_Builder_();
			String_Builder_(string const & value);
			void Append_(string const & value);
			void Append_(String_Builder_ const * value);
			void AppendLine_(string const& value);
			void AppendLine_();
			string ToString_() const { return buffer; }
		};
	}
}
