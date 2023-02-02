#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <ranges>
#include <fstream>

#include "Random.h"
#include "Timer.h"

std::vector<int> vec(10);
std::vector<int> vec1(20);
std::vector<int> vec2(30);
std::vector<int> vec3(30);

namespace rge = std::ranges;

int main() {
	Timer t;
	rge::generate(vec.begin(), vec.end(), Random::I100);

	rge::generate_n(vec1.begin(), 5, [&]() {return Random::Int(20); });
	rge::fill_n(vec1.begin() + 5, 10, 7);
	rge::copy_n(vec.begin() + 5, 5, vec1.begin() + 15);
	{
		static int k(30);
		rge::generate_n(vec2.rbegin(), 10, [&]() {k++; return k; });
	}
	rge::generate(vec2.begin(), vec2.begin() + 10, Random::I100);
	{
		int k(25);
		for (auto i : vec3) {

			if (k % 4 == 0)
				i = k * k / 4;
			else
				i = k - 1;
			k + 2;
		}
	}

	// TEST
	rge::sort(vec);
	rge::sort(vec1);
	rge::sort(vec2);
	rge::sort(vec3);

	rge::set_intersection(vec, vec1, vec.begin());
	std::cout << "vec and vec1 set intersection: " << '\t';
	rge::copy(vec, std::ostream_iterator<int>(std::cout, " ")); printf("\n");

	rge::set_difference(vec2, vec3, vec2.begin());
	std::cout << "vec2 and vec3 set difference: " << '\t';
	rge::copy(vec2, std::ostream_iterator<int>(std::cout, " ")); printf("\n");

	rge::sort(vec.begin(), vec.end());
	rge::sort(vec2.begin(), vec2.end());
	vec1.clear();
	vec1.resize(vec.size() + vec2.size());

	rge::merge(vec, vec2, vec1.begin());
	std::cout << "vec2 set merge vec3: " << '\t';
	rge::copy(vec2, std::ostream_iterator<int>(std::cout, " ")); printf("\n");

	std::cout << "vec includes vec1 after transformations: " << std::boolalpha << rge::includes(rge::take_view(vec1, 10), vec) << std::endl;
}