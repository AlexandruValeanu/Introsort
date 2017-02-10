#ifndef INTROSORT_INSERTION_SORT_H
#define INTROSORT_INSERTION_SORT_H

#include <iterator>
#include <climits>
#include <limits>

namespace introsort_implementation {

    template<typename RandomIterator, typename Comparator>
    bool insertion_sort(RandomIterator begin, RandomIterator end, Comparator comp,
                        const int MAX_DIST = std::numeric_limits<int>::max()) {
        auto i = begin;

        while (++i != end) {
            const auto &tmp = *i;
            auto j = i;
            int d = 0;

            while (j != begin && comp(tmp, *(j - 1))) {
                *j = *(j - 1);
                --j;

                if (++d > MAX_DIST)
                    return false;
            }

            *j = tmp;
        }

        return true;
    };
}

#endif //INTROSORT_INSERTION_SORT_H
