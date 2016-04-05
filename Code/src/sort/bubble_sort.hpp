#ifndef CLRS_BUBBLE_SORT_HPP
#define CLRS_BUBBLE_SORT_HPP

#include <utility>   // for std::swap

namespace alg {
    template <typename Iterator, typename Comp>
    void bubble_sort(const Iterator& first, const Iterator& last, const Comp& comp) {
        if(first == last) return;
        for(Iterator it = first; it != last - 1; ++it) {
            for(Iterator forward_it = last - 1; forward_it != it; --forward_it) {
                if(comp(*forward_it, *(forward_it - 1))) std::swap(*forward_it, *(forward_it-1));
            }
        }
    };
} // end of namespace alg

#endif //CLRS_BUBBLE_SORT_HPP
