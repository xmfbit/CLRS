#ifndef CLRS_BINARY_SEARCH_TREE_HPP
#define CLRS_BINARY_SEARCH_TREE_HPP

#include <utility>
#include <functional>

namespace alg {
    template<typename T>
    struct Comperator {
        int operator()(const T& lhs, const T& rhs) const {
            if(std::less<T>()(lhs, rhs))  return -1;
            if(std::less<T>()(rhs, lhs))  return 1;
            return 0;
        }
    };

    template <typename T, typename Comp = Comperator<T>>
    class BinarySearchTree {
    private:
        typedef size_t size_type;
        // node in the tree
        struct node {
            T val_;
            node* left_;
            node* right_;
            size_t idx_;
            node(const T& val):val_(val), left_(nullptr), right_(nullptr), idx_(0) {}
            node(const T& val, size_t idx):val_(val), left_(nullptr), right_(nullptr), idx_(idx) {}
        };

        size_type sz_;
        node* root_;
        Comp comp_ = Comp();
        // in-order traversal
        template<typename Op>
        void inOrderTraversal(node* n, const Op& op) {
            if(n == nullptr)    return;
            if(n->left_ != nullptr) inOrderTraversal(n->left_, op);
            op(n);
            if(n->right_ != nullptr)    inOrderTraversal(n->right_, op);
        }
        template<typename Op>
        void inOrderTraversal(const Op& op) {
            inOrderTraversal(root_, op);
        }

        // post-order traversal
        template<typename Op>
        void postOrderTraversal(node* n, const Op& op) {
            if(n == nullptr)    return;
            if(n->left_ != nullptr) postOrderTraversal(n->left_, op);
            if(n->right_ != nullptr)    postOrderTraversal(n->right_, op);
            op(n);
        }
        template<typename Op>
        void postOrderTraversal(const Op& op) {
            postOrderTraversal(root_, op);
        }

        // pre-order traversal
        template<typename Op>
        void preOrderTraversal(node* n, const Op& op) {
            if(n == nullptr)    return;
            op(n);
            if(n->left_ != nullptr) preOrderTraversal(n->left_, op);
            if(n->right_ != nullptr)    preOrderTraversal(n->right_, op);
        }
        template<typename Op>
        void preOrderTraversal(const Op& op) {
            preOrderTraversal(root_, op);
        }
    public:
        class Iterator {
        private:
            Iterator():ptr_(nullptr) {}
            Iterator(node* n):ptr_(n) {}
            node* ptr_;
            friend class BinarySearchTree;
        public:
            // can't modify the value of the node outside to keep the property of BST
            const T& operator *() {
                return ptr_->val_;
            }
            bool operator == (const Iterator& that) const{
                if(&that == this)   return true;
                if(that.ptr_ == nullptr && ptr_ == nullptr) return true;
                if(that.ptr_ == nullptr || ptr_ == nullptr) return false;
                return ptr_->val_ == that.ptr_->val_;
            }
        };
    private:
        Iterator search(const T& val, node* n) const {
            if(n == nullptr) return Iterator();
            if(comp_(n->val_, val) == 0)   return Iterator(n);
            else if(comp_(n->val_, val) < 0)  return search(val, n->right_);
            else return search(val, n->left_);
        }

        node* insert(const T& val, node* x) {
            if(x == nullptr) x = new node(val, sz_++);
            else if(comp_(x->val_, val) < 0) {
                x->right_ = insert(val, x->right_);
            } else if(comp_(x->val_ , val) > 0) {
                x->left_ = insert(val, x->left_);
            }
            return x;
        }

    public:
        enum OrderType {PreOrder, PostOrder, InOrder};
        BinarySearchTree():sz_(0), root_(nullptr) {}

        // retuen a null iterator
        Iterator end() const {
            return Iterator();
        }
        // search for a value
        Iterator search(const T& val) const {
            return search(val, root_);
        }
        // insert value
        void insert(const T& val) {
            root_ = insert(val, root_);
        }

        // get the iterator of the minimum value
        Iterator get_minimum() {
            if(empty()) return Iterator();
            node* p = root_;
            while(p->left_ != nullptr) {
                p = p->left_;
            }
            return Iterator(p);
        }

        Iterator get_maximum() {
            if(empty()) return Iterator();
            node* p = root_;
            while(p->right_ != nullptr) {
                p = p->right_;
            }
            return Iterator(p);
        }
        // return the number of nodes in the tree
        inline size_type size() const {
            return sz_;
        }

        inline bool empty() const {
            return sz_ == 0;
        }
        // print the binary tree to output stream in some order
        void print(std::ostream& os, char ch, OrderType order) {
            auto f = [&](const node* n) {os << n->val_ << ch; };
            switch(order) {
                case InOrder:
                    inOrderTraversal(f);
                    break;
                case PostOrder:
                    postOrderTraversal(f);
                    break;
                case PreOrder:
                    preOrderTraversal(f);
                default:
                    break;
            }
        }
        // write the tree node into a container
        template<typename ForwardIterator>
        void writeIntoContainer(const ForwardIterator& first) {
            auto f = [](const node* n, ForwardIterator& it) {*it++ = n->val_;};
            auto it = first;
            inOrderTraversal(std::bind(f, std::placeholders::_1, std::ref(it)));
        }
        // de-construction
        ~BinarySearchTree() {
            auto f = [](const node* p) {delete p; };
            postOrderTraversal(root_, f);
        }
    }; // end of class binary_search_tree
} // end of namespace alg
#endif // end of binary_search_tree.hpp