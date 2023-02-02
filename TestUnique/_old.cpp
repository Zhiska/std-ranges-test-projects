#include <iostream>
#include <set>
#include <algorithm>
#include <list>

#include "Random.h"
#include "Timer.h"

using namespace std;

template<typename R>
bool checkA(R beg, R end) {
	auto val = *beg;
	std::vector<decltype(val)> vec;
	vec.resize(distance(beg, end));
	copy(beg, end, vec.begin());
	unique(vec.begin(), vec.end());
	return equal(beg, end, vec.begin(), vec.end());
}

template<typename R>
bool checkB(R rb, R re) {
	auto val = *rb;
	set<decltype(val)> st(rb,re);
	return size(st) == distance(rb, re);
}

template<typename R>
bool checkC(R rb, R re) {
	sort(rb, re);
	return adjacent_find(rb, re) != re ? false : true;
}

int main() {
	Timer t;

	vector<int> vec( 10000, Random::Int(100) );
	std::list<double> lst(10000, Random::Normalised());

	printf("Sprawdzenie:	1- %b,	2-%b,	3-%b\n", checkA(vec.begin(), vec.end()), checkB(vec.begin(), vec.end()), checkC(vec.begin(), vec.end()));
	printf("Sprawdzenie:	1- %b,	2-%b\n", checkA(lst.begin(), lst.end()), checkB(lst.begin(), lst.end()));
}

