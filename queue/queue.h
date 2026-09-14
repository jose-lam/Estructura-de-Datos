#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cstddef>

namespace utec {
    template <typename T>
    struct queue {
        struct Node {
            T data;
            Node* next;
            Node(const T& val) : data(val), next(nullptr) {}
        };
        Node* first = nullptr;
        Node* last = nullptr;
        size_t sz = 0;

        queue() = default;

        ~queue() {
            clear();
        }

        void enqueue(const T& value){
            Node* new_node = new Node(value);
            if (empty()) first = last = new_node;
            else {
                last->next = new_node;
                last = new_node;
            }
            ++sz;
        }

        void dequeue(){
            if (empty()) return;
            if (first == last) last = nullptr;
            Node* temp = first;
            first = first -> next;
            delete temp;
            --sz;
        }

        void clear() {
            while(!empty()){
                dequeue();
            }
            sz = 0;
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
