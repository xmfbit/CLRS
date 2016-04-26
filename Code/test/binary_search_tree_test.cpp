#include "gtest/gtest.h"
#include "data_structure/binary_search_tree.hpp"
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <set>
namespace {
    using namespace alg;
    using std::vector;
    TEST(BSTTestEmpty, EmptyTree) {
        BinarySearchTree<int> t;
        EXPECT_EQ(t.size(), 0);
        EXPECT_TRUE(t.empty());
    }
    TEST(BSTTestInsert, InsertNode) {
        BinarySearchTree<int> t;
        std::set<int> s;
        const int N = 100;
        for (int i = 0; i < N; ++i) {
            t.insert(i);
            s.insert(i);
        }
        EXPECT_EQ(t.size(), N);
    }

    class BSTTest:public ::testing::Test {
    protected:
        void SetUp() {
            const int N = 100;
            for (int i = 0; i < N; ++i) {
                auto rand_val = rand() % 1000;
                v_.push_back(rand_val);
                t_.insert(rand_val);
            }
        }
        vector<int> v_;
        BinarySearchTree<int> t_;
    };
    TEST_F(BSTTest, GetMinMaxValue) {
        auto minv = *std::min_element(v_.cbegin(), v_.cend());
        auto maxv = *std::max_element(v_.cbegin(), v_.cend());
        EXPECT_EQ(minv, *(t_.get_minimum()));
        EXPECT_EQ(maxv, *(t_.get_maximum()));
    }
    TEST_F(BSTTest, InOrderTravesal) {
        vector<int> sorted = v_;
        std::sort(sorted.begin(), sorted.end());
        auto it = std::unique(sorted.begin(), sorted.end());
        sorted.erase(it, sorted.end());
        vector<int> inorderV;
        t_.writeIntoContainer(std::back_inserter(inorderV));
        EXPECT_EQ(sorted, inorderV);
    }
    TEST_F(BSTTest, Search) {
        auto it = t_.search(v_[0]);
        EXPECT_EQ(*it, v_[0]);
        it = t_.search(10000);
        EXPECT_EQ(it, t_.end());
    }

    struct StringLenComperator {
        int operator()(const std::string& lhs, const std::string& rhs) const {
            if(lhs.size() < rhs.size()) return -1;
            if(lhs.size() > rhs.size()) return 1;
            return 0;
        }
    };
    TEST(BSTTestUserDefineComperator, StringComp) {
        BinarySearchTree<std::string, StringLenComperator> stringTree;
        EXPECT_TRUE(stringTree.empty());
        vector<std::string> strings {"Hello", "Programming", "You"};
        stringTree.insert(strings[0]);
        stringTree.insert(strings[1]);
        stringTree.insert(strings[2]);
        EXPECT_EQ(stringTree.size(), 3);
        EXPECT_EQ(strings[1], *stringTree.get_maximum());
        EXPECT_EQ(strings[2], *stringTree.get_minimum());
    }
}