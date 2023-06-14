#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include <memory>
#include <mutex>
#include <unistd.h>

/*
 * 멀티스레드, 뮤텍스를 사용하여 소수 구하기
 * - 변수들을 보호하는 mutex를 만든다.
 */


using namespace std;
const int g_maxCount = 500000;
const int g_threadCount = 4;

bool IsPrimeNumber(int number)
{
	if (number == 1)
		return false;
	if (number == 2 || number == 3)
		return true;
	for (int i = 2; i < number - 1; i++)
	{
		if ((number % i) == 0)
			return false;
	}
	return true;
}

void PrintNumbers(const vector<int>& primes)
{
	for (int v : primes)
		cout << v << endl;
}

int main(void)
{
	int num = 1; // 각 스레드는 여기서 값을 꺼내온다.
	recursive_mutex num_mutex; // num을 보호하는 mutex

	vector<int> primes;
	recursive_mutex primes_mutex; // primes를 보호하는 mutex

	auto t0 = chrono::system_clock::now();
	vector<shared_ptr<thread> > threads; // 작동할 워커 스레드

	for (int i = 0; i < g_threadCount; i++)
	{
		shared_ptr<thread> thread(new class thread([&]() {
			// 각 스레드의 메인 함수
			// 값을 가져올 수 있으면 루프를 돈다.
			while (true)
			{
				int n;

				{
					lock_guard<recursive_mutex> num_lock(num_mutex);
					n = num;
					num++;
				}

				if (n >= g_maxCount)
					break;
				if (IsPrimeNumber(n))
				{
					lock_guard<recursive_mutex> primes_lock(primes_mutex);
					sleep(1);
					primes.push_back(n);
				}
			}
		}));
		threads.push_back(thread); // 스레드 객체를 일단 갖고 있는다.
	}

	for (auto thread: threads)
	{
		thread->join();
	}
	// end of threads

	auto t1 = chrono::system_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(t1 - t0).count();
	cout << "Took " << duration << " milliseconds" << endl;

	// PrintNumbers(primes);

	return 0;
}
