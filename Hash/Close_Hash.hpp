#include <iostream>
#include <vector>
#include <utility>
// 注意：假如实现的哈希表中元素唯一，即key相同的元素不再进行插入
// 为了实现简单，此哈希表中我们将比较直接与元素绑定在一起
namespace Close_Hash
{
	enum State{ EMPTY, EXIST, DELETE };

	template<class K, class V>
	class HashTable
	{
		struct Elem
		{
            std::pair<K, V> _kv;
			State _state;
		};

	public:
		HashTable(size_t capacity = 3)
			: _ht(capacity), _size(0), _totalSize(0)
		{
			for (size_t i = 0; i < capacity; ++i)
				_ht[i]._state = EMPTY;
		}

        void print()
        {
            for(int i = 0; i < _ht.size(); ++i)
            {
                if(_ht[i]._state == EXIST)
                    std::cout << _ht[i]._kv.first << ":" << _ht[i]._kv.second << std::endl;
            }
        }

		// 插入
		bool Insert(const std::pair<K, V>& val)
        {
            if(Find(val.first) != -1)
                return false;
            
            CheckCapacity();
                    
            size_t hashi = HashFunc(val.first);
            while(_ht[hashi]._state == EXIST)
            {
                hashi++;

                hashi %= _ht.size();
            }

            _ht[hashi]._kv = val;
            _ht[hashi]._state = EXIST;
            ++_size;

            return true;
        }

		// 查找
		size_t Find(const K& key)
        {
            size_t hashi = HashFunc(key);
            CheckCapacity();
            while(_ht[hashi]._state != EMPTY)
            {
                if(_ht[hashi]._state == EXIST
                && _ht[hashi]._kv.first == key)
                    return hashi;
                
                hashi++;
                hashi %= _ht.size();
            }

            return -1;
        }

		// 删除
		bool Erase(const K& key)
        {
            size_t hashi = Find(key);
            if(hashi == -1) return false;

            _ht[hashi]._state = DELETE;
            --_size;
            return true;
        }

		size_t Size()const
		{
			return _size;
		}

		bool Empty() const
		{
			return _size == 0;
		}

		void Swap(HashTable<K, V>& ht)  //交换节点
		{
            std::swap(_size, ht._size);
            std::swap(_totalSize, ht._totalSize);
			_ht.swap(ht._ht);
		}


	private:
		size_t HashFunc(const K& key)
		{
			return key % _ht.capacity();
		}

		void CheckCapacity()
        {
            if(_size * 10 / _ht.size() >= 7)
            {
                HashTable<K, V> newHT;
                newHT._ht.resize(_ht.size() * 2);
                for(size_t i = 0; i < _ht.size(); ++i)
                {
                    if(_ht[i]._state == EXIST)
                        newHT.Insert(_ht[i]._kv);
                }

                _ht.swap(newHT._ht);
            }
        }
	private:
        std::vector<Elem> _ht;
		size_t _size;
		size_t _totalSize;  // 哈希表中的所有元素：有效和已删除, 扩容时候要用到
	};
}

