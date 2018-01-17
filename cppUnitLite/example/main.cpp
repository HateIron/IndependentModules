#include "TestHarness.h"
#include <stdio.h>

TEST( Deque, construction)
{
	CHECK (1);
}
TEST( Deque2, construction)
{
	//CHECK_AND_SAVE (0,"good");
}
int main()
{
	printf("good start!\n");
	TestResult tr;
	TestRegistry::runAllTests(tr);	
	
	return 0;
}