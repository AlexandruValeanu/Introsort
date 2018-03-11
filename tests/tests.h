#ifndef INTROSORT_TESTS_H
#define INTROSORT_TESTS_H

#include <algorithm>
#include <utility>
#include <vector>
#include <random>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <cassert>
#include <introsort.h>
#include <iostream>
#include <iomanip>

template <typename T>
class Tests{
private:

    std::random_device rd{};
    std::mt19937 e1{rd()}, e2{rd()};
    std::uniform_int_distribution<> d1;
    std::uniform_int_distribution<T> d2;

    int nextPosition(){
        return d1(e1);
    }

    T nextValue(){
        return d2(e2);
    }

    void perform_swaps1(std::vector<T> &v, int SWAPS){
        while (SWAPS--){
            int x = nextPosition();
            int y = std::min(x + 1, (int)v.size() - 1);

            std::swap(v[x], v[y]);
        }
    }

    void perform_swaps2(std::vector<T> &v, int SWAPS){
        while (SWAPS--){
            int x = nextPosition();
            int y = nextPosition();

            std::swap(v[x], v[y]);
        }
    }

    int N, V;

public:

    Tests(int _N, int _V) : N(_N), V(_V){
        std::uniform_int_distribution<> x{0, N - 1};
        std::uniform_int_distribution<T> y{0, V - 1};

        d1 = std::move(x);
        d2 = std::move(y);
    }

    std::vector<T> random_order(){
        std::vector<T> v;
        v.resize(N);

        for (T &x: v)
            x = nextValue();

        return v;
    }

    std::vector<T> sorted_ascending(){
        std::vector<T> v = random_order();
        std::sort(v.begin(), v.end());

        return v;
    }

    std::vector<T> sorted_decreasing(){
        std::vector<T> v = random_order();
        std::sort(v.begin(), v.end());
        std::reverse(v.begin(), v.end());

        return v;
    }

    std::vector<T> mostly_sorted1_asc(int SWAPS){
        std::vector<T> v = sorted_ascending();
        perform_swaps1(v, SWAPS);

        return v;
    }

    std::vector<T> mostly_sorted2_asc(int SWAPS){
        std::vector<T> v = sorted_ascending();
        perform_swaps2(v, SWAPS);

        return v;
    }

    std::vector<T> mostly_sorted1_desc(int SWAPS){
        std::vector<T> v = sorted_decreasing();
        perform_swaps1(v, SWAPS);

        return v;
    }

    std::vector<T> mostly_sorted2_desc(int SWAPS){
        std::vector<T> v = sorted_decreasing();
        perform_swaps2(v, SWAPS);

        return v;
    }
};

template <typename T>
auto get_time_introsort(std::vector<T> v){
    std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();

    introsort(v.begin(), v.end());
    assert(std::is_sorted(v.begin(), v.end()));

    std::chrono::high_resolution_clock ::time_point end = std::chrono::high_resolution_clock::now();
    auto item = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

    return item;
}

template <typename T>
auto get_time_std_sort(std::vector<T> v){
    std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();

    std::sort(v.begin(), v.end());
    assert(std::is_sorted(v.begin(), v.end()));

    std::chrono::high_resolution_clock ::time_point end = std::chrono::high_resolution_clock::now();
    auto item = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

    return item;
}

template <typename T>
void print_vector(std::vector<T> v, std::ostream &out){
    for (size_t i = 0; i < v.size(); i++){
        out << v[i];

        if (i + 1 < v.size())
            out << " ";
        else
            out << std::endl;
    }
};

template <typename T>
void test(int N, int V, auto &times_introsort, auto &times_sort){
    assert(times_introsort.size() == 7);
    assert(times_sort.size() == 7);
    Tests<T> tests{N, V};

    auto v = tests.random_order();
    times_introsort[0].push_back(get_time_introsort(v));
    times_sort[0].push_back(get_time_std_sort(v));

    v = tests.sorted_ascending();
    times_introsort[1].push_back(get_time_introsort(v));
    times_sort[1].push_back(get_time_std_sort(v));

    v = tests.sorted_decreasing();
    times_introsort[2].push_back(get_time_introsort(v));
    times_sort[2].push_back(get_time_std_sort(v));

    v = tests.mostly_sorted1_asc(N / 10);
    times_introsort[3].push_back(get_time_introsort(v));
    times_sort[3].push_back(get_time_std_sort(v));

    v = tests.mostly_sorted1_desc(N / 10);
    times_introsort[4].push_back(get_time_introsort(v));
    times_sort[4].push_back(get_time_std_sort(v));

    v = tests.mostly_sorted2_asc(N / 10);
    times_introsort[5].push_back(get_time_introsort(v));
    times_sort[5].push_back(get_time_std_sort(v));

    v = tests.mostly_sorted2_desc(N / 10);
    times_introsort[6].push_back(get_time_introsort(v));
    times_sort[6].push_back(get_time_std_sort(v));
}

/**
 *  0 -> N = 100;          V = 100
 *  1 -> N = 1'000;        V = 500
 *  2 -> N = 10'000;       V = 2'000
 *  3 -> N = 100'000;      V = 15'000
 *  4 -> N = 1'000'000;    V = 40'000
 *  5 -> N = 5'000'000;    V = 80'000
 *  6 -> N = 10'000'000;   V = 125'000
 *
 *  7 -> N = 100;          V = 2'000'000'000
 *  8 -> N = 1'000;        V = 2'000'000'000
 *  9 -> N = 10'000;       V = 2'000'000'000
 * 10 -> N = 100'000;      V = 2'000'000'000
 * 11 -> N = 1'000'000;    V = 2'000'000'000
 * 12 -> N = 10'000'000;   V = 2'000'000'000
 * 13 -> N = 100'000'000;  V = 2'000'000'000
 */


template <typename T>
double average(std::vector<T> v){
    auto sum = std::accumulate(v.begin(), v.end(), 0);
    return static_cast<double >(sum) / v.size();
}

void gen_data(){
    std::vector<std::pair<int,int>> pairs(14);
    pairs[ 0] = {100,             100};
    pairs[ 1] = {1'000,           500};
    pairs[ 2] = {10'000,        2'000};
    pairs[ 3] = {100'000,      15'000};
    pairs[ 4] = {1'000'000,    40'000};
    pairs[ 5] = {5'000'000,    80'000};
    pairs[ 6] = {10'000'000,  125'000};

    pairs[ 7] = {100,         2'000'000'000};
    pairs[ 8] = {1'000,       2'000'000'000};
    pairs[ 9] = {10'000,      2'000'000'000};
    pairs[10] = {100'000,     2'000'000'000};
    pairs[11] = {1'000'000,   2'000'000'000};
    pairs[12] = {5'000'000,   2'000'000'000};
    pairs[13] = {10'000'000,  2'000'000'000};

    std::ofstream out("results.txt");

    for (int i = 0; i < 14; i++){
        const std::string str = "data" + std::to_string(i);
        out << str << std::endl;
        std::cerr << str << std::endl;

        int N = pairs[i].first;
        int V = pairs[i].second;

        out << N << " " << V << std::endl;

        std::vector<std::vector<unsigned long long>> times_introsort(7), times_sort(7);

        int ITERATIONS = 10;

        while (ITERATIONS--){
            test<int>(N, V, times_introsort, times_sort);
        }

        for (int i = 0; i < 7; i++){
            out << std::fixed << std::setprecision(2);
            out << average(times_introsort[i]) << " " << average(times_sort[i]) << std::endl;
        }

        out << std::endl;
    }

    out.close();
}



#endif //INTROSORT_TESTS_H
