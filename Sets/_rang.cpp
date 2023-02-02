#include <iostream>
#include <algorithm>
#include <ranges>
#include <list>
#include <array>

#include "Random.h"

#include "Timer.h"

std::vector<double> stA(20);
std::array<double, 30> stB;
std::list<double> stC(50);

namespace rge = std::ranges;

int main() {
	Timer t;
	rge::fill_n(stA.begin(), 10, 5.);
	rge::generate_n(stA.rbegin(), 5, [n = 6.]() mutable { return n++; });
	rge::generate_n(stA.begin(), 5, Random::Normalised);

	int k{};
	for (auto a : stB) {
		if (k % 4 == 0)
			a = k;
	}
	std::shuffle(stB.begin(), stB.end(), std::mt19937{std::random_device{}()});

	for (auto i = stC.begin(); i != stC.end(); ++i) {
		*i = Random::Coinflip();
	}
	rge::reverse(stC.begin(), stC.end());

	std::vector<double> interV(stB.begin(), stB.end());	

	rge::sort(stA);
	rge::sort(stB);
	stC.sort();

	std::vector<double> result;
	rge::set_union(stA, interV, std::back_inserter(result));

	interV.assign(stC.begin(), stC.end());	
	stA.clear();
	rge::set_symmetric_difference(result, interV, std::back_inserter(stA));
}