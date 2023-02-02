#include <iostream>
#include <algorithm>

#include "Random.h"
#include "Timer.h"

#include <set>
#include <map>
#include <list>
#include <deque>

std::vector<bool> vec;
std::set<long long> st;
std::list<std::string> lst;
std::map<char, int> mp;
std::deque<int> dq;

using namespace std;

enum Size {
	S1 = 100,
	S2 = 10000,
	S3 = 1000,
};

int main() {

	Timer timer;

	std::vector<int> vec(S2, Random::Int(0, 250));

	std::vector<int> temp{}; temp.resize(S2, -1);
	unique_copy(vec.begin(), vec.end(), temp.begin());

	std::cout << *mismatch(vec.begin(), vec.end(), temp.begin()).first << std::endl;

	int size = find(temp.begin(), temp.end(), -1) - temp.begin();
	temp.resize(size);
	std::list<unsigned> freq(size, 0);

	for (int it : temp) {
		freq.push_back(count(vec.begin(), vec.end(), it));
	}

	std::vector<int> vec1(S2, Random::Int(13, 2137));
	if (!is_sorted(vec1.begin(), vec1.end())) {
		sort(vec1.begin(), vec1.end());
	}
	std::cout << *adjacent_find(vec1.begin(), vec1.end()) << std::endl;

	std::vector<unsigned> vec2;
	vec2.resize(S2);
	copy_backward(vec1.begin(), vec1.end(), vec2.end());
	nth_element(vec2.begin(), vec2.begin() + Random::Int(100, 901), vec2.end());

	temp.resize(S2);
	temp.assign(vec2.begin(), vec2.end());

	swap_ranges(temp.begin(), temp.end(), vec.begin());

}