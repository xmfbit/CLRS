#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "gtest/gtest.h"
#include "sort/insertion_sort.hpp"
#include "sort/select_sort.hpp"
#include "sort/bubble_sort.hpp"
#include "sort/merge_sort.hpp"

namespace {
    using namespace alg;

    struct Compare_int {
        bool operator()(int lhs, int rhs) const {
            return lhs < rhs;
        }
    } comp_int;

    static std::vector<int> generate_random_vector(int size, int maxVal) {
        std::vector<int> res;
        res.reserve(size);
        std::srand(time(nullptr));
        for(int i = 0; i < size; ++i) {
            res.push_back(std::rand() % maxVal);
        }
        return res;
    }

    TEST(SortTest, InsertionSortTest) {
        std::vector<int> v = generate_random_vector(100, 100);
        std::vector<int> v_sort = v;
        std::sort(v_sort.begin(), v_sort.end());
        insertion_sort(v.begin(), v.end(), comp_int);
        EXPECT_EQ(v, v_sort);

        v = generate_random_vector(1, 10);
        v_sort = v;
        std::sort(v_sort.begin(), v_sort.end());
        insertion_sort(v.begin(), v.end(), comp_int);
        EXPECT_EQ(v, v_sort);
    }

    TEST(SortTest, InsertionSortRecursiveTest) {
        std::vector<int> v = generate_random_vector(100, 100);
        std::vector<int> v_sort = v;
        std::sort(v_sort.begin(), v_sort.end());
        insertion_sort_recursive(v.begin(), v.end(), comp_int);
        EXPECT_EQ(v, v_sort);

        v = generate_random_vector(1, 10);
        v_sort = v;
        std::sort(v_sort.begin(), v_sort.end());
        insertion_sort_recursive(v.begin(), v.end(), comp_int);
        EXPECT_EQ(v, v_sort);
    }

    TEST(SortTest, SelectSortTest) {
        std::vector<int> v = generate_random_vector(100, 100);
        auto v_sort = v;
        std::sort(v_sort.begin(), v_sort.end());
        select_sort(v.begin(), v.end(), comp_int);
        EXPECT_EQ(v, v_sort);

        v = generate_random_vector(1, 10);
        v_sort = v;
        std::sort(v_sort.begin(), v_sort.end());
        select_sort(v.begin(), v.end());
        EXPECT_EQ(v, v_sort);

        // We test the algorithm when using pointer as iterator and std::less<T> as comparator
        v = generate_random_vector(100, 100);
        v_sort = v;
        int* arr = &v[0];
        std::sort(v_sort.begin(), v_sort.end());
        select_sort(arr, arr + 100);
        EXPECT_EQ(v, v_sort);
    }

    TEST(SortTest, BubbleSortTest) {
        std::vector<int> v = generate_random_vector(100, 100);
        auto v_sort = v;
        std::sort(v_sort.begin(), v_sort.end());
        bubble_sort(v.begin(), v.end(), comp_int);
        EXPECT_EQ(v, v_sort);

        v = generate_random_vector(1, 10);
        v_sort = v;
        std::sort(v_sort.begin(), v_sort.end());
        bubble_sort(v.begin(), v.end(), comp_int);
        EXPECT_EQ(v, v_sort);
    }

    TEST(SortTest, MergeSortTest) {
        std::vector<int> v = generate_random_vector(100, 100);
        auto v_sort = v;
        std::sort(v_sort.begin(), v_sort.end());
        merge_sort(v.begin(), v.end(), comp_int);
        EXPECT_EQ(v, v_sort);

        v = generate_random_vector(1, 10);
        v_sort = v;
        std::sort(v_sort.begin(), v_sort.end());
        merge_sort(v.begin(), v.end(), comp_int);
        EXPECT_EQ(v, v_sort);
    }

    TEST(InversionTest, NaiveMethodTest) {
        std::vector<int> v = {1,2,3,4,5};
        EXPECT_EQ(get_inversion_count_naive(v.begin(), v.end()), 0);
        EXPECT_EQ(0, get_inversion_count(v.begin(), v.end()));

        std::vector<int> v2 = {2,1,3,4,0};
        EXPECT_EQ(get_inversion_count_naive(v2.begin(), v2.end()), 5);
        EXPECT_EQ(5, get_inversion_count(v2.begin(), v2.end()));
    }
}
