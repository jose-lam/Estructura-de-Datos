#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP

#include <cstddef>

namespace utec {
    template <typename T>
    struct forward_list {
        struct SingleNode {
            T data;
            SingleNode* next;
            SingleNode(const T& val) : data(val), next(nullptr) {}
        };
        SingleNode* head;
        SingleNode* tail;
        size_t sz;

        forward_list() : head(nullptr), tail(nullptr), sz(0) {}

        ~forward_list() {
            clear();
        }

        forward_list(const forward_list& other) : head(nullptr), tail(nullptr), sz(0) {
            SingleNode* current = other.head;
            while (current != nullptr) {
                push_back(current->data);
                current = current->next;
            }
        }

        forward_list& operator=(const forward_list& other) {
            if (this != &other) {
                clear();
                SingleNode* current = other.head;
                while (current != nullptr) {
                    push_back(current->data);
                    current = current->next;
                }
            }
            return *this;
        }

        forward_list(forward_list&& other) noexcept : head(other.head), tail(other.tail), sz(other.sz) {
            other.head = nullptr;
            other.tail = nullptr;
            other.sz = 0;
        }

        forward_list& operator=(forward_list&& other) noexcept {
            if (this != &other) {
                clear();
                head = other.head;
                tail = other.tail;
                sz = other.sz;

                other.head = nullptr;
                other.tail = nullptr;
                other.sz = 0;
            }
            return *this;
        }

        void push_front(const T& value) {
            SingleNode* new_node = new SingleNode(value);
            new_node->next = head;
            head = new_node;
            if (tail == nullptr) {
                tail = head;
            }
            ++sz;
        }

        void push_back(const T& value) {
            SingleNode* new_node = new SingleNode(value);
            if (empty()) {
                head = tail = new_node;
            } else {
                tail->next = new_node;
                tail = new_node;
            }
            ++sz;
        }

        void pop_front() {
            if (empty()) return;
            SingleNode* temp = head;
            head = head->next;
            delete temp;
            --sz;
            if (head == nullptr) {
                tail = nullptr;
            }
        }

        void pop_back() {
            if (empty()) return;
            if (head == tail) {
                delete head;
                head = tail = nullptr;
            } else {
                SingleNode* current = head;
                while (current->next != tail) {
                    current = current->next;
                }
                delete tail;
                tail = current;
                tail->next = nullptr;
            }
            --sz;
        }

        void insert(size_t index, const T& value) {
            if (index > sz) return;
            if (index == 0) {
                push_front(value);
                return;
            }
            if (index == sz) {
                push_back(value);
                return;
            }
            SingleNode* current = head;
            for (size_t i = 0; i < index - 1; ++i) {
                current = current->next;
            }
            SingleNode* new_node = new SingleNode(value);
            new_node->next = current->next;
            current->next = new_node;
            ++sz;
        }

        void insert(SingleNode* node, const T& value) {
            if (node == nullptr || node == tail) {
                push_back(value);
                return;
            }
            SingleNode* new_node = new SingleNode(value);
            new_node->next = node->next;
            node->next = new_node;
            ++sz;
        }

        void erase(size_t index) {
            if (index >= sz) return;
            if (index == 0) {
                pop_front();
                return;
            }
            SingleNode* current = head;
            for (size_t i = 0; i < index - 1; ++i) {
                current = current->next;
            }
            SingleNode* del_node = current->next;
            current->next = del_node->next;
            if (del_node == tail) {
                tail = current;
            }
            delete del_node;
            --sz;
        }

        void erase(SingleNode* node) {
            if (node == nullptr || empty()) return;
            if (node == head) {
                pop_front();
                return;
            }
            SingleNode* current = head;
            while (current != nullptr && current->next != node) {
                current = current->next;
            }
            if (current != nullptr) {
                current->next = node->next;
                if (node == tail) {
                    tail = current;
                }
                delete node;
                --sz;
            }
        }

        void clear() {
            while (head != nullptr) {
                SingleNode* temp = head;
                head = head->next;
                delete temp;
            }
            tail = nullptr;
            sz = 0;
        }

        T& front() { return head->data; }
        const T& front() const { return head->data; }

        T& back() { return tail->data; }
        const T& back() const { return tail->data; }

        SingleNode* find(const T& value) {
            SingleNode* current = head;
            while (current != nullptr) {
                if (current->data == value) return current;
                current = current->next;
            }
            return nullptr;
        }

        void reverse() {
            if (sz <= 1) return;
            SingleNode* prev = nullptr;
            SingleNode* current = head;
            SingleNode* next_node = nullptr;
            tail = head;
            while (current != nullptr) {
                next_node = current->next;
                current->next = prev;
                prev = current;
                current = next_node;
            }
            head = prev;
        }

        size_t size() const { return sz; }
        bool empty() const { return head == nullptr; }
    };
}

#endif
