#ifndef CLRS_BUBBLE_SORT_HPP
#define CLRS_BUBBLE_SORT_HPP

#include <utility>    // for std::swap
#include <iterator>   // for std::iterator_traits
#include <functional> // for std::less
namespace alg {
    template <typename Iterator, typename Comp = std::less<typename std::iterator_traits<Iterator>::value_type>>
    void bubble_sort(const Iterator& first, const Iterator& last, const Comp& comp = Comp()) {
        if(first == last) return;
        for(Iterator it = first; it != last - 1; ++it) {
            for(Iterator forward_it = last - 1; forward_it != it; --forward_it) {
                if(comp(*forward_it, *(forward_it - 1))) std::swap(*forward_it, *(forward_it-1));
            }
        }
    };
} // end of namespace alg

#endif //CLRS_BUBBLE_SORT_HPP
