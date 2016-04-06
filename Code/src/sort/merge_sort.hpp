#ifndef CLRS_MERGE_SORT_HPP
#define CLRS_MERGE_SORT_HPP

#include <iterator>
#include <functional>

namespace alg {
    template <typename Iterator, typename Comp>
    static void merge(const Iterator& first, const Iterator& mid, const Iterator& last, const Comp& comp) {
        typedef typename std::iterator_traits<Iterator>::value_type value_type;
        int len = last - first;
        value_type * aux = new value_type[len];

        Iterator p = first, q = mid;
        int k = 0;
        while(p != mid && q != last) {
            if(comp(*p, *q)) aux[k++] = *p++;
            else aux[k++] = *q++;
        }
        while(p != mid) {
            aux[k++] = *p++;
        }
        while(q != last) {
            aux[k++] = *q++;
        }

        for(int i = 0; i < len; ++i) {
            *(first + i) = aux[i];
        }
        delete [] aux;
    };

    template <typename Iterator, typename Comp = std::less<typename std::iterator_traits<Iterator>::value_type>>
    void merge_sort(const Iterator& first, const Iterator& last, const Comp& comp = Comp()) {
        if(first == last || first == last - 1)   return;
        Iterator mid = (last - first) / 2 + first;
        merge_sort(first, mid, comp);
        merge_sort(mid, last, comp);
        merge(first, mid, last, comp);
    };
}
#endif //CLRS_MERGE_SORT_HPP
