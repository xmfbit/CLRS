#ifndef CLRS_RB_TREE_HPP
#define CLRS_RB_TREE_HPP

#include <iostream>
#include <utility>
#include <functional>
#include <iterator>

namespace alg {
    template<typename T>
    struct Comperator {
        int operator()(const T& lhs, const T& rhs) const {
            if (std::less<T>()(lhs, rhs)) return -1;
            if (std::less<T>()(rhs, lhs)) return 1;
            return 0;
        }
    };

    template<typename T, typename Comp = Comperator<T>>
    class RBTree {
    private:
        // the color
        enum COLOR {
            RED, BLACK
        };

        // struct node
        struct node {
            T val_;
            node *left_;
            node *right_;
            node *parent_;
            COLOR color_;

            node(const T& val) : val_(val), left_(nullptr), right_(nullptr), parent_(nullptr), color_(RED) { }

            node(const T& val, node *l_child, node *r_child, node *parent, COLOR c) :
                    val_(val), left_(l_child), right_(r_child), parent_(parent), color_(c) { }
        };

        // in-order traversal
        template<typename Op>
        void inOrderTraversal(const node *n, const Op& op) {
            if (n == nil_) return;
            if (n->left_ != nil_) inOrderTraversal(n->left_, op);
            op(n);
            if (n->right_ != nil_) inOrderTraversal(n->right_, op);
        }

        template<typename Op>
        void inOrderTraversal(const Op& op) {
            inOrderTraversal(root_, op);
        }

        // post-order traversal
        template<typename Op>
        void postOrderTraversal(const node *n, const Op& op) {
            if (n == nil_) return;
            if (n->left_ != nil_) postOrderTraversal(n->left_, op);
            if (n->right_ != nil_) postOrderTraversal(n->right_, op);
            op(n);
        }

        template<typename Op>
        void postOrderTraversal(const Op& op) {
            postOrderTraversal(root_, op);
        }

        // search for the value from a given node
        node *search(const T& val, node *n) const {
            if (n == nil_) return nil_;
            if (comp_(n->val_, val) == 0) return n;
            if (comp_(n->val_, val) < 0) return search(val, n->right_);
            return search(val, n->left_);
        }

        // find the minimum value from a given node
        node *get_minimum(node *root) {
            node *p = root;
            while (p->left_ != nil_) {
                p = p->left_;
            }
            return p;
        }

        // get the node pointer of the minimum value
        node *get_maximum(node *n) {
            node *p = n;
            while (p->right_ != nil_) {
                p = p->right_;
            }
            return p;
        }

        // get the successor of a node in the tree
        node *get_successor(const node *n) {
            if (n->right_ != nil_) {
                // find the minimum value in the right sub-tree
                return get_minimum(n->right_);
            }
            auto y = n->parent_;
            while (y != nil_ && y->left_ != n) {
                n = y;
                y = n->parent_;
            }
            return y;
        }

        // get the predecessor of a node in the tree
        const node *get_predcessor(const node *n) {
            if (n->left_ != nil_) {
                // find the maximum value in the left sub-tree
                return get_maximum(n->left_);
            }
            auto y = n->parent_;
            while (y != nil_ && y->right_ != n) {
                n = y;
                y = n->parent_;
            }
            return y;
        }

        // left rotate
        void leftRotate(node *x) {
            node *y = x->right_;
            node *p_x = x->parent_;
            y->parent_ = p_x;
            if (p_x == nil_) root_ = y;
            else if (p_x->left_ == x) p_x->left_ = y;
            else p_x->right_ = y;

            node *left_y = y->left_;
            left_y->parent_ = x;
            x->right_ = left_y;
            x->parent_ = y;
            y->left_ = x;
        }

        // right rotate
        void rightRotate(node *y) {
            node *x = y->left_;
            node *p_y = y->parent_;
            x->parent_ = p_y;
            if (p_y == nil_) root_ = x;
            else if (p_y->right_ == y) p_y->right_ = x;
            else p_y->left_ = x;

            node *right_x = x->right_;
            right_x->parent_ = y;
            y->left_ = right_x;
            y->parent_ = x;
            x->right_ = y;
        }

        // fix up after insertion to keep the property of the RBTree
        node *insertFixup(node *z) {
            node *tmp = z;
            node *parent = nil_;
            while ((parent = z->parent_)->color_ == RED) {
                node *gradpa = parent->parent_;
                if (parent == gradpa->left_) {
                    node *uncle = gradpa->right_;
                    if (uncle->color_ == RED) {  // Condition 1, the color of the uncle node is RED
                        // then we change the color of the parent and uncle node to BLACK
                        // and the color of the grandparent node to RED
                        // OK, now we make the local rigion satisfy the property but we should continue
                        // to fix the local rigion of z's grandparent
                        uncle->color_ = BLACK;
                        parent->color_ = BLACK;
                        gradpa->color_ = RED;
                        z = gradpa;
                    } else {   // Condition 2 and 3
                        if (z == parent->right_) {  // Condition 2, z is the right child of its parent
                            // then  we left-rotate the parent node
                            z = parent;
                            leftRotate(z);
                        }
                        // Condition 3, z is the left child of its parent
                        // then we change the color of z's parent and grandparent
                        // notice that z's uncle's color is BLACK already
                        parent = z->parent_;
                        gradpa = parent->parent_;
                        parent->color_ = BLACK;
                        gradpa->color_ = RED;
                        // then we right-rotate the grandparent node
                        rightRotate(gradpa);
                    }
                } else {
                    node *uncle = gradpa->left_;
                    if (uncle->color_ == RED) {
                        uncle->color_ = BLACK;
                        parent->color_ = BLACK;
                        gradpa->color_ = RED;
                        z = gradpa;
                    } else {
                        if (z == parent->left_) {
                            z = parent;
                            rightRotate(z);
                        }
                        parent = z->parent_;
                        gradpa = parent->parent_;
                        parent->color_ = BLACK;
                        gradpa->color_ = RED;
                        leftRotate(gradpa);
                    }
                }
            }
            root_->color_ = BLACK;
            return tmp;
        }

        node *insert_(const T& val) {
            // 1. insert the value as BST
            node *y = nil_;
            node *x = root_;
            while (x != nil_) {
                y = x;
                if (comp_(x->val_, val) < 0) x = x->right_;
                else if (comp_(x->val_, val) > 0) x = x->left_;
                else return x;
            }
            node *z = new node(val, nil_, nil_, y, RED);
            if (y == nil_) root_ = z;
            else if (comp_(y->val_, val) < 0) y->right_ = z;
            else y->left_ = z;
            // 2. fix up to keep the property of RBTree
            ++sz_;
            return insertFixup(z);
        }

        void deleteFixup(node *x) {
            while (x != root_ && x->color_ == BLACK) {
                if (x == x->parent_->left_) {
                    node *bro = x->parent_->right_;
                    if (bro->color_ == RED) {
                        bro->color_ = BLACK;
                        x->parent_->color_ = RED;
                        leftRotate(x->parent_);
                        bro = x->parent_->right_;
                    }
                    if (bro->left_->color_ == BLACK && bro->right_->color_ == BLACK) { // Condition 2
                        bro->color_ = RED;
                        x = x->parent_;
                    } else {  // Condition 3 and 4
                        if (bro->right_->color_ == BLACK) { // Condition 3
                            bro->left_->color_ = BLACK;
                            bro->color_ = RED;
                            rightRotate(bro);
                            bro = x->parent_->right_;
                        }
                        // Condition 4
                        bro->color_ = x->parent_->color_;
                        x->parent_->color_ = BLACK;
                        bro->right_->color_ = BLACK;
                        leftRotate(x->parent_);
                        x = root_;
                    }
                } else {
                    node *bro = x->parent_->left_;
                    if (bro->color_ == RED) {
                        bro->color_ = BLACK;
                        x->parent_->color_ = RED;
                        rightRotate(x->parent_);
                        bro = x->parent_->left_;
                    }
                    if (bro->right_->color_ == BLACK && bro->left_->color_ == BLACK) {
                        bro->color_ = RED;
                        x = x->parent_;
                    } else {
                        if (bro->left_->color_ == BLACK) {
                            bro->right_->color_ = BLACK;
                            bro->color_ = RED;
                            leftRotate(bro);
                            bro = x->parent_->left_;
                        }
                        bro->color_ = x->parent_->color_;
                        x->parent_->color_ = BLACK;
                        bro->left_->color_ = BLACK;
                        rightRotate(x->parent_);
                        x = root_;
                    }
                }
            }
            x->color_ = BLACK;
        }

        void erase_(const T& val) {
            node *z = search(val, root_);
            if (z == nil_) return;
            node *y = nil_;
            if (z->left_ == nil_ || z->right_ == nil_) y = z;
            else y = get_successor(z);
            node *x = nil_;
            if (y->left_ != nil_) x = y->left_;
            else x = y->right_;
            x->parent_ = y->parent_;
            if (y->parent_ == nil_) root_ = x;
            else if (y->parent_->left_ == y) y->parent_->left_ = x;
            else y->parent_->right_ = x;
            if (y != z) {
                z->val_ = y->val_;
            }
            if (y->color_ == BLACK) deleteFixup(x);
            delete y;
            --sz_;
        }

        // data member
        typedef size_t size_type;
        size_type sz_;                //<! the size of the tree
        node *root_;                  //<! the root node
        node *nil_;                   //<! the guard node
        Comp comp_ = Comp();          //<! comperator
    public:
        // Construction
        RBTree() : sz_(0), root_(nullptr), nil_(nullptr) { }

        // Iterator
        // Because it is forbidden to change the value by iterator, so it is const.
        // Otherwise, the property of the RBTree would be destroyed.
        class const_Iterator {
        public:
            //const_Iterator():ptr_(nil_) {}
            explicit const_Iterator(const node *p) : ptr_(p) { }

            bool operator==(const const_Iterator& rhs) const {
                if (this == &rhs) return true;
                return ptr_ == rhs.ptr_;
            }

            bool operator!=(const const_Iterator& rhs) const {
                if (this == &rhs) return false;
                return ptr_ != rhs.ptr_;
            }

            const T& operator*() const {
                return ptr_->val_;
            }

        private:
            const node *ptr_;

            friend class RBTree;
        };

        // the size of the tree
        size_type size() const {
            return sz_;
        }

        // is the tree empty
        bool empty() const {
            return sz_ == 0;
        }

        // get the iterator of the minimum value in the tree
        const_Iterator get_minimum() {
            if (empty()) return const_Iterator(nil_);
            return const_Iterator(get_minimum(root_));
        }

        // get the iterator of the minimum value in the tree
        const_Iterator get_maximum() {
            if (empty()) return end();
            return const_Iterator(get_maximum(root_));
        }

        // get the successor of the current iterator
        const_Iterator get_successor(const const_Iterator& it) {
            if (sz_ <= 1) return end();
            auto p = it.ptr_;
            return const_Iterator(get_successor(p));
        }

        const_Iterator get_predcessor(const const_Iterator& it) {
            if (sz_ <= 1) return end();
            auto p = it.ptr_;
            return const_Iterator(get_predcessor(p));
        }

        // get the begin iterator of the tree, which is the first element of in-order traversal
        const_Iterator begin() const {
            return get_minimum();
        }

        // get the end iterator if the tree, which can be used to verify the search result
        const_Iterator end() const {
            return const_Iterator(nil_);
        }

        // search for the value in the tree
        const_Iterator search(const T& val) const {
            if (empty()) return end();
            return const_Iterator(search(val, root_));
        }

        // insert value
        const_Iterator insert(const T& val) {
            if (empty()) {
                ++sz_;
                if (nil_ == nullptr) {
                    nil_ = new node(val, nullptr, nullptr, nullptr, BLACK);
                }
                root_ = new node(val, nil_, nil_, nil_, BLACK);
                return const_Iterator(root_);
            }
            return const_Iterator(insert_(val));
        }

        // erase value
        void erase(const T& val) {
            if (empty()) return;
            erase_(val);
        }

        // output to a container with iterator
        template<typename ForwardIterator>
        void outputByInorderTraversal(const ForwardIterator& first) {
            if (!empty()) {
                auto f = [](const node *n, ForwardIterator& it) { *it++ = n->val_; };
                auto it = first;
                inOrderTraversal(std::bind(f, std::placeholders::_1, std::ref(it)));
            }
        }

        // de-construction
        ~RBTree() {
            if (!empty()) {
                auto f = [](const node *p) { delete p; };
                postOrderTraversal(root_, f);
            }
            if (nil_ != nullptr) delete nil_;
        }
    }; // end of class rb_tree
} // end of namespace alg
#endif // end of binary_search_tree.hpp