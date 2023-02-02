#include <iostream>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>
#include <ranges>

#include "Random.h"
#include "Timer.h"

namespace rge = std::ranges;

int main() {
    {
        Timer timer;
        size_t size(36);

        std::vector<int> vec(size);
        rge::fill(vec.begin(), vec.end(), 0);

        std::ifstream file_in("content.txt");

        if (file_in.is_open()) {
            std::string line;
            int value;

            while (std::getline(file_in, line)) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));  
                system("cls");
                int i{};
                auto ss = std::stringstream(line);

                while (ss >> std::skipws >> value) {
                    *(vec.begin() + 4 + 8 * i) += value;
                    *(vec.begin() + 5 + 8 * i) += value;
                    i++;
                }

                std::cout << "      col A    col B    col C    col D" << std::endl; 

                int max1 = *rge::max_element(vec) * 1.1;
                int max2 = max1;

                for (int i = 0; i < max1; i++) {
                    if (i < 2 || i % 4 == 0)
                        std::cout << std::right << std::setw(5) << i; 
                    else
                        std::cout << std::right << std::setw(5) << ' ';
                    for (int j = 0; j < vec.size(); j++) {
                        if (vec.at(j) < i) {
                            std::cout << '*';
                        }
                        else {
                            std::cout << ' ';
                        }
                    }
                    max2--;
                    std::cout << std::endl;
                }
            }
            file_in.close();
        }
        else {
            return 1;
        }
    }
}