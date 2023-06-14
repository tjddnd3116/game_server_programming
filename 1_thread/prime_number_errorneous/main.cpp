#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include <memory>

/*
 * 멀티스레드를 사용하여 소수 구하기
 * - 전역 변수 num을 만든다.
 * - 각 스레드는 num에서 값을 하나씩 가져와서 소수인지 판별한다.
 * - 소수이면 primes에 추가한다.
 * - 모든 스레드가 일을 마치고 나면 소수를 출력한다.
 *
 * 문제점
 * - num이라는 변수에 데이터 레이스가 발생한다.
 * - vector 재할당시 메모리의 주소가 변경되는데, 이때 다른 스레드가 접근하면 문제가 발생한다.
 */


using namespace std;
const int g_maxCount = 150000;
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
	vector<int> primes;
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

				n = num;
				num++;

				if (n >= g_maxCount)
					break;
				if (IsPrimeNumber(n))
				{
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

	auto t1 = chrono::system_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(t1 - t0).count();
	cout << "Took " << duration << " milliseconds" << endl;

	// PrintNumbers(primes);

	return 0;
}
