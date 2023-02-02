#include <iostream>
#include <ranges>
#include <algorithm>

#include "Random.h"
#include "Timer.h"

namespace rge = std::ranges;

int main() {
	Timer t;
	std::vector<double> vec;
	std::vector<double> vec1;

	vec.resize(1000);
	rge::generate(vec.begin(), vec.end(), []() {return (double)Random::Normalised(); });

	rge::make_heap(vec.begin(), vec.end());

	for (int i{}; i < 100; ++i) {
		rge::pop_heap(vec.begin(), vec.end());
		vec1.emplace_back(*std::make_move_iterator(vec.end() - 1));
		vec.erase(vec.end() - 1);
		rge::make_heap(vec.begin(), vec.end());
	}
	rge::reverse(vec1.begin(), vec1.end());
	vec1.resize(1000);

	rge::generate_n(vec1.begin() + 100, 900, Random::Real100);

	rge::sort_heap(vec);

	rge::make_heap(vec1.begin() + 100, vec1.end());
	rge::sort_heap(vec1.begin() + 100, vec1.end());
	rge::merge(vec1.begin(), vec1.begin() + 99, vec1.begin() + 100, vec1.end(), vec1.begin());
	rge::merge(vec, vec1, std::inserter(vec, vec.begin()));
}