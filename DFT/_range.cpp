#include <iostream>
#include <complex>
#include <cmath>
#include <algorithm>
#include <ranges>

#include "Random.h"
#include "Timer.h"

void dft(std::vector<std::complex<double>>::iterator rb, std::vector<std::complex<double>>::iterator re,
	std::vector<std::complex<double>>::iterator outb, std::vector<std::complex<double>>::iterator oute) {

	unsigned k{};
	unsigned N = std::ranges::distance(rb, re);
	double C = 2 * std::_Pi * N;
	unsigned n{};
	std::complex<double> t_sum(0., 0.);	

	for (auto i(outb); i != oute; i++) {	
		n++;
		for (auto j(rb); j != re; j++) {	
			std::complex<double> temp(cos(C * k * n), -sin(C * k * n));
			t_sum += *j * temp;
			k++;
		}
		*i = t_sum;
	}
};

void dft(std::vector<std::complex<double>> v0, std::vector<std::complex<double>> v1) {
	dft(v0.begin(), v0.end(), v1.begin(), v1.end());
}

int main() {

	Timer t;

	std::vector<std::complex<double>> vec0;
	std::vector<std::complex<double>> vec1;

	std::vector<std::complex<double>> vec2;
	std::vector<std::complex<double>> vec3;

	vec0.resize(1000);
	vec1.resize(1000);
	vec2.resize(1000);
	vec3.resize(1000);

	std::ranges::fill(vec0, std::complex<double>{ -17.64, 23.52 });
	std::ranges::generate(vec1, Random::Cmplx1);

	dft(vec0.begin(), vec0.end(), vec2.begin(), vec2.end());
	dft(vec1.begin(), vec1.end(), vec3.begin(), vec3.end());

	std::copy(vec2.begin(), vec2.begin() + 6,
		std::ostream_iterator<std::complex<double>>(std::cout, "; ")); std::cout << '\n';
	std::copy(vec3.begin(), vec3.begin() + 6,
		std::ostream_iterator<std::complex<double>>(std::cout, "; ")); std::cout << '\n';
}
