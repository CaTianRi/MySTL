#include "HashTable.hpp"
#include <utility>

namespace bit 
{
    template <class K, class V, class Hash= HashFuc<K>>
    class unordered_map
    {
        struct KeyOfMap
        {
            const K& operator()(const std::pair<const K, V>& val)const 
            {
                return val.first;
            }
        };

    public:
        typedef typename HashBucket<K, std::pair<const K, V>, KeyOfMap, Hash>::iterator iterator;
        typedef typename HashBucket<K, std::pair<const K, V>, KeyOfMap, Hash>::const_iterator const_iterator;

        unordered_map(){}

        template <class InputIterator>
        unordered_map(InputIterator first, InputIterator last)
        {
            for(first; first != last; ++first)
            {
                insert(*first);
            }
        }

        const_iterator begin()const 
        {
            return _hashtable.begin();
        }

        const_iterator end()const 
        {
            return _hashtable.end();
        }

        iterator begin()
        {
            return _hashtable.begin();
        }

        iterator end()
        {
            return _hashtable.end();
        }

        V& operator[](const K& key)
        {
            auto it = _hashtable.insert({key, V()});
            return (*(it.first)).second;
        }

        std::pair<iterator, bool> insert(const std::pair<const K, V>& data)
        {
            return _hashtable.insert(data);
        }

        bool erase(const K& key)
        {
            return _hashtable.erase(key);
        }

        iterator find(const K& key)
        {
            return _hashtable.find(key);
        }

        iterator find(const K& key)const
        {
            return _hashtable.find(key);
        }
    private:
        HashBucket<K, std::pair<const K, V>, KeyOfMap, Hash> _hashtable;
    };

};
