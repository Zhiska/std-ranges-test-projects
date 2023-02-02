

//#include <algorithm>
//#include <iostream>
//#include <iterator>
//#include <vector>
//
//namespace rng = std::ranges;
//
//template <std::permutable I, std::sentinel_for<I> S>
//constexpr void stable_sort(I first, S last)
//{
//	if (first == last)
//		return;
//
//	auto pivot = *rng::next(first, rng::distance(first, last) / 2, last);
//	auto left = [pivot](const auto& em) { return em < pivot; };
//	auto tail1 = rng::stable_partition(first, last, left);
//	auto right = [pivot](const auto& em) { return !(pivot < em); };
//	auto tail2 = rng::stable_partition(tail1, right);
//
//	stable_sort(first, tail1.begin());
//	stable_sort(tail2.begin(), tail2.end());
//}

#include <iostream>
#include <algorithm>

#include "Random.h"
#include "Timer.h"

using namespace std;

string GenWord() {

	string wrd{};	size_t size(Random::Int(12, 40));
	for (int i{}; i < size; i++) {
		wrd += (char)Random::Int(97, 122);
	}

	return wrd;
}

int sum0, sum1, sum2, sum3; 
string cat = "cat", dog = "dog";

void CmpWords(size_t n) {
	string a, b;
	for (int i{}; i <n; i++) {
		a = GenWord();	b = GenWord();
		std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end()) ? sum0 += 1 : sum1 += 1;
		
		search(a.begin(), a.end(), cat.begin(), cat.end()) !=a.end() ? sum2 + 2 : sum2++;
		search(b.begin(), b.end(), dog.begin(), dog.end()) != b.end() ? sum3 + 2 : sum3++;
	}
}

int main() {
	Timer t;
	std::cout << GenWord() << std::endl;
	CmpWords(1000);
}