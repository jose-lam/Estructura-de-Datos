#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

namespace utec {

template <typename T>
struct func_hash {
    unsigned long long operator()(const T& key) const {
        return static_cast<unsigned long long>(key) * 67ULL;
    }
};

template <>
struct func_hash<std::string> {
    unsigned long long operator()(const std::string& key) const {
        unsigned int h = 5333;
        for (char c : key) {
            h = h * 67 + c;
        }
        return h;
    }
};

template <typename Tc, typename Tv>
struct hash_table {
private:
    std::vector<std::vector<std::pair<Tc, Tv>>> bucket;
    long long m;
    size_t sz = 0;

public:
    explicit hash_table(long long n) : m(n > 0 ? n : 1) {
        bucket.resize(m);
    }

    Tv& insert(const Tc& key, Tv value = Tv()) {
        long long idx = hash(key);
        for (auto& e : bucket[idx]) {
            if (e.first == key) {
                e.second = value;
                return e.second;
            }
        }
        bucket[idx].push_back(std::make_pair(key, value));
        ++sz;
        return bucket[idx].back().second;
    }

    Tv& operator[](const Tc& key) {
        long long idx = hash(key);
        for (auto& e : bucket[idx]) {
            if (e.first == key) {
                return e.second;
            }
        }
        return insert(key);
    }

    long long hash(const Tc& key) const {
        func_hash<Tc> fh;
        return static_cast<long long>(fh(key) % static_cast<unsigned long long>(m));
    }

    bool erase(const Tc& key) {
        long long idx = hash(key);
        auto& b = bucket[idx];
        for (size_t i = 0; i < b.size(); ++i) {
            if (b[i].first == key) {
                std::swap(b[i], b.back());
                b.pop_back();
                --sz;
                return true;
            }
        }
        return false;
    }

    bool has_key(const Tc& key) const {
        long long idx = hash(key);
        for (const auto& e : bucket[idx]) {
            if (e.first == key) {
                return true;
            }
        }
        return false;
    }

    size_t size() const { return sz; }
};

}

#endif
