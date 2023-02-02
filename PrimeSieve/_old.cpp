#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <random>
#include <numeric>

#include "Timer.h"
#include "Random.h"
using namespace std;

void SieveOfEratosthenes(int n, vector<bool>& vec, list<unsigned>& lst)
{
	Timer t;

	const int size = n + 1;

	vec.reserve(size);
	vec.resize(size);
	fill(vec.begin(), vec.end(), true);

	for (int p = 2; p * p <= n; p++) {
		if (vec[p] == true) {
			for (int i = p * p; i <= n; i += p)
				*(vec.begin() + i) = false;
		}
	}

	vector<unsigned> vals(size);
	std::iota(vals.begin(), vals.end(), 1);

	int id{};

	std::vector<unsigned> temp;
	for (auto it(vec.begin()); it != vec.end(); it++) {
		if (*it)
			temp.push_back(*(vals.begin()+distance(vec.begin(), it)));
	}

	sample(temp.begin(), temp.end(), std::back_inserter(lst), temp.size() / 2, std::mt19937{std::random_device{}()});
};

int main() {

		int n = 6;
		cout << "Following are the prime numbers smaller "
			<< " than or equal to " << n << endl;
		vector<bool> primeNet;
		list<unsigned> Primes;
		SieveOfEratosthenes(n, primeNet, Primes);
		return 0;
}