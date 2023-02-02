#include <iostream>
#include <algorithm>

#include "Random.h"
#include "Timer.h"

int main() {

	Timer t;

	std::vector<double> vec;
	std::vector<double> vec1;

	vec.resize(1000);
	std::generate(vec.begin(), vec.end(), []() {return (double)Random::Normalised(); });

	std::make_heap(vec.begin(), vec.end());

	for (int i{}; i < 100; ++i) {
		std::pop_heap(vec.begin(), vec.end());
		std::cout << " " << *(vec.end() - 1);
		vec1.emplace_back(*std::make_move_iterator(vec.end() -1));
		vec.erase(vec.end()-1);
		std::make_heap(vec.begin(), vec.end());
	}
	std::reverse(vec1.begin(), vec1.end());
	vec1.resize(1000);

	std::generate_n(vec1.begin()+100, 900, Random::Real100);

	std::sort_heap(vec.begin(), vec.end());

	std::make_heap(vec1.begin() + 100, vec1.end());
	std::sort_heap(vec1.begin() + 100, vec1.end());
	std::merge(vec1.begin(), vec1.begin() + 99, vec1.begin() + 100, vec1.end(), vec1.begin());
	std::merge(vec.begin(), vec.end(), vec1.begin(), vec1.end(), std::inserter(vec, vec.begin()));
}