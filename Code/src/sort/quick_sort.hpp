#ifndef CLRS_QUICK_SORT_HPP
#define CLRS_QUICK_SORT_HPP

#include <iterator>
#include <utility>

namespace alg {
    template <typename Iterator, typename Comp = std::less<typename std::iterator_traits<Iterator>::value_type>>
    static Iterator _partition(const Iterator& first, const Iterator& last, const Comp& comp = Comp()) {
        typedef typename std::iterator_traits<Iterator>::value_type value_type;
        value_type x = *last;
        // 循环不变式：a[p, i]始终不大于x, a[i+1, j-1]始终大于x, a[j, r-1]不定，a[r]是枢纽元素
        size_t len = last - first;
        Iterator i = first - 1;
        for(Iterator j = first; j != last; ++j) {
            if(!comp(x, *j)) {
                std::swap(*j, *++i);
            }
        }
        std::swap(*last, *++i);
        return i;
    };

    template <typename Iterator, typename Comp = std::less<typename std::iterator_traits<Iterator>::value_type>>
    void quick_sort(const Iterator& first, const Iterator& last, const Comp& comp = Comp()) {
        if(first == last || first == last - 1) return;
        Iterator pivot_iter = _partition(first, last - 1, comp);
        quick_sort(first, pivot_iter, comp);
        quick_sort(pivot_iter+1, last, comp);
    };
} // end of namespace alg

#endif // end of file quick_sort.hpp