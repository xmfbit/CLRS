#include "gtest/gtest.h"
#include "data_structure/d_heap.hpp"
#include <algorithm>
namespace {
    using namespace alg;

    TEST(DHeapTest, EmptyHeap) {
        d_heap<int, 3> heap;
        EXPECT_EQ(heap.size(), 0);
    }

    TEST(DHeapTest, InsertAndMaximum) {
        std::vector<int> v;
        srand(time(nullptr));

        for (int i = 0; i < 1000; ++i) {
            v.push_back(rand() % 100);
        }
        int maxV = *std::max_element(v.begin(), v.end());
        int minV = *std::min_element(v.begin(), v.end());

        d_heap<int, 3> dh;
        for (auto i : v) {
            dh.insert(i);
        }
        EXPECT_EQ(dh.maximum(), minV);

        d_heap<int, 3, std::greater<int>> dh_max;
        for (auto i : v) {
            dh_max.insert(i);
        }
        EXPECT_EQ(dh_max.maximum(), maxV);
    }

    TEST(DHeapTest, Extract_Max) {
        std::vector<int> v;
        srand(time(nullptr));

        for (int i = 0; i < 3000; ++i) {
            v.push_back(rand() % 10000);
        }
        d_heap<int, 4> dh;
        for (auto i : v) {
            dh.insert(i);
        }
        std::sort(v.begin(), v.end());
        auto iter = v.begin();
        while (!dh.empty()) {
            int val = dh.extract_max();
            EXPECT_EQ(val, *iter);
            ++iter;
        }
        std::cout << "\n";
    }

    TEST(DHeapTest, DifferentD) {
        std::vector<int> v;
        srand(time(nullptr));

        for (int i = 0; i < 10; ++i) {
            v.push_back(rand() % 100);
        }
        int maxV = *std::max_element(v.begin(), v.end());
        {
            d_heap<int, 2, std::greater<int>> dh;
            for (auto i: v) {
                dh.insert(i);
            }
            EXPECT_EQ(dh.maximum(), maxV);
        }
        {
            d_heap<int, 5, std::greater<int>> dh;
            for (auto i: v) {
                dh.insert(i);
            }
            EXPECT_EQ(dh.maximum(), maxV);
        }
        {
            d_heap<int, 8, std::greater<int>> dh;
            for (auto i: v) {
                dh.insert(i);
            }
            EXPECT_EQ(dh.maximum(), maxV);
        }
    }
}