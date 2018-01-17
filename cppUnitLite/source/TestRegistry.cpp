

#include "TestFrame.h"
#include "TestResult.h"
#include "TestRegistry.h"
#include <stdio.h>

#ifdef __WIN32

	#include <windows.h>
	#include <io.h>
	#include <process.h>
	#include <direct.h>
#endif

void TestRegistry::addTest (Test *test) 
{
	instance ().add (test);
}


void TestRegistry::runAllTests (TestResult& result) 
{
	instance ().run (result);
}


TestRegistry& TestRegistry::instance () 
{
	static TestRegistry registry;
	return registry;
}


void TestRegistry::add (Test *test) 
{
	if (tests == 0) {
		tests = test;
		return;
	}
	
	test->setNext (tests);
	tests = test;
}


void TestRegistry::run (TestResult& result) 
{
	result.testsStarted ();

	for (Test *test = tests; test != 0; test = test->getNext ())
	{
		test->PrintName();
		test->run (result);
		//Sleep(10);
	}
	result.testsEnded ();
}



