#ifndef CLRS_SELECT_SORT_HPP
#define CLRS_SELECT_SORT_HPP

#include <utility>    // for std::swap
#include <iterator>   // for std::iterator_traits
#include <functional> // for std::less

namespace alg {
    template<typename Iterator, typename Comp = std::less<typename std::iterator_traits<Iterator>::value_type>>
    void select_sort(const Iterator &first, const Iterator &last, const Comp &comp = Comp()) {
        if (first == last) return;
        for (Iterator it = first; it != last - 1; ++it) {
            Iterator minIt = it;
            for (Iterator backward_it = it + 1; backward_it != last; ++backward_it) {
                if (comp(*backward_it, *minIt)) minIt = backward_it;
            }
            if (minIt != it) std::swap(*it, *minIt);
        }
    };
} // end of namespace alg
#endif // CLRS_SELECT_SORT_HPP
