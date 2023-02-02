#include <iostream>
#include <map>

#include <ranges>
#include <array>

#include "Timer.cpp"

std::array< std::pair<int, int>, 100> glArr;

void GenerateGrid(int x0, int y0, unsigned x, unsigned y) {
	for (int i{ x0 }; i < x + x0; i++) {
		for (int j{ y0 }; j < y + y0; j++) {
			glArr[i * y + j] = std::make_pair(i, j);
		}
	}
}

void PrintGrid(unsigned x, unsigned y) {
	std::cout << "\n/";

	for (int i{}; i < y; i++) {
		std::cout << " =++= ";
	}
	std::cout << "\\";

	for (int i{}; i < x; i++) {
		std::cout << "|";
		for (auto iy : std::ranges::views::values(std::views::take(std::views::drop(glArr, i* y), y))) {
			std::cout << i << ", " << x << " ";
		}
		std::cout << "|\n";
	}
	std::cout << "\\";

	for (int i{}; i < y; i++) {
		std::cout << " =++= ";
	}
	std::cout << "/";
}

unsigned int Solve (unsigned int x, unsigned int y) {
	std::map<std::pair<int, int>, int> segMap;
	for (auto p1 : glArr) {
		for (auto p2 : glArr) {
			if (p1.first == p2.first && p1.second > p2.second) {
				segMap[std::pair<int, int>{ p1.second, p2.second }]++;
			}
		}
	}

	unsigned sum{};
	for (auto v : std::ranges::views::values(segMap))
		sum += v;
	return sum;
}

int main() {

	Timer timer;
	int n(30), m(30);

	PrintGrid(n, m);

	std::cout << '\n' << '\t' << 9 << '\n';

	return 0;
}