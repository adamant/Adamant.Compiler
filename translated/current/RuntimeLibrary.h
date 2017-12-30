// On windows this disables warnings about using fopen_s instead of fopen
// It must be defined before including the headers.
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <cstdio>
#include <cstdint>

template<typename T, typename F>
T LogicalAnd(T const & lhs, F rhs)
{
	return lhs.op_False().Value ? lhs : lhs.op_And(rhs());
}

template<typename T, typename F>
T LogicalOr(T const & lhs, F rhs)
{
	return lhs.op_True().Value ? lhs : lhs.op_Or(rhs());
}

struct p_bool
{
public:
	// Runtime Use Members
	bool Value;

	p_bool(): Value(false) {}
	p_bool(bool value): Value(value) {}
	p_bool * operator->() { return this; }
	p_bool const * operator->() const { return this; }
	p_bool & operator* () { return *this; }
	p_bool const & operator* () const { return *this; }

	// Adamant Members
	p_bool op_Not() const { return !this->Value; }
	p_bool op_True() const { return this->Value; }
	p_bool op_False() const { return !this->Value; }
	p_bool op_And(p_bool other) const { return this->Value & other.Value; }
	p_bool op_Or(p_bool other) const { return this->Value | other.Value; }
};

struct p_uint;

struct p_int
{
public:
	// Runtime Use Members
	std::int32_t Value;

	p_int(std::int32_t value): Value(value) {}
	p_int * operator->() { return this; }
	p_int const * operator->() const { return this; }
	p_int & operator* () { return *this; }
	p_int const & operator* () const { return *this; }

	// Hack to support conversion of uint to int for now
	p_int(p_uint value);

	// Adamant Members
	p_int(): Value(0) {}
	void op_PlusAssign(p_int other) { this->Value += other.Value; }
	void op_MinusAssign(p_int other) { this->Value -= other.Value; }
	p_bool op_Equal(p_int other) const { return this->Value == other.Value; }
	p_bool op_NotEqual(p_int other) const { return this->Value != other.Value; }
	p_bool op_LessThan(p_int other) const { return this->Value < other.Value; }
	p_bool op_LessThanOrEqual(p_int other) const { return this->Value <= other.Value; }
	p_bool op_GreaterThan(p_int other) const { return this->Value > other.Value; }
	p_bool op_GreaterThanOrEqual(p_int other) const { return this->Value >= other.Value; }
	p_int op_Plus(p_int other) const { return this->Value + other.Value; }
	p_int op_Minus(p_int other) const { return this->Value - other.Value; }
	p_int op_UnaryMinus() const { return -this->Value; }
	p_int op_Mod(p_int other) const { return this->Value % other.Value; }
	p_int op_Magnitude() const { if(this->Value==INT32_MIN) throw "Overflow exception"; return this->Value < 0 ? -this->Value : this->Value; }

	// Hack because we don't support as correctly yet
	p_uint AsUInt_() const;
};

struct p_uint
{
public:
	// Runtime Use Members
	std::uint32_t Value;

	p_uint(std::uint32_t value): Value(value) {}
	p_uint * operator->() { return this; }
	p_uint const * operator->() const { return this; }
	p_uint & operator* () { return *this; }
	p_uint const & operator* () const { return *this; }

	// Hack to support conversion of int to uint for now
	p_uint(p_int value): Value(value.Value) {}

	// Adamant Members
	p_uint(): Value(0) {}
	void op_PlusAssign(p_uint other) { this->Value += other.Value; }
	void op_MinusAssign(p_uint other) { this->Value -= other.Value; }
	p_bool op_Equal(p_uint other) const { return this->Value == other.Value; }
	p_bool op_NotEqual(p_uint other) const { return this->Value != other.Value; }
	p_bool op_LessThan(p_uint other) const { return this->Value < other.Value; }
	p_bool op_LessThanOrEqual(p_uint other) const { return this->Value <= other.Value; }
	p_bool op_GreaterThan(p_uint other) const { return this->Value > other.Value; }
	p_bool op_GreaterThanOrEqual(p_uint other) const { return this->Value >= other.Value; }
	p_uint op_Plus(p_uint other) const { return this->Value + other.Value; }
	p_uint op_Minus(p_uint other) const { return this->Value - other.Value; }
};

inline p_int::p_int(p_uint value)
	: Value(value.Value)
{
}

struct p_code_point
{
private:
	std::int32_t Value;

public:
	// Runtime Use Members
	p_code_point(): Value(0) {}
	p_code_point(char value): Value(value) {}
	p_code_point * operator->() { return this; }
	p_code_point const * operator->() const { return this; }
	p_code_point & operator* () { return *this; }
	p_code_point const & operator* () const { return *this; }
	char CharValue() const;

	// Adamant Members
	p_bool op_Equal(p_code_point const & other) const { return this->Value == other.Value; }
	p_bool op_NotEqual(p_code_point const & other) const { return this->Value != other.Value; }
	// TODO: Not sure code_point should support these operations
	p_bool op_LessThan(p_code_point other) const { return this->Value < other.Value; }
	p_bool op_LessThanOrEqual(p_code_point other) const { return this->Value <= other.Value; }
	p_bool op_GreaterThan(p_code_point other) const { return this->Value > other.Value; }
	p_bool op_GreaterThanOrEqual(p_code_point other) const { return this->Value >= other.Value; }

};

struct p_string
{
public:
	// Runtime Use Members
	char const * Buffer;

	p_string();
	p_string(char const * s);
	p_string(int length, char const * s);
	char const * cstr() const;
	p_string const * operator->() const { return this; }
	p_string const & operator* () const { return *this; }

	typedef char const * const_iterator;
	const_iterator begin() const { return &Buffer[0]; }
	const_iterator end() const { return &Buffer[Length_.Value]; }

	// Hack to support conversion of integers to strings for now
	p_string(p_int other);

	// Adamant Members
	p_int Length_;
	// TODO ByteLength this should be a property
	p_int ByteLength_() const { return this->Length_; }

	p_string(p_code_point c, p_int repeat);

	p_string Substring_(p_int start, p_int length) const;
	p_string Substring_(p_int start) const { return Substring_(start, Length_.Value-start.Value); }
	p_string Replace_(p_string oldValue, p_string newValue) const;
	p_int LastIndexOf_(p_code_point c) const;

	p_code_point op_Element(p_int const index) const { return Buffer[index.Value]; }
	p_string op_Plus(p_string const & value) const;
	p_bool op_Equal(p_string const & other) const;
	p_bool op_NotEqual(p_string const & other) const { return !this->op_Equal(other).Value; }
	p_bool op_LessThan(p_string other) const { return std::strcmp(this->cstr(), other.cstr()) < 0; }
	p_bool op_LessThanOrEqual(p_string other) const { return std::strcmp(this->cstr(), other.cstr()) <= 0; }
	p_bool op_GreaterThan(p_string other) const { return std::strcmp(this->cstr(), other.cstr()) > 0; }
	p_bool op_GreaterThanOrEqual(p_string other) const { return std::strcmp(this->cstr(), other.cstr()) >= 0; }
};

class ResourceManager
{
public:
	p_string const & GetString_(p_string resourceName);
	void AddResource(p_string name, p_string value);
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
			// Runtime Use Members
			typedef T const * const_iterator;
			const_iterator begin() const { return values; }
			const_iterator end() const { return &values[length]; }

			// Adamant Members
			List_() : values(0), length(0), capacity(0) { }
			void Add_(T value);
			p_int Length_() const { return length; }
			p_int op_Magnitude() const { return length; }
			T const & Get_(p_int const index) const { return values[index.Value]; }
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
			void Write_(p_string value);
			void WriteLine_(p_string value);
			void WriteLine_();
		};

		class Arguments_
		{
		private:
			p_string* args;
		public:
			// Runtime Use Members
			typedef p_string const * const_iterator;

			Arguments_(int argc, char const *const * argv);
			const_iterator begin() const { return &args[0]; }
			const_iterator end() const { return &args[Count_]; }

			// Adamant Members
			const int Count_;
			p_int op_Magnitude() const { return Count_; }
			p_string const & Get_(int const index) const { return args[index]; }
		};
	}

	namespace IO_
	{
		class File_Reader_
		{
		private:
			std::FILE* file;

		public:
			File_Reader_(const p_string& fileName);
			p_string ReadToEndSync_();
			void Close_();
		};

		class File_Writer_
		{
		private:
			std::FILE* file;

		public:
			File_Writer_(const p_string& fileName);
			void Write_(const p_string& value);
			void Close_();
		};
	}

	namespace Text_
	{
		class String_Builder_
		{
		private:
			p_string buffer;
		public:
			String_Builder_();
			String_Builder_(p_string const & value);
			void Append_(p_string const & value);
			void Append_(String_Builder_ const * value);
			void AppendLine_(p_string const& value);
			void AppendLine_();
			void Remove_(p_int start, p_int length);
			void Remove_(p_int start);
			p_string ToString_() const { return buffer; }
		};
	}
}