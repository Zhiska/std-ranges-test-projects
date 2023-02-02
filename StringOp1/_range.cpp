#include <fstream>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <ranges>
#include <sstream>
#include <string>

#include "Random.h"
#include "Timer.h"

int main() {
    Timer t;

	std::ofstream myfile;
	myfile.open("test1.txt");

    auto words = std::stringstream{ "today is yesterday’s tomorrow" };
    for (int i{}; i < 100; i++) {
        for (const auto& s : std::ranges::istream_view<std::string>(words)) {
            myfile << s << i<<' '<<', ';
        }
    }

    std::cout << '\n';
    myfile.close();

    std::ifstream drawfile;
    drawfile.open("test.txt");
    std::string s;

    std::getline(drawfile, s);

    std::string signs = "ntvrf";
    std::string floats =  "1.1  2.2\t\t3.3\n\v4.4\f55\n\r66\r7.7  8.8" ;
    for (int i{}; i < 100; i++) {
        floats += (char)Random::Int(97, 122)+"\\"+signs[Random::Int(5)];
    }
    std::stringstream strim(floats);
    std::ranges::copy(
        std::ranges::istream_view<float>(strim),
        std::ostream_iterator<float>{std::cout, ", "});
    std::cout << '\n';

	return 0;
}