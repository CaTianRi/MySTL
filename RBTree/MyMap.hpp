#pragma once
#include "RBTree.hpp"

namespace bit
{
    template <class K, class T>
    class map 
    {
    private:
        struct Mapkot 
        {
            const K& operator()(const std::pair<K, T>& value) const
            {
                return value.first;
            }
        };
    public:
        typedef typename RBTree<K, std::pair<const K, T>, Mapkot>::iterator iterator;
        typedef typename RBTree<K, std::pair<const K, T>, Mapkot>::const_iterator const_iterator;

        const_iterator end() const 
        {
            return _t.end();
        }

        const_iterator begin() const
        {
            return _t.begin();
        }

        iterator end()
        {
            return _t.end();
        }

        iterator begin()
        {
            return _t.begin();
        }
        
        std::pair<iterator,bool> insert(const std::pair<const K, T> data)
        {
            return _t.Insert(data);
        }

        T& operator[](const K& key)
        {
            auto ret = _t.Insert(std::make_pair(key,T()));
            return ret.first->second;
        }
    private:
        RBTree<K, std::pair<const K, T>, Mapkot> _t;
    };
}
