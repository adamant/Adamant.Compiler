#include "runtime.h"

int Func(const int a, const int b)
{
	return b;
}

int Main()
{
	return Func(0, 42);
}

// Entry Point Adapter
int main(int argc, const char * argv[])
{
	return Main();
}
