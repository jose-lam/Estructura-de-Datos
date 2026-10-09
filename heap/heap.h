#ifndef HEAP_HPP
#define HEAP_HPP

#include <cstddef>
#include <vector>
#include <utility>

namespace utec {
    struct Comparador {
        template <typename T>
        bool operator()(const T& a, const T& b) const {
            return a < b;
        }
    };

    template<typename T, typename compare = Comparador>
        struct heap {

        explicit heap(compare c = compare()) : comp(c) {}

        heap(std::vector<T> vec, compare c = compare()) : data(std::move(vec)), comp(c) {
            build_heap();
        }

        const T& top() const {
            return data[0];
        }

        bool empty() const {
            return data.empty();
        }

        std::size_t size() const {
            return data.size();
        }

        void pop() {
            if (empty()) return;
            if (size() != 1) data[0] = std::move(data.back());
            data.pop_back();
            if (!empty()) sift_down(0);
        }

        void insert(const T& val) {
            data.emplace_back(val);
            sift_up(data.size()-1);
        }

        private:

        std::vector<T> data;
        compare comp;

        std::size_t left(std::size_t i) const {
            return 2*i+1;
        }

        std::size_t right(std::size_t i) const {
            return 2*i+2;
        }

        std::size_t parent(std::size_t i) const {
            return (i-1)/2;
        }

        void sift_down (std::size_t i) {
            while (true) {
                std::size_t m = i;
                if (left(i) < data.size() && comp(data[left(i)], data[m])) m = left(i);
                if (right(i) < data.size() && comp(data[right(i)], data[m])) m = right(i);
                if (m == i) return;
                std::swap(data[i], data[m]);
                i = m;
            }
        }

        void sift_up (std::size_t i) {
            while (i > 0 && comp(data[i], data[parent(i)])) {
                std::swap(data[i], data[parent(i)]);
                i = parent(i);
            }
        }

        void build_heap() {
            if (size() <= 1) return;
            for (std::size_t i = parent(data.size() - 1); ; --i) {
                sift_down(i);
                if (i == 0) return;
            }
        }

    };
}

#endif
