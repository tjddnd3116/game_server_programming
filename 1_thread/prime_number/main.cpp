#include <vector>
#include <iostream>
#include <chrono>

/*
 * 싱글스레드를 사용하여 소수 구하기
 */

using namespace std;
const int g_maxCount = 150000;

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
	vector<int> primes;

	auto t0 = chrono::system_clock::now();

	for (int i = 1; i <= g_maxCount; i++)
	{
		if (IsPrimeNumber(i))
		{
			primes.push_back(i);
		}
	}
	auto t1 = chrono::system_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(t1 - t0).count();
	cout << "Took " << duration << " milliseconds" << endl;

	// PrintNumbers(primes);
	return 0;
}
