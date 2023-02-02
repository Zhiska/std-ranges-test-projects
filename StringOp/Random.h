#pragma once

#include <random>
#include <iostream>

class Random {
public:

	static Random& Get() {
		static Random instance;
		return instance;
	}

	static float Real(float a, float b) { return Get().IReal(a, b); }

	static float Real(float a) { return Get().IReal(0., a); }

	static float Normalised() { return Get().IReal(); }

	static int Int(int a, int b) { return Get().IInt(a, b); }

	static int Int(int b) { return Get().IInt(0, b); }

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