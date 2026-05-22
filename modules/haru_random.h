//
// Created by developer on 2026-05-22.
//

#ifndef HARU_OPENCV_WEB_HARU_RANDOM_H
#define HARU_OPENCV_WEB_HARU_RANDOM_H
#include <random>
using namespace std;
namespace haru {
    int min = 1;
    int max = 7;

    // Initialize a random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(min, max);

    // Generate random number in the range [min, max]
    // int randomValue = distrib(gen);
    int getRandom() {
        return distrib(gen);
    }
}
#endif //HARU_OPENCV_WEB_HARU_RANDOM_H
