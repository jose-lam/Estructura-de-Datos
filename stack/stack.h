#ifndef STACK_HPP
#define STACK_HPP

#include <cstddef>

namespace utec {
    template <typename T>
    struct stack {
        struct Node {
            T data;
            Node* next;
            Node(const T& val) : data(val), next(nullptr) {}
        };
        Node* tope = nullptr;
        size_t sz = 0;

        stack() = default;

        ~stack() {
            clear();
        }

        void push(const T& value){
            Node* new_node = new Node(value);
            new_node->next = tope;
            tope = new_node;
            ++sz;
        }

        void pop(){
            if (empty()) return;
            Node* temp = tope;
            tope = tope->next;
            delete temp;
            --sz;
        }

        void clear() {
            while(!empty()){
                pop();
            }
            sz = 0;
        }

        T& top() { return tope->data; }
        const T& top() const { return tope->data; }

        size_t size() const { return sz; }
        bool empty() const { return tope == nullptr; }
    };
}


#endif
