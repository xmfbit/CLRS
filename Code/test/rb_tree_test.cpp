#include "gtest/gtest.h"
#include "data_structure/rb_tree.hpp"
#include <algorithm>
#include <set>
namespace {
    using namespace alg;
    using namespace std;
    TEST(RB_TreeEmpty, Empty) {
        RBTree<int> tree;
        EXPECT_TRUE(tree.empty());
        EXPECT_EQ(tree.size(), 0);
    }

    TEST(RB_Tree, InsertAndErase) {
        set<int> nums;
        const int N = 1000;
        RBTree<int> tree;
        for(int i = 0; i < N; ++i) {
            int val = rand() % N;
            nums.insert(val);
            tree.insert(val);
        }
        vector<int> array;
        array.insert(array.begin(), nums.cbegin(), nums.cend());
        sort(array.begin(), array.end());
        vector<int> tree_out;
        tree_out.reserve(array.size());
        tree.outputByInorderTraversal(back_inserter(tree_out));
        EXPECT_EQ(array, tree_out);
        EXPECT_EQ(tree.size(), array.size());

        // erase element
        for(int i = 0; i < N; ++i) {
            int val = rand() % N;
            nums.erase(val);
            tree.erase(val);
        }
        array.clear();
        array.insert(array.begin(), nums.cbegin(), nums.cend());
        sort(array.begin(), array.end());
        tree_out.clear();
        tree.outputByInorderTraversal(back_inserter(tree_out));
        //EXPECT_EQ(array, tree_out);
        //EXPECT_EQ(tree.size(), array.size());

    }
}