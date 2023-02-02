// Singletons are containers for static data and its relevant methods (fe.: counting metadata, time functions, random generators, enums)
// used in a single translation unit
#pragma once

#include <random>
#include <iostream>

class Random {	// singleton
public:

	static int Val;

	static Random& Get() {
		static Random instance;
		return instance;
	}

	static bool Coinflip() { return Get().IInt(); }

	static float Normalised() { return Get().IReal(); }	// part 1 - calls on instance for us - shorter IFloat method call: Random::Float(); instead of Random::Get().IFloat();

	static float Real(float a, float b) { return Get().IReal(a, b); }

	static int Int(int k, int n) { return Get().IInt(k, n); }

private:

	std::random_device dev;

	Random() {
	}	// private constructor - only 1 use

	Random(const Random&) = delete;	// copy "protection"

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