#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "Introsort.h"
#include <forward_list>

using namespace std;

struct Alex{
    int x, y;

    bool operator < (const Alex &other) const{
        if (x != other.x)
            return x < other.x;
        else
            return y < other.y;
    }
};

int main() {
    srand((unsigned int) time(0));
    constexpr int N = 50'000'000;

    vector<int> v{0};

    for (size_t i = 0; i < N; i++){
        int x = rand() % 100'000;
        int y = rand() % 100'000;

        v.push_back(x);
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    if (is_sorted(v.begin(), v.end()))
        cout << "Already sorted\n";

    introsort(v.begin(), v.end());
    assert(is_sorted(v.begin(), v.end()));

    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
    std::cout << "Time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() <<std::endl;

    return 0;
}