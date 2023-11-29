#include "HashTable.hpp"

namespace bit
{
    template <class K, class HF = HashFuc<K>>
    class unordered_set 
    {
    public:
        struct KeyOfSet
        {
            bool operator()(const K& key)
            {
                return (size_t)key;
            }
        };

        typedef typename HashBucket<K, K, KeyOfSet, HF>::const_iterator iterator;
        typedef typename HashBucket<K, K, KeyOfSet, HF>::const_iterator const_iterator;

        iterator begin() const
        {
            return hash.begin();
        }

        iterator end() const 
        {
            return hash.end();
        }

        std::pair<iterator, bool> insert(const K& key)
        {
            auto it = hash.insert(key);
            return std::pair<iterator, bool>(it.first, it.second);
        }

        iterator find(const K& key)
        {
            return hash.find(key);
        }
    private:
        HashBucket<K, K, KeyOfSet, HF> hash;
    };
};
