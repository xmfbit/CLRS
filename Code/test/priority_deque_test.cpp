#include "gtest/gtest.h"
#include "data_structure/priority_deque.hpp"
#include <ctime>
#include <cstdlib>
#include <functional>
#include <vector>
#include <algorithm>

namespace {
    using namespace alg;
    TEST(PriorityDequeTest, EmptyDeque) {
        priority_deque<int> pd;
        EXPECT_EQ(pd.size(), 0);
    }

    TEST(PriorityDequeTest, InsertAndMaximum) {
        std::vector<int> v;
        srand(time(nullptr));

        for(int i = 0; i < 10; ++i) {
            v.push_back(rand() % 100);
        }
        int maxV = *std::max_element(v.begin(), v.end());
        int minV = *std::min_element(v.begin(), v.end());

        priority_deque<int> pd;
        for(auto i : v) {
            pd.insert(i);
        }
        EXPECT_EQ(pd.maximum(), minV);

        priority_deque<int, std::greater<int>> pd_max;
        for(auto i : v) {
            pd_max.insert(i);
        }
        EXPECT_EQ(pd_max.maximum(), maxV);
    }

    TEST(PriorityDequeTest, Extract_Max) {
        std::vector<int> v;
        srand(time(nullptr));

        for(int i = 0; i < 1000; ++i) {
            v.push_back(rand() % 100);
        }
        priority_deque<int> pd;
        for(auto i : v) {
            pd.insert(i);
        }
        std::sort(v.begin(), v.end());
        auto iter = v.begin();
        while(!pd.empty()) {
            int val = pd.extract_max();
            EXPECT_EQ(val, *iter);
            ++iter;
        }
    }

    struct StringLenComp {
        bool operator()(const std::string& lhs, const std::string& rhs) const {
            return lhs.length() > rhs.length();
        }
    };

    TEST(PriorityDequeTest, UserDefineStructure) {
        priority_deque<std::string, StringLenComp> pd;
        pd.insert("Hello");
        pd.insert("I");
        pd.insert("Programming");
        EXPECT_EQ(pd.extract_max(), "Programming");
        EXPECT_EQ(pd.extract_max(), "Hello");
        EXPECT_EQ(pd.extract_max(), "I");
        EXPECT_TRUE(pd.empty());
    }
}