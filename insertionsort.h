#ifndef INTROSORT_INSERTION_SORT_H
#define INTROSORT_INSERTION_SORT_H

#include <iterator>
#include <climits>
#include <limits>

namespace introsort_implementation {

    template<typename RandomIterator, typename Comparator>
    bool insertion_sort(RandomIterator begin, RandomIterator end, Comparator comp,
                        const int MAX_DIST = std::numeric_limits<int>::max()) {

        for (auto i = begin + 1; i < end; ++i){
            auto x = std::move(*i);
            decltype(i) j;
            int d = 0;

            for (j = i; j > begin && comp(x, *(j - 1)); j--){
                *j = std::move(*(j - 1));

                if (++d > MAX_DIST)
                    return false;
            }

            *j = x;
        }

        return true;
    };
}

#endif //INTROSORT_INSERTION_SORT_H
