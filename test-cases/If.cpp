#include "runtime.h"

int Main()
{
	if (true)
	{
		return 0;
	}
}

// Entry Point Adapter
int main(int argc, const char * argv[])
{
	return Main();
}
