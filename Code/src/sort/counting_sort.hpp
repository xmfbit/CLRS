#ifndef CLRS_COUNTING_SORT_HPP
#define CLRS_COUNTING_SORT_HPP

#include <stdio.h>
#include <string.h>
#include <iterator>
namespace alg {
    template<typename Iterator>
    /*
     * counting_sort 能够在线性时间复杂度内对已知范围的整数序列进行排序
     */
    void counting_sort(const Iterator& first, const Iterator& last, int max_val) {
        auto dis = std::distance(first, last);
        if(dis <= 1)    return;
        int* b = new int[dis];
        int i = 0;
        auto it = first;
        // 将原始数组中的元素复制到b中
        for(; it != last; ++it) {
            b[i++] = *it;
        }
        // 使用c计数，c[i]为原始数组中不大于数i的元素的个数
        int *c = new int[max_val + 1];
        memset(c, 0, sizeof(int) * (max_val + 1));
        for(it = first; it != last; ++it) {
            c[*it]++;
        }

        for(i = 1; i <= max_val; ++i) {
            c[i] += c[i-1];
        }

        // 从原始数组的尾端开始遍历，找到其对应的位置即c[*it]-1（因为下标从0开始）
        for(std::advance(it = first, dis - 1); it != first - 1; --it) {
            b[--c[*it]] = *it;
        }

        for(i = 0, it = first; it != last; ++it) {
            *it = b[i++];
        }
        delete[] b;
        delete[] c;
    }
} // end of namespace alg
#endif // end of file counting_sort.hpp