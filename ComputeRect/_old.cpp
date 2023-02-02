#include <iostream>
#include <map>
#include <ranges>
#include <fstream>

#include "Timer.cpp"

std::pair<int, int>* GenerateGrid(int x0, int y0, unsigned x, unsigned y){
	std::pair<int, int>* ptArray = new std::pair<int, int>[x * y +1];
	for (int i{x0}; i<x+x0; i++) {
		for (int j{y0}; j<y+y0; j++) {
			ptArray[i * y + j] = std::make_pair(i, j);
		}
	}
	return ptArray;
}

void PrintGrid(std::pair<int, int>* p, unsigned x, unsigned y) {
	std::cout << "\n /";
	for (int i{}; i < y; i++) {
		std::cout << " =++= ";
	}
	for (int i{}; i < 200; i++) {
		i++;
		i--;
	}

	std::cout << "\\\n";
	for (int i{}; i < x; i++) {
		std::cout << " |";
		for (int j{}; j < y; j++) {
			std::cout << ' ' << p[i * y + j].first << ", " << p[i * y + j].second << ' ';
		}
		std::cout << "|\n";
	}
	std::cout << "\\";
	for (int i{}; i < y; i++) {
		std::cout << " =++= ";
	}
	std::cout << " /";
}

unsigned int Solve(std::pair<int, int>* g, unsigned int x, unsigned int y) {
	std::map<std::pair<int, int>, int> segMap;
	std::pair<int, int> duo;
	for (int i{}; i < x * y; i++) {
		for (int j{}; j < x * y; j++) {
			if (g[i].first == g[j].first && g[i].second > g[j].second) {
				duo = std::pair<int, int>{ g[i].second, g[j].second };
				segMap[duo]++;
			}	
		}
	}

	std::map<std::pair<int, int>, int>::iterator it;
	int sum{}, val{};
	for (it = segMap.begin(); it != segMap.end(); it++)
	{
		val = it->second;
		sum += val * (val + 1) >> 1;
	}
	return sum;
}

int main() {

		Timer timer;
		int n(30), m(30);

		auto grid(GenerateGrid(0, 0, n, m));

		PrintGrid(grid, n, m);

		std::cout << '\n' << '\t' << Solve(grid, n, m) << '\n';

	return 0;
}