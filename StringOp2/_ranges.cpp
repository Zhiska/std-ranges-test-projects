#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <algorithm>

#include "Timer.h"
#include "Random.h"

#include <list>
#include <vector>

using namespace std::ranges;

void ReadFileColumns(const std::string& path, std::vector<int>& vec, std::vector<double>& vec1, std::vector<std::string>& vec2, std::list<std::string>& lst) {
	std::ifstream infile(path);
	if (infile.is_open() && bool(infile)) {

		std::string colA, colB, colC, colD;
		std::string c;

		while (infile >> colA >> colB >> colC >> colD) {
			if (std::stoi(colA))

				vec.push_back(stoi(colA));
			else
				vec.push_back(-1);

			if (stod(colB))
				vec1.push_back(stoi(colA));
			else
				vec1.push_back(-1.);

			vec2.push_back(colC); lst.emplace_front(colD);
		}
	}
	infile.close();
}

void WriteFile(const std::string& path, std::vector<int>& vec, std::vector<double>& vec1, std::vector<std::string>& vec2, std::list<std::string>& lst) {
	if (size(vec) != size(vec1) || size(vec1) != size(vec2) || size(vec2) != size(lst))
		return;

	std::ofstream outfile(path);
	if (outfile.is_open() && bool(outfile)) {

		auto lstidx = lst.begin();
		for (size_t i{}; i < vec.size(); i++) {
			outfile << vec[i] << vec1[i] << vec2[i] << *lstidx;
			std::advance(lstidx, 1);
		}

		outfile.close();
	}
}

int Mingle(int n) {
	return Random::Int(10) + n / 3 % 4 * Random::Int(1, 3);
}

int main() {

	Timer t;

	std::vector<int> vec;
	std::vector<double> vec1;
	std::vector<std::string> vec2;
	std::list<std::string> lst;

	ReadFileColumns("valsA.txt", vec, vec1, vec2, lst);

	transform(vec, vec.begin(), [&](int n) {return Mingle(n); });
	transform(vec, vec1, vec1.begin(), [&](int n, double b) {return n == 0 ? b + n / 2. : b / n; }, {});
	for (auto it(vec2.begin()); it != vec2.end(); it++) {
		std::string str(*it); auto hj = str.end();
		str += *min_element(str.begin(), hj - 2);
		reverse(str.begin(), str.end());
		str += *max_element(str.begin(), hj - 2);
		reverse(str.begin(), str.end());
	}
	swap_ranges(vec2.begin(), vec2.end(), lst.begin(), lst.end());

	WriteFile("valsA.txt", vec, vec1, vec2, lst);

	return 0;
}

//fstream As("valsA", std::ios::out);
//fstream Bs("valsB", std::ios::out);
//fstream Cs("valsC", std::ios::out);
//fstream Ds("valsC", std::ios::out);