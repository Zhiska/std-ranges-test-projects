#include <iostream>
#include <vector>
#include <list>
#include <ranges>
#include <algorithm>
#include <random>
#include <numeric>

#include "Timer.h"
#include "Random.h"

using namespace std::ranges;

void SieveOfEratosthenes(int n, std::vector<bool>& vec, std::list<unsigned>& lst)
{

	const int size = n + 1;

	vec.reserve(size);
	vec.resize(size);	constexpr bool one = true;
	for (bool x : vec)
		x = true;

	for (int p = 2; p * p <= n; p++) {
		if (vec[p] == true) {
			for (int i = p * p; i <= n; i += p)
				*(vec.begin() + i) = false;
		}
	}

	std::vector<unsigned> temp;

	std::vector<unsigned> vals(size);
	for (unsigned i : views::iota(1) | views::take(n)) {
		if (vec[i])
			temp.push_back(vals[i]);
	}

	sample(temp.begin(), temp.end(), std::back_inserter(lst), temp.size() / 2, std::mt19937{ std::random_device{}() });
};

int main() {
	Timer t;

	int n = 10060;
	std::cout << "Following are the prime numbers smaller "
		<< " than or equal to " << n << std::endl;
	std::vector<bool> primeNet;
	std::list<unsigned> Primes;
	SieveOfEratosthenes(n, primeNet, Primes);

	return 0;
}