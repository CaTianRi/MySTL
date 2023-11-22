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

        iterator begin()const
        {
            return _t.begin();
        }

        iterator end()const 
        {
            return _t.end();
        }

        std::pair<iterator, bool> insert(const K& key)
        {   /*使用pair的拷贝(构造)函数来返回,如果是同类型则为拷贝，
            不同类型则为构造*/
            std::pair<typename RBTree<K, K, SetKeyOfT>::iterator, bool> ret = _t.Insert(key);
            return std::pair<iterator, bool>(ret.first, ret.second);
        }

    private:
        RBTree<K, K, SetKeyOfT> _t;
    };
}
