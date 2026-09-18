#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <utility>

namespace utec {

template <typename T>
class vector {
private:
    T* data;
    size_t sz;
    size_t cap;

public:
    vector() : data(nullptr), sz(0), cap(0) {}

    explicit vector(size_t initial_cap) : sz(initial_cap), cap(initial_cap) {
        data = new T[initial_cap]();
    }

    ~vector() {
        delete[] data;
    }

    vector(const vector& other) : sz(other.sz), cap(other.cap) {
        data = new T[cap];
        for (size_t i = 0; i < sz; ++i) {
            data[i] = other.data[i];
        }
    }

    vector& operator=(const vector& other) {
        if (this != &other) {
            T* new_data = new T[other.cap];
            for (size_t i = 0; i < other.sz; ++i) {
                new_data[i] = other.data[i];
            }
            delete[] data;
            data = new_data;
            sz = other.sz;
            cap = other.cap;
        }
        return *this;
    }

    vector(vector&& other) noexcept : data(other.data), sz(other.sz), cap(other.cap) {
        other.data = nullptr;
        other.sz = 0;
        other.cap = 0;
    }

    vector& operator=(vector&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            sz = other.sz;
            cap = other.cap;

            other.data = nullptr;
            other.sz = 0;
            other.cap = 0;
        }
        return *this;
    }

    void reserve(size_t new_cap) {
        if (new_cap <= cap) return;

        T* new_data = new T[new_cap]();
        for (size_t i = 0; i < sz; ++i) {
            new_data[i] = std::move(data[i]);
        }
        delete[] data;
        data = new_data;
        cap = new_cap;
    }

    void resize(size_t new_size) {
        if (new_size > cap) {
            reserve(new_size);
        }
        sz = new_size;
    }

    void push_back(const T& value) {
        if (sz == cap) {
            reserve(cap == 0 ? 1 : cap * 2);
        }
        data[sz] = value;
        ++sz;
    }

    void pop_back() {
        if (empty()) return;
        --sz;
    }

    void insert(size_t index, const T& value) {
        if (index > sz) return;
        if (sz == cap) {
            reserve(cap == 0 ? 1 : cap * 2);
        }
        for (size_t i = sz; i > index; --i) {
            data[i] = std::move(data[i - 1]);
        }
        data[index] = value;
        ++sz;
    }

    void erase(size_t index) {
        if (index >= sz) return;
        for (size_t i = index; i < sz - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        pop_back();
    }

    void clear() {
        sz = 0;
    }

    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }

    T& front() { return data[0]; }
    const T& front() const { return data[0]; }

    T& back() { return data[sz - 1]; }
    const T& back() const { return data[sz - 1]; }

    T* begin() { return data; }
    const T* begin() const { return data; }
    T* end() { return data + sz; }
    const T* end() const { return data + sz; }

    size_t size() const { return sz; }
    size_t capacity() const { return cap; }
    bool empty() const { return sz == 0; }
};

}

#endif
