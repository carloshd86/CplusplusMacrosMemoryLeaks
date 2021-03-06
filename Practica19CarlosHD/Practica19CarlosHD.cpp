// Practica19CarlosHD.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define MEMORY_LEAKS_MONITOR

#include "Test.h"
#include "MemoryLeaksMonitor.h"


int main()
{
	CTest * test1 = NEW(CTest);
	CTest * test2 = NEW(CTest);
	CTest * arr = NEW_ARRAY(CTest, 3);
	CTest * arr2 = NEW_ARRAY(CTest, 4);
	DELETE(test1);
	DELETE_ARRAY(arr);

#ifdef MEMORY_LEAKS_MONITOR
	PrintMemoryLeaks();		
#endif

    return 0;
}

