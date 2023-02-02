#include <iostream>
#include <ranges>
#include <random>
#include <numeric>
#include <functional>
#include <iomanip>
#include <algorithm>
#include <numeric>

#include "TypeName.h"
#include "Timer.h"

#define PI 3.14

std::mt19937 rng;  
unsigned seed;          

std::uniform_real<float_t> rDist(0.0f, 2.0f);  

void Initialize(){
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

	auto adapted = std::ranges::views::transform(func)
		| std::ranges::views::drop_while([](int n) {return n < 10; })
		| std::ranges::views::reverse
		| std::ranges::views::take(10);

	auto b = vec | adapted;
}

//struct MySafetype {};
//
//template<typename MySafeType>
//inline constexpr bool
//std::ranges::enable_borrowed_range<MySafeType> = true;