#ifndef _TEST_H_
#define _TEST_H_

class CTest
{ 
	public:
		CTest(int foo = 0);

		int get_foo();
		void set_foo(int foo);

	private:
		int m_foo;
};

#endif