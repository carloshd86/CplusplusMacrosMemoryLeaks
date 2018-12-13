#include "stdafx.h"
#include "Test.h"

// Constructors

CTest::CTest(int foo)
{
	m_foo = foo;
}


// Public

int CTest::get_foo()
{
	return m_foo;
}

void CTest::set_foo(int foo)
{
	m_foo = foo;
}