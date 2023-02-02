#include <iterator>
#include <cstddef>
#include <iostream>

#include <algorithm>
#include <random>

#include "Timer.h"

std::random_device rng;
std::uniform_real ur100(120., 220.);
std::mt19937 gen;

template<typename T>
class CustomBox {
private:
	T *m_tab;
	unsigned m_size;

public:
	class Iterator
	{
	public:
		//Iterator required definition
		using iterator_category = std::bidirectional_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = int;
		using pointer = int*;
		using reference = int&;

		Iterator() : im_ptr{}, im_size{} {}
		Iterator(pointer ptr, const unsigned size) : im_ptr(ptr), im_size(size) {}

		reference operator*() const { 
			return *im_ptr; 
		}
		pointer operator->() { 
			return im_ptr; 
		}

		Iterator& operator++() { 
			im_ptr++; 
			return *this; 
		}
		Iterator& operator+(int n) {
			im_ptr + n;
			return *this;
		}
		Iterator operator++(int) { 
			Iterator tmp = *this; 
			++(*this); 
			return tmp; 
		}
		Iterator& operator--() {
			im_ptr--;
			return *this;
		}
		Iterator operator--(int) {
			Iterator tmp = *this;
			--(*this);
			return tmp;
		}

		bool operator== (const Iterator& b) { return im_ptr == b.im_ptr; };
		bool operator!= (const Iterator& b) { return im_ptr != b.im_ptr; };

	private:
		pointer im_ptr;
		unsigned im_size;
	};

	CustomBox() : m_size{} {}

	CustomBox(const T* p, const unsigned size) : m_size(size) {
		m_tab = new T[m_size];

		for (int i{}; i < size; i++) {
			m_tab[i] = p[i];
		}
	}

	~CustomBox() {
		delete[] m_tab;
	}

	Iterator begin() {
		auto it = m_tab;
		return Iterator(&it, m_size);
	}

	Iterator end() {
		auto it = m_tab[m_size - 1];
		return Iterator(( & it), m_size); // after the end
	}
};

int main() {

	Timer t;

	int arr[10]{ 1,2,3,4,5,6,7,8,9,0 };
	float arr1[10];

	CustomBox Container(arr, 10);

	CustomBox Container1(arr1, 10);

	for (auto i : Container)
		std::cout << i << '\n';
}
	//CustomBox(int size, T val) : m_size(size) {
//	m_tab = new T[m_size];

//	for (int i{}; i < size; i++) {
//		m_tab[i] = val;
//	}
//}