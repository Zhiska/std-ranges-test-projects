#include <iterator>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <array>

#include "Random.h"
#include "Timer.h"

#include <algorithm>

template<typename T>
class CustomBox {
private:
	T* m_tab;
	unsigned m_size;

public:
	class Iterator 
		 {
	public:
		//Iterator required definition
		using iterator_category = std::bidirectional_iterator_tag;// ranges concept
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

	CustomBox(const unsigned size) : m_size(size) {
		m_tab = new T[size];
	}

	CustomBox(const T* p, const unsigned size) : m_size(size) {
		m_tab = new T[size];

		for (int i{}; i < size; i++) {
			m_tab[i] = p[i];
		}
	}

	~CustomBox() {
		delete[] m_tab;
	}

	//requires std::bidirectional_iterator
	Iterator begin() 
		{
		return Iterator(&m_tab[0], m_size);
	}

	Iterator  end()
		{
		return Iterator(&m_tab[m_size], m_size);
	}
};

int main() {

	Timer t;

	int arr[10]{1,2,3,4,5,6,7,8,9,0};
	float arr1[10];

	CustomBox Container(arr, 10);

	CustomBox Container1(arr1, 10);

	for (auto i : Container)
		std::cout << i << '\n';
}