#include <iostream>
#include <algorithm>
#include <fstream>

#include "Random.h"
#include "Timer.h"
#include <algorithm>

#include <vector>
#include <list>
#include <set>

using namespace std;

enum Sizes {

	S1 = 10000,
	S2 = 1000,
	S3 = 100
};

void SortsAndChecks(std::vector<float>& vec, std::set<float_t>& st, std::list<float>& lst) {

	if (size(vec) == 0 || size(st) == 0)
		return;

	std::vector<float> temp;
	sample(vec.begin(), vec.end(), std::back_inserter(temp), 1000, std::mt19937{std::random_device{} ()});
	copy_n(temp.begin(), 10, std::ostream_iterator<float>(std::cout, " "));


	rotate(temp.begin(), temp.begin() + size(temp) / 3, temp.end());

	copy_n(temp.begin(), 10, std::ostream_iterator<float>(std::cout, " "));

	if (any_of(st.begin(), st.end(), [&](float_t i) {return *begin(temp) == i; }))
		copy_n(vec.begin() + size(vec) / 4, 20, std::back_inserter(lst));
	else
		for (auto it(vec.begin() + size(vec) / 4); it != vec.begin() + size(vec) / 4 + 20; it++)
			st.insert(*it);

	copy_if(vec.begin(), vec.end(), std::back_inserter(lst), [=](float x) {return abs(x) > 0.5; });

	std::cout << "Performed range algorithms";
}

const std::string& GetSet(std::vector<float>& vec, std::set<float_t>& st, size_t n) {

	if (size(vec) < 2)
		return "Range too small";

	for (auto it(vec.begin()); it != vec.end() && it != vec.end() - 1; it++) {
		Random::Int(1000) == 621 ? st.insert(*it + n) : st.insert(*it);
		it++;
		n += 9.;
	}
	return "\tAction performed succesfully";
}

void PrintData(std::vector<float>& vec, std::set<float_t>& st, std::list<float>& lst) {
	std::cout << "\tSizes: " << size(vec) << '\t' << size(st) << '\t' << size(lst) << std::endl;
	std::cout << "\tRange samples: " << std::endl;
	std::vector<float> temp(6);
	sample(vec.begin(), vec.end(), std::back_inserter(temp), 6, std::mt19937{std::random_device{} ()}); copy(temp.begin(), temp.end(), std::ostream_iterator<float>(std::cout, " ")); temp.clear();
	if (size(st) > 5)
		sample(st.begin(), st.end(), std::back_inserter(temp), 6, std::mt19937{std::random_device{} ()}); copy(temp.begin(), temp.end(), std::ostream_iterator<float>(std::cout, " ")); temp.clear();
	if (size(lst) > 5)
		sample(lst.begin(), lst.end(), std::back_inserter(temp), 6, std::mt19937{std::random_device{} ()}); copy(temp.begin(), temp.end(), std::ostream_iterator<float>(std::cout, " ")); temp.clear();
}

float rnd() {
	return Random::Real(-20., 20.);
}

int main() {
	Timer tinmer;

	std::vector<float> vec; vec.resize(S1);
	generate(vec.begin(), vec.end(), rnd);
	std::set<float_t> st;
	std::list<float> lst;

	std::cout << GetSet(vec, st, 432);
	SortsAndChecks(vec, st, lst);
	PrintData(vec, st, lst);
}