#ifndef INTROSORT_INTRO_SORT_H
#define INTROSORT_INTRO_SORT_H

#include <utility>
#include <random>
#include <algorithm>
#include <cassert>
#include <vector>
#include "sorting_networks.h"
#include "insertionsort.h"

template <typename Iterator>
void introsort(Iterator begin, Iterator end);

namespace introsort_implementation {

    constexpr int CUT_OFF = 25;
    constexpr int MAX_DIST = 15;

    template<typename RandomIterator, typename Comparator>
    typename std::iterator_traits<RandomIterator>::value_type
    choose_pivot(RandomIterator low, RandomIterator high, Comparator comp) {
        static std::random_device rd;
        static std::mt19937 mt(rd());
        static std::uniform_int_distribution<> distribution(0, std::numeric_limits<int>::max());

        const auto length = high - low + 1;

        typename std::iterator_traits<RandomIterator>::value_type x = *(low + distribution(mt) % length);
        typename std::iterator_traits<RandomIterator>::value_type y = *(low + distribution(mt) % length);
        typename std::iterator_traits<RandomIterator>::value_type z = *(low + distribution(mt) % length);

        sort3(x, y, z, comp);
        return y;
    }

    template<typename RandomIterator, typename Comparator>
    std::pair<RandomIterator, RandomIterator>
    three_way_partition(RandomIterator low, RandomIterator high, Comparator comp) {
        assert(high - low + 1 >= 7);

        RandomIterator lt = low;
        RandomIterator gt = high;
        auto pivot = choose_pivot(low, high, comp);

        auto i = low;
        while (i <= gt) {
            if (comp(*i, pivot))
                std::iter_swap(lt++, i++);
            else if (comp(pivot, *i))
                std::iter_swap(i, gt--);
            else
                i++;
        }

        return std::make_pair(lt, gt);
    }

    template<typename RandomIterator, typename Comparator>
    void impl_intro_sort(RandomIterator low, RandomIterator high, unsigned depth, Comparator comp) {
        while (low <= high) {
            const auto length = high - low + 1;

            /* Trivial case */
            if (length <= 1)
                return;

            /* For very small ranges (< 7 elements) we use a sorting network */
            switch (length) {
                case 2:
                    sort2(*low, *(low + 1), comp);
                    return;
                case 3:
                    sort3(*low, *(low + 1), *(low + 2), comp);
                    return;
                case 4:
                    sort4(*low, *(low + 1), *(low + 2), *(low + 3), comp);
                    return;
                case 5:
                    sort5(*low, *(low + 1), *(low + 2), *(low + 3), *(low + 4), comp);
                    return;
                case 6:
                    sort6(*low, *(low + 1), *(low + 2), *(low + 3), *(low + 4), *(low + 5), comp);
                    return;
                default:
                    break;
            }

            /* We have less than CUT_OFF elements so we must use insertion sort */
            if (length <= CUT_OFF) {
                insertion_sort(low, high + 1, comp);
                return;
            }

            /* Quicksort is not behaving properly so we switch to heapsort */
            if (depth == 0) {
                std::make_heap(low, high + 1, comp);
                std::sort_heap(low, high + 1, comp);
                return;
            }

            // try gambling ? (optimization)
            if (insertion_sort(low, high + 1, comp, MAX_DIST))
                return;

            /*
             * We use 3-way partition in order to get 3 ranges:
             *  a[low..pit.first) ++ a[pit.first..pit.second] ++ a(pit.second..high]
             *      < pivot                  == pivot                  > pivot
             */
            auto pit = three_way_partition(low, high, comp);

            /*
             * If len(a[low..pit.first)) < len(a(pit.second..high]) then
             * transform sort(a(pit.second..high]) into tail recursion
             * Otherwise transform sort(a[low..pit.first)) into tail recursion
             */
            if (pit.first - low < high - pit.second){
                impl_intro_sort(low, pit.first - 1, depth - 1, comp);
                low = pit.second + 1;
            }
            else{
                impl_intro_sort(pit.second + 1, high, depth - 1, comp);
                high = pit.first - 1;
            }

            depth -= 1;
        }
    };

    template<typename RandomIterator>
    unsigned find_maximal_depth(RandomIterator low, RandomIterator high) {
        unsigned lg2 = 0;

        for (auto d = high - low + 1; d != 0; d >>= 1, ++lg2);

        return lg2 * 2;
    }

    template <typename RandomIterator>
    void introsort(RandomIterator begin, RandomIterator end, std::random_access_iterator_tag){
        if (begin != end)
            impl_intro_sort(begin, --end, find_maximal_depth(begin, end),
                            std::less<typename std::iterator_traits<RandomIterator>::value_type>());
    };

    template <typename BidirectionalIterator>
    void introsort(BidirectionalIterator begin, BidirectionalIterator end, std::bidirectional_iterator_tag){
        std::vector<typename std::iterator_traits<BidirectionalIterator>::value_type> container(begin, end);
        introsort(container.begin(), container.end(), std::random_access_iterator_tag());
        std::move(container.begin(), container.end(), begin);
    };

    template <typename ForwardIterator>
    void introsort(ForwardIterator begin, ForwardIterator end, std::forward_iterator_tag){
        std::vector<typename std::iterator_traits<ForwardIterator>::value_type> container(begin, end);
        introsort(container.begin(), container.end(), std::random_access_iterator_tag());
        std::move(container.begin(), container.end(), begin);
    };

    template <typename Iterator>
    void introsort(Iterator begin, Iterator end){
        introsort_implementation::introsort(begin, end, typename std::iterator_traits<Iterator>::iterator_category());
    };
}

template <typename Iterator>
void introsort(Iterator begin, Iterator end){
    introsort_implementation::introsort(begin, end);
};

#endif //INTROSORT_INTRO_SORT_H
