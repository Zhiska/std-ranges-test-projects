#include <iostream>
#include <set>
#include <cmath>
#include <array>
#include <algorithm>

#include "Random.h"
#include "Timer.h"

int main() {

	std::array<float, 30> arr;
	std::vector<int> vec(20);

	std::set<double> st;
	
	std::vector<int> result;

	for (int i(7); i != 210; i += 7) {
		printf("%i", i);
		arr[i%30] = (int)std::floor(sqrt(i));
	}

	std::generate_n(vec.begin(), 20, Random::I100);

	for (int i(Random::I100()); i > -30; i--)
		st.insert(i%2==0?i/2:3*i-1);

	// TEST
	std::make_heap(arr.begin(), arr.end());
	result.resize(30);
	std::transform(arr.begin(), arr.end(), result.begin(), [](float f) {return (int)f; });

	std::make_heap(vec.begin(), vec.end()-10);

	result.insert(result.end(), std::make_move_iterator(vec.begin()), std::make_move_iterator(vec.begin() + 10));
	std::make_heap(result.begin(), result.end());
	std::sort_heap(result.begin(), result.end());

	for (auto it = vec.end() - 10; it != vec.end(); it++)
		st.insert(*it);

	vec.clear();
	vec.insert(std::end(vec), std::begin(st), std::end(st));

	std::make_heap(vec.begin(), vec.end());
	for (unsigned i(vec.size() - 1); i != 0; i--)
		std::pop_heap(vec.begin(), vec.end());

	for (auto it(vec.begin()); it != vec.end(); it++) {
		result.push_back(*it);
		std::push_heap(result.begin(), result.end());
	}

	std::cout << "Wektor po przekszta³ceniach: \n";
	for (auto a : result)
		std::cout << a;
}