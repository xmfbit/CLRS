#ifndef CLRS_INSERTION_SORT_HPP
#define CLRS_INSERTION_SORT_HPP

#include <iterator>   // for std::iterator_traits
#include <functional> // for std::less

namespace alg {
    template<typename Iterator, typename Comp = std::less<typename std::iterator_traits<Iterator>::value_type>>
    void insertion_sort(const Iterator& first, const Iterator& last, const Comp &comp = Comp()) {
        if(first == last)   return;
        for (Iterator it = first + 1; it != last; ++it) {
            auto key = *it;
            Iterator forward_it = it - 1;
            for (; forward_it - first >= 0 && !comp(*forward_it, key); --forward_it) {
                *(forward_it + 1) = *forward_it;
            }
            *(forward_it + 1) = key;
        }
    }

    // Insertion sort recursively
    template<typename Iterator, typename Comp>
    static void insertion_sort_recursive_(const Iterator& first, const Iterator& last, const Comp &comp) {
        if (first == last) return;
        insertion_sort_recursive_(first, last - 1, comp);
        auto key = *last;
        Iterator it = last;
        for (; it != first && comp(key, *(it - 1)); --it) {
            *it = *(it - 1);
        }
        *it = key;
    }

    template<typename Iterator, typename Comp = std::less<typename std::iterator_traits<Iterator>::value_type>>
    void insertion_sort_recursive(const Iterator& first, const Iterator& last, const Comp &comp = Comp()) {
        if (first == last) return;
        insertion_sort_recursive_(first, last - 1, comp);
    }
} // end of namespace alg
#endif // CLRS_INSERTION_SORT_HPP
