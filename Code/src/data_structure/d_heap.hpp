#ifndef CLRS_D_HEAP_HPP
#define CLRS_D_HEAP_HPP

#include <cstddef>
#include <functional>
#include <vector>
namespace alg {
    template<typename T, size_t D, typename Comp = std::less<T>>
    class d_heap {
        /*
         * API: (same with priority_deque)
         * 1. INSERT(S, x) -- Insert element x into set S.
         * 2. MAXIMUJM(S) -- Return the element which has the maximum key
         * 3. EXTRACT-MAX(S) -- delete the element which has the maximum key and return its value
         * (I didn't use <key, value> here for simplification, just used the value of the element as key).
         */
    public:
        typedef typename std::vector<T>::size_type size_type;

        d_heap() : size_(0), data_(Container()), comp_(Comp()) { }

        inline size_type size() const {
            return size_;
        }

        inline bool empty() const {
            return size_ == 0;
        }

        void insert(const T &x) {
            data_.push_back(x);
            swim(size_);
            size_++;
        }

        inline T &maximum() {
            return data_[0];
        }

        T extract_max() {
            T val = data_[0];
            data_[0] = data_[size_ - 1];
            sink(0);
            --size_;
            return val;
        }

    private:
        typedef std::vector<T> Container;
        size_type size_;
        Container data_;
        Comp comp_;

        // get the index of left child
        inline int lchild(int x) {
            return x * D + 1;
        }

        // get the index of right child
        inline int rchild(int x) {
            return (x + 1) * D;
        }

        // get the index of parent
        inline int parent(int x) {
            return x == 0 ? -1 : (x - 1) / D;
        }

        void sink(int i) {
            int lb = lchild(i);
            int rb = std::min<int>(rchild(i), size_ - 1);
            int smallest = i;
            for (int idx = lb; idx <= rb; ++idx) {
                if (comp_(data_[idx], data_[smallest])) smallest = idx;
            }
            if (smallest != i) {
                std::swap(data_[i], data_[smallest]);
                sink(smallest);
            }
        }

        void swim(int i) {
            int p = 0;  // parent index of node i
            while ((p = parent(i)) >= 0 && comp_(data_[i], data_[p])) {
                std::swap(data_[i], data_[p]);
                i = p;
            }
        }
    };
} // end of namespace alg
#endif // end of file d_heap.hpp