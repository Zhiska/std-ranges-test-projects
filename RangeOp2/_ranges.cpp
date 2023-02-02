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

void Initialize()	//when needed{
	rng.seed(seed);

}

std::vector<float> GetVector(unsigned n) {
	std::vector<float> vec;
	vec.resize(n);
	std::generate(vec.begin(), vec.end(), [&] {return rDist(rng); });

	return vec;
}

template <std::input_iterator I, std::sentinel_for<I> S, typename Init = std::iter_value_t<I>, typename Op = std::plus<>, typename Proj = std::identity>
Init accumulate(I first, S last, Init init = Init{}, Op op = Op{}, Proj proj = Proj{}) {
	while (!(first == last)) {
		init = std::invoke(op, std::move(init), std::invoke(proj, *first));
		++first;
	}
	return init;

}

//overloading to begin-end ranges version is a standard way of implmenting such algorithm
template <std::ranges::input_range R, typename Init = std::ranges::range_value_t<R>, typename Op = std::plus<>, typename Proj = std::identity>
Init accumulate(R&& rge, Init init = Init{}, Op op = Op{}, Proj proj = Proj{}) {
	return accumulate(std::ranges::begin(rge), std::ranges::end(rge), std::move(init), std::move(op), std::move(proj));
}

int main() {
		Timer timer;

		std::cout << accumulate(GetVector(100000), {}, {}, [](float i) { return i * i; });
}
