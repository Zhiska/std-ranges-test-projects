#include <iostream>
#include <ranges>
#include <algorithm>

#include "Random.h"
#include "Timer.h"

#include <vector>
#include <list>
#include <set>

using namespace std::ranges;

enum Sizes {
	S1 = 10000,
	S2 = 1000,
	S3 = 100
};

void SortsAndChecks(std::vector<float>& vec, std::set<float_t>& st, std::list<float>& lst) {

	if (size(vec) == 0 || size(st) == 0)
		return;

	std::vector<float> temp;
	sample(vec, std::back_inserter(temp), 1000, std::mt19937{std::random_device{} ()});
	copy_n(temp.begin(), 10, std::ostream_iterator<float>(std::cout, " "));


	rotate(temp, temp.begin() + size(temp)/3);

	copy_n(temp.begin(), 10, std::ostream_iterator<float>(std::cout, " "));

	if (any_of(st, [&](float_t i) {return *begin(temp) == i; }))
		copy_n(vec.begin() + size(vec) / 4, 20, std::back_inserter(lst));
	else
		for (auto x : subrange(vec.begin() + size(vec) / 4, vec.begin() + size(vec) / 4 + 20))
			st.insert(x);

	copy_if(vec, std::back_inserter(lst), [=](float x) {return abs(x) > 0.5; });

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
	sample(vec, std::back_inserter(temp), 6, std::mt19937{ std::random_device{} () }); copy(temp, std::ostream_iterator<float>(std::cout, " ")); temp.clear();
	if(size(st) >5)
		sample(st, std::back_inserter(temp), 6, std::mt19937{ std::random_device{} () }); copy(temp, std::ostream_iterator<float>(std::cout, " ")); temp.clear();
	if(size(lst)>5)
		sample(lst, std::back_inserter(temp), 6, std::mt19937{ std::random_device{} () }); copy(temp, std::ostream_iterator<float>(std::cout, " ")); temp.clear();
}

float rnd() {
	return Random::Real(-20., 20.);
}

int main() {
	Timer timer;
	std::vector<float> vec; vec.resize(S1);
	generate(vec, rnd);

	std::set<float_t> st;
	std::list<float> lst;

	std::cout << GetSet(vec, st, 432);
	SortsAndChecks(vec, st, lst);
	PrintData(vec, st, lst);
}