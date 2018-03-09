#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "introsort.h"
#include <iomanip>
#include "tests.h"

using namespace std;

template <typename T>
auto get_time_introsort(vector<T> v){
    std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();

    introsort(v.begin(), v.end());
    assert(is_sorted(v.begin(), v.end()));

    std::chrono::high_resolution_clock ::time_point end = std::chrono::high_resolution_clock::now();
    auto item = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

    return item;
}

template <typename T>
auto get_time_std_sort(vector<T> v){
    std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();

    sort(v.begin(), v.end());
    assert(is_sorted(v.begin(), v.end()));

    std::chrono::high_resolution_clock ::time_point end = std::chrono::high_resolution_clock::now();
    auto item = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

    return item;
}

template <typename T>
void print_vector(vector<T> v, ostream &out){
    for (size_t i = 0; i < v.size(); i++){
        out << v[i];

        if (i + 1 < v.size())
            out << " ";
        else
            out << endl;
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
double average(vector<T> v){
    auto sum = accumulate(v.begin(), v.end(), 0);
    return static_cast<double >(sum) / v.size();
}

void gen_data(){
    vector<pair<int,int>> pairs(14);
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

    ofstream out("results.txt");

    for (int i = 0; i < 14; i++){
        const string str = "data" + to_string(i);
        out << str << endl;
        cerr << str << endl;

        int N = pairs[i].first;
        int V = pairs[i].second;

        out << N << " " << V << endl;

        vector<vector<unsigned long long>> times_introsort(7), times_sort(7);

        int ITERATIONS = 10;

        while (ITERATIONS--){
            test<int>(N, V, times_introsort, times_sort);
        }

        for (int i = 0; i < 7; i++){
            out << fixed << setprecision(2);
            out << average(times_introsort[i]) << " " << average(times_sort[i]) << endl;
        }

        out << endl;
    }

    out.close();
}

int main() {
//    gen_data();

    vector<int> v{0, 6, 7, 6, 0, 5, 5, 8, 8, 5, 0, 6, 3, 7, 2, 3, 0, 5,
                  3, 5, 2, 7, 8, 9, 6, 8, 1, 6, 3, 4, 2, 4, 0, 9, 6, 1, 3, 3, 8, 5,1,2,1,5,7,1,0,9,8,3,4};

    introsort(v.begin(), v.end());

    cout << v.size() << endl;

    for (auto x: v)
        cout << x << " ";
    cout << endl;

    assert(is_sorted(v.begin(), v.end()));

    return 0;
}