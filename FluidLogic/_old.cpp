#include <iostream>
#include <array>
#include <algorithm>

#include "Timer.h"

using namespace std;

// Assumptions
// Fluid incompresible, no viscosity, 

float ro{0.5};	// fluid density
float h{0.125};	// grid spacing, m
float dt{0.05};	// step time, s
// size 80 * 60

float corr{ 1.75 };	// speed sum correction

array<int, 642 * 482> S;	// scale grid - walls are 0
array<float, 640*481> V;	// vert speed grid
array<float, 641*480> U;	// horizontal speed grid
array<float, 640 * 480> P; // presssure in tiles

int main() {

	Timer t;
	fill(S.begin(), S.end(), 1);
	for (int i(642); i < 642 * 482; i += 642) {	// side 0s
		S[i] = 0;
		S[i-1] = 0;
	}
	for (int i{}; i < 641; i++) {	// top, bottom 0s
		S[i] = 0;
		S[481*642 + i] = 0;
	}
		
	generate(V.begin(), V.end(), Random::Normal); // seed speeds between 0. - 2.
	generate(U.begin(), U.end(), Random::Normal); // etc.

	fill_n(P.begin(), 480*640, 1000.);

	float d{}; int s{};	// local sums for each tile of 'grid'

	// Evolution over time for 100 iterations
	for (int k{}; k < 100; ++k) {
		for (int i{}; i < 480 * 640; i++) {
			d = corr* (U[i + 1] - U[i] + V[i] - V[i + 640]);
			s = S[i + 1] + S[i + 642] + S[i + 644] + S[i + 1285];

			U[i] += d * S[i + 642] / s;
			U[i + 1] -= d * S[i + 644];
			V[i+640] += d * S[i + 1285] / s;
			V[i] -= d * S[i + 1] / s;

			P[i] += d / s * ( ro * h / dt);

		}
	}
}
// advocation
//for (int i{}; i < 640 * 480; i++) {
//	vd = (V[i] + V[i + 1] + V[i + 640] + V[i + 641]) / 4.;	// local mean speed vector
//	ud = (U[i] + U[i + 1] + U[i + 641] + U[642]) / 4.;

//	x = x - ud * dt;	// prev hor grid index
//	y = y - vd * dt;	// prev ver grid index