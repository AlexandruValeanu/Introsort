#ifndef INTROSORT_TESTS_H
#define INTROSORT_TESTS_H

#include <algorithm>
#include <utility>
#include <vector>
#include <random>

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

#endif //INTROSORT_TESTS_H
