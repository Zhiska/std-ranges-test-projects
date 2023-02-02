#pragma once

#include <random>
#include <iostream>
#include <complex>

class Random {
public:  
	static Random& Get() {
		static Random instance;
		return instance;
	}

	static std::complex<double> Cmplx1() { return { Get().IReal(-1.,1.), Get().IReal(-1.,1.) }; }
	static std::complex<double> Cmplx(double a, double b) { return { Get().IReal(-a,a), Get().IReal(-b,b) }; }
	static float Real(float a, float b) { return Get().IReal(a, b); }
	static float Real(float a) { return Get().IReal(0., a); }
	static float Real() { return Get().IReal(0., 10.); }
	static float Normalised() { return Get().IReal(); }
	static int Int(int a, int b) { return Get().IInt(a, b); }
	static int Int(int b) { return Get().IInt(0, b); }
	static int Int() { return Get().IInt(0, 10); }
	static bool Coinflip() { return Get().IInt(); }

private:
	std::random_device dev;

	Random() {}
	Random(const Random&) = delete;

	float IReal(float k = 0., float n = 1.) {
		std::mt19937 rng(dev());
		std::uniform_real_distribution<> UniFlDist(k, n);
		return UniFlDist(rng);
	}
	int IInt(int k = 0, int n = 1) {
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> UniIntDist(k, n);
		return UniIntDist(rng);
	}
};