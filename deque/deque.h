#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cstddef>

namespace utec {
    template <typename T>
    struct deque {
        struct Node {
            T data;
            Node* next;
            Node(const T& val) : data(val), next(nullptr) {}
        };
        Node* first = nullptr;
        Node* last = nullptr;
        size_t sz = 0;

        deque() = default;

        ~deque() {
            clear();
        }

        void enqueue(const T& value) {
            Node* new_node = new Node(value);
            if (empty()) first = last = new_node;
            else {
                last->next = new_node;
                last = new_node;
            }
            ++sz;
        }

        void dequeue() {
            if (empty()) return;
            Node* temp = first;
            first = first->next;
            if (first == nullptr) last = nullptr;
            delete temp;
            --sz;
        }

        void push(const T& value) {
            Node* new_node = new Node(value);
            new_node->next = first;
            if (empty()) last = new_node;
            first = new_node;
            ++sz;
        }

        void pop() {
            dequeue();
        }

        void clear() {
            while (!empty()) {
                dequeue();
            }
        }

        T& front() { return first->data; }
        const T& front() const { return first->data; }

        T& back() { return last->data; }
        const T& back() const { return last->data; }

        size_t size() const { return sz; }
        bool empty() const { return first == nullptr; }
    };
}


#endif
