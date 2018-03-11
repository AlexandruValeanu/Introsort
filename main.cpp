#include <iostream>
#include <vector>
#include <chrono>
#include <tests/tests.h>
#include "introsort.h"

using namespace std;

int main() {
//    gen_data();

    int N = 1'000'000;

    vector<int> v(N);

    for (int i = 0; i < N; i++){
        v[i] = rand() % 100'000;
    }

    const auto b = v;

    std::chrono::high_resolution_clock::time_point begin1 = std::chrono::high_resolution_clock::now();
    introsort(v.begin(), v.end());
    std::chrono::high_resolution_clock::time_point end1 = std::chrono::high_resolution_clock::now();
    std::cout << "introsort Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end1 - begin1).count() << std::endl;
    assert(is_sorted(v.begin(), v.end()));

    v = b;

    begin1 = std::chrono::high_resolution_clock::now();
    sort(v.begin(), v.end());
    end1 = std::chrono::high_resolution_clock::now();
    std::cout << "std::sort Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end1 - begin1).count() << std::endl;
    assert(is_sorted(v.begin(), v.end()));

    return 0;
}