// On windows this disables warnings about using fopen_s instead of fopen
// It must be defined before including the headers.
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

// TODO C: Consider using *_s versions of standard lib functions

// -----------------------------------------------------------------------------
// C++ Compatibility
// -----------------------------------------------------------------------------
// This section defines things that make C++ behave more like C so we can make
// the transition to C.
#ifdef __cplusplus

// Use `_Bool` as the native bool type
#define _Bool bool

// This type is used to emulate C style void pointers in C++. That is, they
// implictly convert to/from other pointer types.
class void_ptr
{
private:
    void *_Nullable ptr;
public:
    template<class T>
    void_ptr(T *_Nullable value) : ptr((void *_Nullable)value) {}
    template<class T>
    operator T *_Nullable() const { return (T *)ptr; }
    _Bool operator==(void_ptr rhs) const { return ptr == rhs.ptr; }
    template<class T>
    _Bool operator==(T *_Nullable rhs) const { return ptr == rhs; }
};

#else

#define void_ptr void*_Nullable

#endif

// -----------------------------------------------------------------------------
// Primitive Types
// -----------------------------------------------------------------------------

// `bool`
// For now, use `BOOL` as the emitted type
// TODO C: switch `BOOL` to `bool`
// TODO C: switch `TRUE` to `true`
// TODO C: switch `FALSE` to `false`
typedef struct BOOL BOOL;
struct BOOL
{
    _Bool value;
};

static const BOOL TRUE = { 1 };
static const BOOL FALSE = { 0 };

// Function used in conditions to make them take `bool`
inline _Bool cond(BOOL cond) { return cond.value; }

// Used by runtime for converting to bool
inline BOOL bool_from(_Bool v) { return (BOOL){ v }; }

// Wrap a bool operation that is bool based
inline BOOL bool_op(_Bool v) { return (BOOL){ v }; }
// Convert the arguments of a logical operation to bool
inline _Bool bool_arg(BOOL v) { return v.value; }

inline BOOL BOOL__0op__not(BOOL v) { return (BOOL){ !v.value }; }

// Need full definition of `bool` for these
#define assert__2(condition, message) assert__2__impl(condition, #condition, message, __FILE__, __LINE__)
#define assert__1(condition) assert__1__impl(condition, #condition, __FILE__, __LINE__)
#define lib_assert(condition) lib_assert_impl(condition, #condition, __FILE__)

typedef struct string string;

inline void assert__2__impl(const BOOL condition, char const *_Nonnull code, const string message, char const *_Nonnull file, const int32_t line);
inline void assert__1__impl(const BOOL condition, char const *_Nonnull code, char const *_Nonnull file, const int32_t line);
inline void lib_assert_impl(const _Bool condition, char const *_Nonnull code, char const *_Nonnull file);

// `never` type
struct never
{
};

// `never?` type
struct optional__never
{
};

typedef struct optional__BOOL optional__BOOL;
struct optional__BOOL
{
    BOOL has_value;
    union
    {
        never _;
        BOOL value;
    };
};

// TODO this is a hack for now, the type of `none` should be `never?`
static const void_ptr none = (void*)0;

template<typename T>
struct p_optional final
{
private:
    _Bool hasValue;
    union
    {
        T data;
    };

public:
    // TODO make this constructor explicit
    p_optional(T const & value) : data(value), hasValue(1) {}
    // TODO get rid of this conversion operator when compiler emits conversions
    p_optional(void_ptr value) : hasValue(0) {}
    auto has_value() const -> BOOL { return bool_from(hasValue); }
    auto value() const -> T { return data; }

    T & operator->()
    {
        lib_assert(hasValue);
        return data;
    }
    T const & operator->() const
    {
        lib_assert(hasValue);
        return data;
    }
    T & operator* ()
    {
        lib_assert(hasValue);
        return data;
    }
    T const & operator* () const
    {
        lib_assert(hasValue);
        return data;
    }
};

struct uint32;

// `int`
struct int32
{
    // Runtime Use Members
    int32_t value;

    explicit int32() = default;
    explicit int32(int32_t value): value(value) {}

    int32 *_Nonnull operator->() { return this; }
    int32 const *_Nonnull operator->() const { return this; }
    int32 & operator* () { return *this; }
    int32 const & operator* () const { return *this; }

    // Hack to support conversion of uint to int for now
    int32(uint32 value);

    // Adamant Members
    void op__add_assign(int32 other) { this->value += other.value; }
    void op__subtract_assign(int32 other) { this->value -= other.value; }
    BOOL op__less_than(int32 other) const { return bool_from(this->value < other.value); }
    BOOL op__less_than_or_equal(int32 other) const { return bool_from(this->value <= other.value); }
    BOOL op__greater_than(int32 other) const { return bool_from(this->value > other.value); }
    BOOL op__greater_than_or_equal(int32 other) const { return bool_from(this->value >= other.value); }
    int32 op__add(int32 other) const { return int32(this->value + other.value); }
    int32 op__subtract(int32 other) const { return int32(this->value - other.value); }
    int32 op__multiply(int32 other) const { return int32(this->value * other.value); }
    int32 op__divide(int32 other) const { return int32(this->value / other.value); }
    int32 op__remainder(int32 other) const { return int32(this->value % other.value); }
    int32 op__magnitude() const;

    // Hack because we don't support as correctly yet
    uint32 as_uint__0() const;
};

inline int32 int32__0op__negate(int32 v) { return int32(-v.value); }
inline BOOL int32__0op__less_than(int32 lhs, int32 rhs) { return bool_from(lhs.value < rhs.value); }
inline BOOL int32__0op__less_than_or_equal(int32 lhs, int32 rhs) { return bool_from(lhs.value <= rhs.value); }
inline BOOL int32__0op__greater_than(int32 lhs, int32 rhs) { return bool_from(lhs.value > rhs.value); }
inline BOOL int32__0op__greater_than_or_equal(int32 lhs, int32 rhs) { return bool_from(lhs.value >= rhs.value); }

// `uint`
struct uint32
{
    // Runtime Use Members
    uint32_t value;

    explicit uint32() = default;
    explicit uint32(uint32_t value): value(value) {}

    uint32 *_Nonnull operator->() { return this; }
    uint32 const *_Nonnull operator->() const { return this; }
    uint32 & operator* () { return *this; }
    uint32 const & operator* () const { return *this; }

    // Hack to support conversion of int to uint for now
    uint32(int32 value): value(value.value) {}

    // Adamant Members
    void op__add_assign(uint32 other) { this->value += other.value; }
    void op__subtract_assign(uint32 other) { this->value -= other.value; }
    BOOL op__less_than(uint32 other) const { return bool_from(this->value < other.value); }
    BOOL op__less_than_or_equal(uint32 other) const { return bool_from(this->value <= other.value); }
    BOOL op__greater_than(uint32 other) const { return bool_from(this->value > other.value); }
    BOOL op__greater_than_or_equal(uint32 other) const { return bool_from(this->value >= other.value); }
    uint32 op__add(uint32 other) const { return uint32(this->value + other.value); }
    uint32 op__subtract(uint32 other) const { return uint32(this->value - other.value); }
};

inline BOOL uint32__0op__less_than(uint32 lhs, uint32 rhs) { return bool_from(lhs.value < rhs.value); }
inline BOOL uint32__0op__less_than_or_equal(uint32 lhs, uint32 rhs) { return bool_from(lhs.value <= rhs.value); }
inline BOOL uint32__0op__greater_than(uint32 lhs, uint32 rhs) { return bool_from(lhs.value > rhs.value); }
inline BOOL uint32__0op__greater_than_or_equal(uint32 lhs, uint32 rhs) { return bool_from(lhs.value >= rhs.value); }

inline int32::int32(uint32 value)
    : value(value.value)
{
}

struct code_point
{
    uint32_t value;

    // Runtime Use Members
    explicit code_point() = default;
    explicit code_point(char value): value(value) {}

    code_point *_Nonnull operator->() { return this; }
    code_point const *_Nonnull operator->() const { return this; }
    code_point & operator* () { return *this; }
    code_point const & operator* () const { return *this; }
};

char code_point__to_char(code_point v);

// TODO: Not sure code_point should support comparision operations
inline BOOL code_point__0op__less_than(code_point lhs, code_point rhs) { return bool_from(lhs.value < rhs.value); }
inline BOOL code_point__0op__less_than_or_equal(code_point lhs, code_point rhs) { return bool_from(lhs.value <= rhs.value); }
inline BOOL code_point__0op__greater_than(code_point lhs, code_point rhs) { return bool_from(lhs.value > rhs.value); }
inline BOOL code_point__0op__greater_than_or_equal(code_point lhs, code_point rhs) { return bool_from(lhs.value >= rhs.value); }

struct string
{
    // Runtime Use Members
    char const *_Nonnull Buffer;
    int Length;

    explicit string() = default;
    explicit string(char const *_Nonnull s);
    explicit string(int length, char const *_Nonnull s);
    char const *_Nonnull cstr() const;
    string const *_Nonnull operator->() const { return this; }
    string const & operator* () const { return *this; }

    typedef char const *_Nonnull const_iterator;
    const_iterator begin() const { return &Buffer[0]; }
    const_iterator end() const { return &Buffer[Length]; }

    // Hack to support conversion of int and code_point to strings for now
    string(int32 other);
    string(code_point other);
    explicit string(BOOL other);

    // Adamant Members
    // TODO ByteLength should be a property
    int32 ByteLength__0() const { return int32(Length); }

    string Substring__2(int32 start, int32 length) const;
    string Substring__1(int32 start) const { return Substring__2(start, int32(Length-start.value)); }
    string Replace__2(string oldValue, string newValue) const;
    int32 LastIndexOf__1(code_point c) const;
    int32 index_of__1(code_point c) const;

    // TODO check index bounds
    code_point op__Element(int32 const index) const { return code_point(Buffer[index.value]); }
    string op__add(string const & value) const;
    string op__add(BOOL value) const { return this->op__add(string(value)); }
};

BOOL string__0op__less_than(string lhs, string rhs);
BOOL string__0op__less_than_or_equal(string lhs, string rhs);
BOOL string__0op__greater_than(string lhs, string rhs);
BOOL string__0op__greater_than_or_equal(string lhs, string rhs);

string string__0new__0();
string string__0new__1(string value);
string string__0new__2(code_point c, int32 repeat);


inline int32 int32::op__magnitude() const
{
    lib_assert(this->value!=INT32_MIN);
    return int32(this->value < 0 ? -this->value : this->value);
}

// -----------------------------------------------------------------------------
// Operators
// -----------------------------------------------------------------------------

inline BOOL equal_op(BOOL lhs, BOOL rhs)
{
    return bool_from(lhs.value == rhs.value);
}
inline BOOL equal_op(optional__BOOL lhs, optional__BOOL rhs)
{
    if(cond(lhs.has_value))
        return bool_op(bool_arg(rhs.has_value) && bool_arg(equal_op(lhs.value, rhs.value)));
    else
        return BOOL__0op__not(rhs.has_value);
}

inline BOOL equal_op(int32 lhs, int32 rhs)
{
    return bool_from(lhs.value == rhs.value);
}
inline BOOL equal_op(p_optional<int32> lhs, p_optional<int32> rhs)
{
    if(lhs.has_value().value)
        return bool_op(bool_arg(rhs.has_value()) && bool_arg(equal_op(lhs.value(), rhs.value())));
    else
        return BOOL__0op__not(rhs.has_value());
}

inline BOOL equal_op(void_ptr lhs, void_ptr rhs)
{
    return bool_from(lhs == rhs);
}

inline BOOL equal_op(code_point lhs, code_point rhs)
{
    return bool_from(lhs.value == rhs.value);
}

BOOL equal_op(string lhs, string rhs);

// TODO implement this without templates
template<typename T>
inline BOOL equal_op(T const *_Nullable lhs, void_ptr rhs)
{
    return bool_from(lhs == rhs);
}

// TODO implement this without templates
template<typename T>
inline BOOL equal_op(void_ptr lhs, T const *_Nullable rhs)
{
    return bool_from(lhs == rhs);
}

// TODO Get rid of this ability
template<typename T>
inline BOOL equal_op(T const *_Nullable lhs, T const *_Nullable const & rhs)
{
    return bool_from(lhs == 0);
}

inline BOOL not_equal_op(int32 lhs, int32 rhs)
{
    return bool_from(lhs.value != rhs.value);
}
inline BOOL not_equal_op(p_optional<int32> lhs, p_optional<int32> rhs)
{
    if(lhs.has_value().value)
        return bool_op(bool_arg(BOOL__0op__not(rhs.has_value())) || bool_arg(not_equal_op(lhs.value(), rhs.value())));
    else
        return rhs.has_value();
}

// TODO implement this without templates
template<typename T>
inline BOOL not_equal_op(T lhs, T  rhs)
{
    return BOOL__0op__not(equal_op(lhs, rhs));
}

// TODO implement this without templates
template<typename T>
inline BOOL not_equal_op(T const *_Nullable lhs, void_ptr rhs)
{
    return bool_from(lhs != rhs);
}

// TODO implement this without templates
template<typename T>
inline BOOL not_equal_op(void_ptr lhs, T const *_Nullable rhs)
{
    return bool_from(lhs != rhs);
}

// -----------------------------------------------------------------------------
// Standard Library
// -----------------------------------------------------------------------------
// Parts of the standard library that are currently implemented in the runtime.

// Version of allocate used directly by the runtime
inline void_ptr allocate(size_t bytes)
{
    return malloc(bytes);
}

inline void_ptr allocate__1(int32 bytes)
{
    return malloc(bytes.value);
}

inline void free__1(void_ptr object)
{
    free(object);
}

inline void assert__2__impl(const BOOL condition, char const *_Nonnull code, const string message, char const *_Nonnull file, const int32_t line)
{
    if(!condition.value)
    {
        printf("%s", string("Assertion failed: ").op__add(string(code)).op__add(string(", ")).op__add(message)
            .op__add(string(", file ")).op__add(string(file)).op__add(string(", line ")).op__add(int32(line)).cstr());
        exit(70);
    }
}

inline void assert__1__impl(const BOOL condition, char const *_Nonnull code, char const *_Nonnull file, const int32_t line)
{
    if(!condition.value)
    {
        printf("%s", string("Assertion failed: ").op__add(string(code))
            .op__add(string(", file ")).op__add(string(file)).op__add(string(", line ")).op__add(int32(line)).cstr());
        exit(70);
    }
}

inline void lib_assert_impl(const _Bool condition, char const *_Nonnull code, char const *_Nonnull file)
{
    if(!condition)
    {
        printf("%s", string("Assertion failed: ").op__add(string(code))
            .op__add(string(", file ")).op__add(string(file)).cstr());
        exit(70);
    }
}

_Noreturn inline void NOT_IMPLEMENTED(const string message, char const *_Nonnull function, char const *_Nonnull file, const int32_t line)
{
    printf("%s", string("Function ").op__add(string(function))
        .op__add(string(" not yet implemented, ")).op__add(message).op__add(string(", ")).op__add(string(file)).op__add(string(", line ")).op__add(int32(line)).cstr());
    exit(70);
}

_Noreturn inline void NOT_IMPLEMENTED(char const *_Nonnull function, char const *_Nonnull file, const int32_t line)
{
    printf("%s", string("Function ").op__add(string(function))
        .op__add(string(" not yet implemented, ")).op__add(string(file)).op__add(string(", line ")).op__add(int32(line)).cstr());
    exit(70);
}

#define NOT_IMPLEMENTED__1(message) NOT_IMPLEMENTED(message, __func__, __FILE__, __LINE__)
#define NOT_IMPLEMENTED__0() NOT_IMPLEMENTED(__func__, __FILE__, __LINE__)

_Noreturn inline void UNREACHABLE(char const *_Nonnull function, char const *_Nonnull file, const int32_t line)
{
    printf("%s", string("Reached \"UNREACHABLE\" statement in function ").op__add(string(function))
        .op__add(string(", ")).op__add(string(file)).op__add(string(", line ")).op__add(int32(line)).cstr());
    exit(70);
}

#define UNREACHABLE__0() UNREACHABLE(__func__, __FILE__, __LINE__)

class ResourceManager
{
public:
    string const & GetString__1(string resourceName);
    void AddResource(string name, string value);
};

extern ResourceManager *_Nonnull const resource_manager__;

void debug_write__1(string value);
void debug_write_line__1(string value);
void debug_write_line__0();

template<typename T>
struct system__collections__List__1
{
    T *_Nonnull values;
    int length;
    int capacity;

    // Runtime Use Members
    typedef T const *_Nonnull const_iterator;
    const_iterator begin() const { return values; }
    const_iterator end() const { return &values[length]; }

    // Adamant Members
    void add__1(T value);
    void clear__0() { length = 0; }
    int32 op__magnitude() const { return int32(length); }
    T const & op__Element(int32 const index) const;
};

template<typename T>
void system__collections__List__1<T>::add__1(T value)
{
    if(length >= capacity)
    {
        int newCapacity = capacity == 0 ? 16 : capacity * 2;
        // Allocate uninitalized buffer (note `sizeof(char) == 1` always)
        // Needed if T is a value type to avoid needing a default constructor
        T* newValues = (T*)new char[newCapacity * sizeof(T)];
        memcpy(newValues, values, length * sizeof(T));
        values = newValues;
        capacity = newCapacity;
    }
    values[length] = value;
    length++;
}

template<typename T>
T const & system__collections__List__1<T>::op__Element(int32 const index) const
{
    lib_assert(index.value >= 0 && index.value < length);
    return values[index.value];
}

template<typename T>
system__collections__List__1<T> *_Nonnull system__collections__List__1__0new__0(system__collections__List__1<T> *_Nonnull self)
{
    self->values = 0;
    self->length = 0;
    self->capacity = 0;
    return self;
}

class system__console__Console__0
{
public:
    void Write__1(string value);
    void WriteLine__1(string value);
    void WriteLine__0();
};

class system__console__Arguments__0
{
private:
    string *_Nonnull args;
public:
    // Runtime Use Members
    typedef string const *_Nonnull const_iterator;

    system__console__Arguments__0(int argc, char const *_Nonnull const *_Nonnull argv);
    const_iterator begin() const { return &args[0]; }
    const_iterator end() const { return &args[Count]; }

    const int Count;

    // Adamant Members
    int32 op__magnitude() const { return int32(Count); }
    string const & op__Element(int32 const index) const
    {
        lib_assert(index.value >= 0 && index.value < Count);
        return args[index.value];
    }
};

struct system__io__File_Reader__0
{
    FILE *_Nonnull file;

    string ReadToEndSync__0();
    void Close__0();
};

system__io__File_Reader__0 *_Nonnull system__io__File_Reader__0__0new__1(system__io__File_Reader__0 *_Nonnull self, const string& fileName);

struct system__io__File_Writer__0
{
    FILE *_Nonnull file;

    void Write__1(const string& value);
    void Close__0();
};

system__io__File_Writer__0 *_Nonnull system__io__File_Writer__0__0new__1(system__io__File_Writer__0 *_Nonnull self, const string& fileName);

struct system__text__String_Builder__0
{
    char *_Nullable buffer;
    int capacity;
    int length;
    void ensure_capacity(int needed);

    // Adamant Members
    // TODO byte_length should be a property
    int32 byte_length__0() const { return int32(length); }
    void Append__1(string const & value);
    void Append__1(system__text__String_Builder__0 const *_Nonnull value);
    void AppendLine__1(string const& value);
    void AppendLine__0();
    void Remove__2(int32 start, int32 length);
    void Remove__1(int32 start);
    string ToString__0();
};

inline system__text__String_Builder__0 *_Nonnull system__text__String_Builder__0__0new__0(system__text__String_Builder__0 *_Nonnull self)
{
    self->buffer = 0;
    self->capacity = 0;
    self->length = 0;
    return self;
}

system__text__String_Builder__0 *_Nonnull system__text__String_Builder__0__0new__1(system__text__String_Builder__0 *_Nonnull self, string const & value);
system__text__String_Builder__0 *_Nonnull system__text__String_Builder__0__0new__with_capacity__1(system__text__String_Builder__0 *_Nonnull self, int32 capacity);
