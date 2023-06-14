#include <thread>
#include <iostream>
#include <unistd.h>

#include "CriticalSection.hpp"
#include "CriticalSectionLock.hpp"

/*
 * This is a test program to test the CriticalSection class.
 */

using namespace std;

int a;
CriticalSection a_mutex;
int b;
CriticalSection b_mutex;
int c;
CriticalSection c_mutex;

int main(void)
{
	thread t1([]()
	{
		while (1)
		{
			CriticalSectionLock lock(a_mutex);
			a++;
			CriticalSectionLock lock2(b_mutex);
			b++;
			CriticalSectionLock lock3(c_mutex);
			c++;
			cout << "t1 done.\n";
		}
	});

	thread t2([]() {
		while (1)
		{
			CriticalSectionLock lock(c_mutex);
			c++;
			CriticalSectionLock lock2(b_mutex);
			b++;
			CriticalSectionLock lock3(a_mutex);
			a++;
			cout << "t2 done.\n";
		}
	});

	t1.join();
	t2.join();

	return 0;
}
