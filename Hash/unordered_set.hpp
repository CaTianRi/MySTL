#include "HashTable.hpp"

namespace bit {
template <class K, class HF = HashFuc<K>> class unordered_set {
  public:
    struct KeyOfSet {
        const K &operator()(const K &key) { return key; }
    };

    typedef typename HashBucket<K, K, KeyOfSet, HF>::const_iterator iterator;
    typedef typename HashBucket<K, K, KeyOfSet, HF>::const_iterator const_iterator;

    template <class InputIterator>
    unordered_set(InputIterator first, InputIterator last) {
        for (first; first != last; ++first) {
            insert(*first);
        }
    }

    iterator begin() const { return hash.begin(); }

    iterator end() const { return hash.end(); }

    std::pair<iterator, bool> insert(const K &key) {
        auto it = hash.insert(key);
        return std::pair<iterator, bool>(it.first, it.second);
    }

    bool erase(const K &key) { return hash.erase(key); }

    iterator find(const K &key) { return hash.find(key); }

  private:
    HashBucket<K, K, KeyOfSet, HF> hash;
};
}; // namespace bit
