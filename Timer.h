#pragma once

#include <iostream>
#include <chrono>

struct Timer {
    std::chrono::time_point<std::chrono::high_resolution_clock> s;
    std::chrono::time_point<std::chrono::high_resolution_clock> f;

    Timer() {
        s = std::chrono::high_resolution_clock::now();
    }
    ~Timer() {
        f = std::chrono::high_resolution_clock::now();
        std::cout << "Scoped timer time: " << std::chrono::duration<double, std::nano>(f - s).count() << "ns\n";
    }
};
