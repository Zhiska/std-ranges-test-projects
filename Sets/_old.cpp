#include <iostream>
#include <algorithm>
#include <list>
#include <array>

#include "Random.h"

#include "Timer.h"

std::vector<double> stA(200);
std::array<double, 300> stB;
std::list<double> stC(500);

int main() {
	Timer t;
	std::fill_n(stA.begin(), 100, 5.);
	std::generate_n(stA.rbegin(), 50, [n = 6.]() mutable { return n++; });
	std::generate_n(stA.begin(), 50, Random::Normalised);

	int k{};

	for (auto a : stB) {
		if (k % 4 == 0)
			a = k;
	}

	std::shuffle(stB.begin(), stB.end(), std::mt19937{ std::random_device{} ()});

	for (auto i = stC.begin(); i != stC.end(); ++i) {
		*i = Random::Coinflip();
	}

	std::reverse(stC.begin(), stC.end());

	std::vector<double> interV(stB.begin(), stB.end());

	std::sort(stA.begin(), stA.end());

	std::sort(stB.begin(), stB.end());
	stC.sort();

	std::vector<double> result;	
	std::set_union(stA.begin(), stA.end(), interV.begin(), interV.end(), std::back_inserter(result));

	interV.assign(stC.begin(), stC.end());
	stA.clear();
	std::set_symmetric_difference(result.begin(), result.end(), interV.begin(), interV.end(), std::back_inserter(stA));
}