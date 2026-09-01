#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>

namespace utec {

template <typename T>
struct list {
    struct DoubleNode {
        T data;
        DoubleNode* prev;
        DoubleNode* next;
        DoubleNode(const T& val) : data(val), prev(nullptr), next(nullptr) {}
    };
    DoubleNode* head;
    DoubleNode* tail;
    size_t sz;

    DoubleNode* get_node(size_t index) const {
        if (index >= sz) return nullptr;
        DoubleNode* current;
        if (index < sz / 2) {
            current = head;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }
        } else {
            current = tail;
            for (size_t i = sz - 1; i > index; --i) {
                current = current->prev;
            }
        }
        return current;
    }

    list() : head(nullptr), tail(nullptr), sz(0) {}

    ~list() {
        clear();
    }

    list(const list& other) : head(nullptr), tail(nullptr), sz(0) {
        DoubleNode* current = other.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }

    list& operator=(const list& other) {
        if (this != &other) {
            clear();
            DoubleNode* current = other.head;
            while (current != nullptr) {
                push_back(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    list(list&& other) noexcept : head(other.head), tail(other.tail), sz(other.sz) {
        other.head = nullptr;
        other.tail = nullptr;
        other.sz = 0;
    }

    list& operator=(list&& other) noexcept {
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
        DoubleNode* new_node = new DoubleNode(value);
        if (empty()) {
            head = tail = new_node;
        } else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        ++sz;
    }

    void push_back(const T& value) {
        DoubleNode* new_node = new DoubleNode(value);
        if (empty()) {
            head = tail = new_node;
        } else {
            new_node->prev = tail;
            tail->next = new_node;
            tail = new_node;
        }
        ++sz;
    }

    void pop_front() {
        if (empty()) return;
        DoubleNode* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        --sz;
    }

    void pop_back() {
        if (empty()) return;
        DoubleNode* temp = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
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
        DoubleNode* current = get_node(index - 1);
        insert_after(current, value);
    }

    DoubleNode* insert_after(DoubleNode* node, const T& value) {
        if (node == nullptr || node == tail) {
            push_back(value);
            return tail;
        }
        DoubleNode* new_node = new DoubleNode(value);
        new_node->next = node->next;
        new_node->prev = node;
        node->next->prev = new_node;
        node->next = new_node;
        ++sz;
        return new_node;
    }

    DoubleNode* insert_before(DoubleNode* node, const T& value) {
        if (node == nullptr || node == head) {
            push_front(value);
            return head;
        }
        DoubleNode* new_node = new DoubleNode(value);
        new_node->prev = node->prev;
        new_node->next = node;
        node->prev->next = new_node;
        node->prev = new_node;
        ++sz;
        return new_node;
    }

    void erase(size_t index) {
        if (index >= sz) return;
        if (index == 0) {
            pop_front();
            return;
        }
        if (index == sz - 1) {
            pop_back();
            return;
        }
        DoubleNode* target = get_node(index);
        erase(target);
    }

    void erase(DoubleNode* node) {
        if (node == nullptr || empty()) return;
        if (node == head) {
            pop_front();
            return;
        }
        if (node == tail) {
            pop_back();
            return;
        }
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
        --sz;
    }

    void clear() {
        DoubleNode* current = head;
        while (current != nullptr) {
            DoubleNode* temp = current;
            current = current->next;
            delete temp;
        }
        head = tail = nullptr;
        sz = 0;
    }

    T& front() { return head->data; }
    const T& front() const { return head->data; }

    T& back() { return tail->data; }
    const T& back() const { return tail->data; }

    DoubleNode* find(const T& value) {
        DoubleNode* current = head;
        while (current != nullptr) {
            if (current->data == value) return current;
            current = current->next;
        }
        return nullptr;
    }

    void reverse() {
        if (sz <= 1) return;
        DoubleNode* current = head;
        while (current != nullptr) {
            DoubleNode* temp = current->next;
            current->next = current->prev;
            current->prev = temp;
            current = temp;
        }
        DoubleNode* temp = head;
        head = tail;
        tail = temp;
    }

    size_t size() const { return sz; }
    bool empty() const { return head == nullptr; }
};

}

#endif
