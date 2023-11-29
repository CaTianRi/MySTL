#pragma once
#include <utility>
#include <iostream>
#include <vector>

template <class T>
struct HashBucketNode
{
    HashBucketNode<T>* _next;
    T _data;
    HashBucketNode(const T& data)
    :_data(data)
    ,_next(nullptr)
    {}
};


// 为了实现简单，在哈希桶的迭代器类中需要用到hashBucket本身，
template<class K, class T, class KeyOfValue, class HF>
class HashBucket;

// 注意：因为哈希桶在底层是单链表结构，所以哈希桶的迭代器不需要--操作
template <class K, class V, class Ref, class Ptr, class KeyOfValue, class HF>
struct HBIterator 
{
	typedef HashBucket<K, V, KeyOfValue, HF> HBK;
	typedef HashBucketNode<V> Node;
	typedef HBIterator<K, V, Ref, Ptr, KeyOfValue, HF> Self;
    typedef HBIterator<K, V, V&, V*, KeyOfValue, HF> iterator;

	Node* _node;             // 当前迭代器关联的节点
	const HBK* _pHt;         // 哈希桶--主要是为了找下一个空桶时候方便
    size_t _hashi;

    HBIterator(const iterator& it)
    :_node(it._node)
    ,_pHt(it._pHt)
    ,_hashi(it._hashi)
    {}
    
//    HBIterator(const Self& it)
//    :_node(it._node)
//    ,_pHt(it._pHt)
//    ,_hashi(it._hashi)
//    {}

	HBIterator(Node* pNode = nullptr, const HBK* pHt = nullptr, size_t hashi = -1)
    :_node(pNode)
    ,_pHt(pHt)
    ,_hashi(hashi)
    {}

    Self& operator++()
    {
        _node = _node->_next;
        if(!_node)
        {
            while(!_node && _hashi < _pHt->_ht.size())
            {
                _node = _pHt->_ht[++_hashi];
            }
        }
        if(_hashi >= _pHt->_ht.size())
            _node = nullptr;

        return *this;
    }

	Self operator++(int)
    {
        iterator tem = *this;
        ++*this;
        return tem;
    }

    Ref operator*()
    {
        return _node->_data;
    }

	Ptr operator->()
    {
        return &operator*();
    }

	bool operator==(const Self& it) const
    {
        return _node == it._node;
    }

	bool operator!=(const Self& it) const
    {
        return !operator==(it);
    }
};

template <class K>
struct HashFuc
{
    size_t operator()(const K& key)
    {
        return (size_t)key;
    }
};

template <>
struct HashFuc<std::string>
{
    size_t operator()(const std::string& str)
    {
        size_t hashi = 0;
        for(auto it : str)
        {
            hashi += (31 + it);
        }

        return hashi;
    }
};

template <class K, class T, class KeyOfValue, class HF = HashFuc<K>>
class HashBucket
{
    template<class Key, class Value, class Ref, class Ptr, class KeyOfT, class Hash>  //clang error
	friend struct HBIterator;

public:
    typedef HashBucketNode<T> Node;
    typedef HBIterator<K, T, T&, T*, KeyOfValue, HF> iterator;
    typedef HBIterator<K, T, const T&, const T*, KeyOfValue, HF> const_iterator;

    template <class InputIterator>
    HashBucket(InputIterator first, InputIterator last)
        :_size(0)
    {
        while(first != last)
        {
            insert(*first);
            ++first;
            ++_size;
        }
    }
    
    HashBucket()
    :_size(0)
    {
        _ht.resize(10);
    }

    ~HashBucket()
    {
        for(size_t i = 0; i < _ht.size(); ++i)
        {
            Node* node = _ht[i];
            while (node)
            {
                Node* next = node->_next;
                delete node;
                node = next;
            }
        }
    }

    //迭代器    //to do
    const_iterator begin() const
    {
        for(size_t i = 0; i < _ht.size(); ++i)
        {
            if(_ht[i])
            {
                return const_iterator(_ht[i], this, i);
            }
        }

        return end();
    }

    iterator begin()
    {
        for(size_t i = 0; i < _ht.size(); ++i)
        {
            if(_ht[i])
            {
                return iterator(_ht[i], this, i);
            }
        }

        return end();
    }

    iterator end()
    {
        return iterator(nullptr, this, -1);
    }

    const_iterator end() const
    {
        return const_iterator(nullptr, this, -1);
    }

    iterator find(const K& key)
    {
        size_t hashi = _hf(key) % _ht.size();
        
        Node* cur = _ht[hashi];
        while(cur)
        {
            if(_kot(cur->_data) == key)
                return iterator(cur, this, hashi);

            cur = cur->_next;
        }

        return iterator(cur);
    }

    std::pair<iterator, bool> insert(const T& val)    //插入
    {
        iterator it = find(_kot(val));
        if (it != end())
        {
            return std::make_pair(it, false);
        }
            
        CheckCapacity();

        size_t hashi = _hf(_kot(val)) % _ht.size();
        Node* node = new Node(val);

        node->_next = _ht[hashi];
        _ht[hashi] = node;
        _size++;
        
        return std::make_pair(iterator(node, this, hashi), true);
    }

    bool erase(const K& key)       //删除
    {
        size_t hashi = _hf(key) % _ht.size();
        Node* cur = _ht[hashi];
        Node* prev = nullptr;
        while(cur) 
        {
            if(_kot(cur->_data) == key)
            {
                if(!prev)
                {
                    _ht[hashi] = cur->_next;
                }
                else 
                {   
                    prev->_next = cur->_next;
                }
                
                --_size;
                delete cur;
                return true;
            }
            prev = cur;
            cur = cur->_next;
        }
        return false;
    }

    size_t size() { return _size; }
        
    bool empty() { return _size == 0; }
private:
	void CheckCapacity()
    {
        if(_size == _ht.size())
        {
            std::vector<Node*> newHT;
            newHT.resize(_ht.size() * 2, nullptr);
            for(size_t i = 0; i < _ht.size(); ++i)
            {
                Node* node = _ht[i];
                while(node)
                {
                    Node* next = node->_next;
                    size_t hashi = _hf(_kot(node->_data)) % newHT.size();
                    node->_next = newHT[hashi];
                    newHT[hashi] = node;

                    node = next;
                }
                _ht[i] = nullptr;
            }

            _ht.swap(newHT);
        }
    }
private:
    HF _hf;
    KeyOfValue _kot;
    std::vector<Node*> _ht;
    size_t _size;
};
