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
            node* parent_;
            size_t idx_;
            node(const T& val):val_(val), left_(nullptr), right_(nullptr), parent_(nullptr), idx_(0) {}
            node(const T& val, size_t idx):val_(val), left_(nullptr), right_(nullptr), parent_(nullptr), idx_(idx) {}
            node(const T& val, node* parent, size_t idx):val_(val), left_(nullptr), right_(nullptr), parent_(parent), idx_(idx) {}
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
        node* search(const T& val, node* n) const {
            if(n == nullptr) return nullptr;
            if(comp_(n->val_, val) == 0)   return n;
            else if(comp_(n->val_, val) < 0)  return search(val, n->right_);
            else return search(val, n->left_);
        }

        node* insert(const T& val, node* x, node* parent) {
            if(x == nullptr) x = new node(val, parent, sz_++);
            else if(comp_(x->val_, val) < 0) {
                x->right_ = insert(val, x->right_, x);
            } else if(comp_(x->val_ , val) > 0) {
                x->left_ = insert(val, x->left_, x);
            }
            return x;
        }
        // get the node pointer of the minimum value
        node* get_minimum(node* n) {
            node* p = n;
            while(p->left_ != nullptr) {
                p = p->left_;
            }
            return p;
        }
        // get the node pointer of the minimum value
        node* get_maximum(node* n) {
            node* p = n;
            while(p->right_ != nullptr) {
                p = p->right_;
            }
            return p;
        }
        // get the successor of a node in the tree
        node* get_successor(node* n) {
            if(n->right_ != nullptr) {
                // find the minimum value in the right sub-tree
                return get_minimum(n->right_);
            }
            auto y = n->parent_;
            while(y != nullptr && y->left_!=n) {
                n = y;
                y = n->parent_;
            }
            return y;
        }
        // get the predecessor of a node in the tree
        node* get_predcessor(node* n) {
            if(n->left_ != nullptr) {
                // find the maximum value in the left sub-tree
                return get_maximum(n->left_);
            }
            auto y = n->parent_;
            while (y != nullptr && y->right_ != n) {
                n = y;
                y = n->parent_;
            }
            return y;
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
            return Iterator(search(val, root_));
        }
        // insert value
        void insert(const T& val) {
            root_ = insert(val, root_, nullptr);
        }
        // erase value
        void erase(const T& val) {
            auto p = search(val, root_);
            if(p == nullptr)    return; // the value is not found. return
            node* y = nullptr, *x = nullptr;
            if(p->left_ == nullptr || p->right_ == nullptr) {
                // if p has no more than one child, we erase the node p
                y = p;
            } else {
                // if p has two children, we erase the successor of node p, which is y
                y = get_successor(p);
            }
            // find the non-null child node of y
            if(y->left_ != nullptr)    x = y->left_;
            else x = y->right_;
            // change the parent link of node x
            if(x != nullptr)    x->parent_ = y->parent_;
            if(y->parent_ == nullptr) {
                // y is the root node of BST
                root_ = x;
            } else if(y == y->parent_->left_){
                // y is the left child node of its parent node
                y->parent_->left_ = x;
            } else {
                // y is the right child node of its parent node
                y->parent_->right_ = x;
            }
            if(y != p) {
                // copy the content of y into p
                p->val_ = std::move(y->val_);
            }
            delete y;
            --sz_;
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

        Iterator get_successor(const Iterator& it) {
            auto p = it.ptr_;
            return Iterator(get_successor(p));
        }

        Iterator get_predcessor(const Iterator& it) {
            auto p = it.ptr_;
            return Iterator(get_predcessor(p));
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