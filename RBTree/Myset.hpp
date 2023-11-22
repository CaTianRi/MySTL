#include "RBTree.hpp"

namespace bit
{
    template <class K>
    class set
    {
    public:
        struct SetKeyOfT
        {
            const K& operator()(const K& key)
            {
                return key;
            }
        };
        typedef typename RBTree<K, K, SetKeyOfT>::const_iterator iterator;
        typedef typename RBTree<K, K, SetKeyOfT>::const_iterator const_iterator;

        iterator begin()
        {
            return _t.begin();
        }

        iterator end() 
        {
            return _t.end();
        }

        const_iterator begin() const
        {
            return _t.begin();
        }

        const_iterator end() const
        {
            return _t.end();
        }

        std::pair<iterator, bool> insert(const K& key)
        {
            return _t.Insert(key);
        }

    private:
        RBTree<K, K, SetKeyOfT> _t;
    };
}
