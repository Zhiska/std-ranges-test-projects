#include <iostream>
#include <deque>
#include <list>
#include <set>

#include "Random.h"
#include "Timer.h"

using namespace std;

void alaCollatz(double n, deque<double>& deq, list<double>& lst) {

	static const size_t maxIter = 10000;
	size_t i{};

	while (round(n) != 1. && i<maxIter) {

		deq.push_front(n);

		if (((int)round(n) % 2) == 0)
			n = n / 2;
		else
			n = 3 * n + 1;
	}

	size_t deqSize(deq.size());
	if (deqSize == 0)
		return;

	double dMax = *max_element(deq.begin(), deq.end());
	lst.clear();

	vector<double> temp(deq.begin(), deq.end());
	sort(temp.begin(), temp.end());

	for (decltype(temp.begin()) it = temp.begin(); it != temp.end(); it++) {
		lst.emplace_back(*it / dMax * 100.);
	}
	
	set<double> st(deq.begin(), deq.end());

	if (deqSize = st.size())
		printf("\tSequence is unique.");
	else
		printf("\tNot unique sequence.");
}

int main() {

	std::deque<double> deq;
	std::list<double> lst;

	alaCollatz(973, deq, lst);

}