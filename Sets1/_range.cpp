#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

#include "Random.h"
#include "Timer.h"

std::vector<int> vec(10);
std::vector<int> vec1(20);
std::vector<int> vec2(30);
std::vector<int> vec3(30);

int main() {
	Timer timer;
	std::generate(vec.begin(), vec.end(), Random::I100);

	std::generate_n(vec1.begin(), 5, [&]() {return Random::Int(20); });
	std::fill_n(vec1.begin() + 5, 10, 7);
	std::copy_n(vec.begin() + 5, 5, vec1.begin() + 15);

	std::iota(vec2.rbegin(), vec2.rbegin() + 10, 30);
	std::generate(vec2.begin(), vec2.begin() + 10, Random::I100);
	{
		int k(25);
		for (auto i = vec3.begin(); i != vec3.end(); i++) {
			if (k % 4 == 0)
				*i = k * k / 4;
			else
				*i = k - 1;
			k+2;
		}
	}

	// TEST
	std::sort(vec.begin(), vec.end());
	std::sort(vec1.begin(), vec1.end());
	std::sort(vec2.begin(), vec2.end());
	std::sort(vec3.begin(), vec3.end());

	std::set_intersection(vec.begin(), vec.end(), vec1.begin(), vec1.end(), vec.begin());
	std::cout << "vec and vec1 set intersection: " << '\t';
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " ")); printf("\n");

	std::set_difference(vec2.begin(), vec2.end(), vec3.begin(), vec3.end(), vec2.begin());
	std::cout << "vec2 and vec3 set difference: " << '\t';
	std::copy(vec2.begin(), vec2.end(), std::ostream_iterator<int>(std::cout, " ")); printf("\n");

	std::sort(vec.begin(), vec.end());
	std::sort(vec2.begin(), vec2.end());
	vec1.clear();
	vec1.resize(vec.size()+ vec2.size());

	std::merge(vec.begin(), vec.end(), vec2.begin(), vec2.end(), vec1.begin());
	std::cout << "vec2 set merge vec3: " << '\t';
	std::copy(vec2.begin(), vec2.end(), std::ostream_iterator<int>(std::cout, " ")); printf("\n");

	std::cout << "vec includes vec1 after transformations: " << std::boolalpha << std::includes(vec1.begin(), vec1.begin() + 9, vec.begin(), vec.end()) << std::endl;
}