#include <ranges>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <random>
#include <numeric>
#include <concepts>
#include <functional>
#include "Timer.h"

std::mt19937 rng;  // the Mersenne Twister with a popular choice of parameters
unsigned seed;           // populate with junk

std::uniform_real<float_t> rDist(0.0f, 2.0f);  // uniform distribution

void Initialize(){	//when needed{
	rng.seed(seed);
}

std::vector<float_t> GetVector(unsigned n) {
	std::vector<float_t> vec;
	vec.resize(n);
	std::generate(vec.begin(), vec.end(), [&] {return rDist(rng); });

	return vec;
}

int main() {
		Timer t;
		std::vector<float_t> vec(GetVector(100000));
		std::cout << std::accumulate(vec.begin(), vec.end(), 1., std::multiplies<float_t>());

	return 0;
}

