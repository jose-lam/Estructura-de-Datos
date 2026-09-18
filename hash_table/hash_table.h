#ifndef HASH_TABLE_CPP
#define HASH_TABLE_CPP

#include <string>
#include <vector>
#include <utility>

namespace utec {

template <typename T>
struct func_hash {
    long long operator()(const T& key) const {
        long long x = static_cast<long long>(key);
        return (x < 0 ? -x : x) * 67LL;
    }
};

template <>
struct func_hash<std::string> {
    long long operator()(const std::string& key) const {
        unsigned int h = 5333;
        for (char c : key) {
            h = h * 67 + c;
        }
        return static_cast<long long>(h);
    }
};

template <typename Tc, typename Tv>
struct hash_table {
    std::vector<std::vector<std::pair<Tc,Tv>>> bucket;
    long long m;
    size_t sz = 0;

    hash_table(long long n) : m(n > 0 ? n : 1) {
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
        return fh(key) % m;
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
};
}

#endif
