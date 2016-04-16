#ifndef CLRS_HEAP_SORT_HPP
#define CLRS_HEAP_SORT_HPP

#include <iostream>
#include <functional>
#include <utility>

namespace alg {
    static inline int LCHILD(int x) {
        return ((x + 1) << 1) - 1;   // ! 移位运算比算术运算符优先级别低！不要忘记括号！
    }

    static inline int RCHILD(int x) {
        return (x + 1) << 1;
    }
    /*
     * helper function
     */
    // sink the ith node to its right position
    template<typename T, typename Comp = std::less<T>>
    static void sink(T* arr, int i, int size, const Comp& comp = Comp()) {
        int largest = i;
        int left = LCHILD(i);
        int right = RCHILD(i);
        if(left < size && comp(*(arr+i), *(arr+left)))  largest = left;
        if(right < size && comp(*(arr+largest), *(arr+right)))  largest = right;
        if(i != largest) {
            // swap a[i] and a[largest]
            std::swap(*(arr+i), *(arr+largest));
            sink(arr, largest, size, comp);
        }
    }

    // build a max-root heap given an array with random order
    template<typename T, typename Comp = std::less<T>>
    static void build_maxheap(T* arr, int size, const Comp& comp = Comp()) {
        int first_leaf = size >> 1;
        for(int i = first_leaf - 1; i >= 0; i--) {
            sink(arr, i, size, comp);
        }
    }

    template<typename T, typename Comp = std::less<T>>
    void heap_sort(T* arr, int size, const Comp& comp = Comp()) {
        if(size <= 1)   return;
        // build the heap
        build_maxheap(arr, size, comp);
        while(size-- > 0) {
            // a[0] is the maximum value, we swap it with a[end]
            // (this is also its final position) after sorting
            // and then sink a[0]
            std::swap(*(arr + size), *arr);
            sink(arr, 0, size, comp);
        }
    }
} // end of namesapce alg
#endif // end of file heap_sort.hpp