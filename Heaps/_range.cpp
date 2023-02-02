#include <iostream>
#include <set>
#include <cmath>
#include <array>
#include <algorithm>
#include <ranges>

#include "Random.h"
#include "Timer.h"

namespace rge = std::ranges;

int main() {
	Timer t;
	std::array<float, 30> arr;
	std::vector<int> vec(20);
	std::set<double> st;

	std::vector<int> result;

	for (int i(7); i != 210; i += 7) {
		printf("%i", i);
		arr[i % 30] = (int)std::floor(sqrt(i));
	}

	rge::generate_n(vec.begin(), 20, Random::I100);

	for (int i(Random::I100()); i > -30; i--)
		st.insert(i % 2 == 0 ? i / 2 : 3 * i - 1);

	// TEST
	rge::make_heap(arr);

	result.resize(30);
	rge::transform(arr, result.begin(), [](float f) {return (int)f; });

	rge::make_heap(vec.begin(), vec.end() - 10);

	result.insert(result.end(), std::make_move_iterator(vec.begin()), std::make_move_iterator(vec.begin() + 10));
	
	rge::make_heap(result.begin(), result.end());
	rge::sort_heap(result.begin(), result.end());

	for (auto it = vec.end() - 10; it != vec.end(); it++)
		st.insert(*it);

	vec.clear();
	vec.insert(std::end(vec), std::begin(st), std::end(st));

	rge::make_heap(vec.begin(), vec.end());
	for (unsigned i(vec.size() - 1); i != 0; i--)
		rge::pop_heap(vec.begin(), vec.end());

	for (auto it(vec.begin()); it != vec.end(); it++) {
		result.push_back(*it);
		rge::push_heap(result.begin(), result.end());
	}

	std::cout << "Output vector after transformations: \n";
	for (auto a : result)
		std::cout << a;
}