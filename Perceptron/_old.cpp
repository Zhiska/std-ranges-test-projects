#include <iostream>

#include "Timer.h"
#include "Random.h"

#include <array>
#include <random>
#include <algorithm>

std::array<double, 3> w;    
int K = 512;    
int k{}, y;    
float mi = 0.1, s{};

std::pair<float, float> points[4]{ {0,0}, {0,1}, {1,0}, {1,1} };    
int vals[4]{0,0,0,1};  

int main() {
    Timer t;

    std::generate(w.begin(), w.end(), [&]() mutable { return Random::Normalised(); });

    std::cout << "Starting coefficients: " << w[1] / w[2] << w[0] / w[2] << '\n';

    while (k < K) {
        for (auto x : points) {
            int dd = vals[k % 4]; /

            s = x.first * w[1] + x.second * w[2] - w[0];

            if (s >= 0.)
                y = 1;
            else
                y = 0;

            w[0] = w[0] - mi * (dd - y);     
            w[1] = w[1] + mi * (dd - y) * x.first; 
            w[2] = w[2] + mi * (dd - y) * x.second; 

            k += 1;
        }
    }

    std::cout << "Learned coefficients: " << w[1] / w[2] << w[0] / w[2] << '\n';

}