#include <fstream>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
"
#include "Timer.h"

int main() {
    Timer t;

    std::ofstream myfile;
    myfile.open("test1.txt");

    // string stream - start point
    auto words = std::stringstream{ "today is yesterday’s tomorrow" };

    std::string word;
    for (int i{}; i < 100; i++) {
        while(words >> word) {
            myfile << word << i << ' ' << ', ';
        }
    }

    std::cout << '\n';
    myfile.close();

    std::ifstream drawfile;
    drawfile.open("test.txt");
    std::string s;

    std::getline(drawfile, s);

    std::string signs = "ntvrf";
    std::string floats = "1.1  2.2\t\t3.3\n\v4.4\f55\n\r66\r7.7  8.8";
    for (int i{}; i < 100; i++) {
        floats += (char)Random::Int(97, 122) + "\\" + signs[Random::Int(5)];
    }
    std::string strim(floats);

    // end point - has to be print by copy
    std::copy(
        strim.begin(), strim.end(),
        std::ostream_iterator<float>{std::cout, ", "});
    std::cout << '\n';

    return 0;
}
