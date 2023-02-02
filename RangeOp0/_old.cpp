#include <iostream>
#include <random>
#include <numeric>
#include <functional>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <span>

#include "TypeName.h"
#include "Timer.h"

#define PI 3.14

std::mt19937 rng;
unsigned seed;

std::uniform_real<float_t> rDist(0.0f, 2.0f);

void Initialize() {
	rng.seed(seed);
}

std::span<int> GetSpan() {
	std::vector<int> vec = { 1,2,3,4,5,6,7,8,9,0 };
	std::span<int> sp(vec);
	return sp;
}

std::vector<int> GetVector() {
	std::vector<int> temp = { 1,2,3 };
	return temp;
}

int main() {

	std::vector<int> vec = { 1,2,3,4,5,6,7,8,9,0 };
	auto func = [&](int n) {return n * n; };

	std::transform(vec.begin(), vec.end(), vec.begin(), func);

	std::vector<int>::iterator it = vec.begin();
	while (it != vec.end()) {
		if (*it < 10) {
			it = vec.erase(it);
			continue;
		}
		it++;
	}

	std::reverse(vec.begin(), vec.end());

	std::vector<int> result(vec.begin(), vec.begin()+10);
}

//struct MySafetype {};
//
//template<typename MySafeType>
//inline constexpr bool
//std::ranges::enable_borrowed_range<MySafeType> = true;