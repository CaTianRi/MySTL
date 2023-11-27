#include <utility>
#include <vector>
#include <unistr.h>

namespace bit
{
template <class K, class V>
struct HashBucketNode
{
    HashBucketNode<K, V>* _next;
    std::pair<K, V> _kv;
    HashBucketNode(const std::pair<K, V> data)
    :_kv(data)
    ,_next(nullptr)
    {}
};


// 为了实现简单，在哈希桶的迭代器类中需要用到hashBucket本身，
template<class K, class V, class KeyOfValue, class HF>
class HashBucket;

// 注意：因为哈希桶在底层是单链表结构，所以哈希桶的迭代器不需要--操作
template <class K, class V, class Ref, class Ptr, class KeyOfValue, class HF>
struct HBIterator 
{
	typedef HashBucket<K, V, KeyOfValue, HF> HashBucket;
	typedef HashBucketNode<K, V> Node;
	typedef HBIterator<K, V, Ref, Ptr, KeyOfValue, HF> Self;
    typedef HBIterator<K, V, V&, V*, KeyOfValue, HF> iterator;

    HBIterator(iterator& it)
    :_node(it._node)
    ,_pHt(it._pHt)
    {}

	HBIterator(Node* pNode = nullptr, HashBucket* pHt = nullptr, size_t hashi = -1)
    :_node(pNode)
    ,_pHt(pHt)
    ,_hashi(hashi)
    {}

    Self& operator++();
	Self operator++(int);
    Ref operator*();
	Ptr operator->();
	bool operator==(const Self& it) const;
	bool operator!=(const Self& it) const;
	Node* _node;             // 当前迭代器关联的节点
	HashBucket* _pHt;         // 哈希桶--主要是为了找下一个空桶时候方便
    size_t _hashi;
};

template <class K>
struct HashFuc
{
    size_t operator()(const K& key)
    {
        return (size_t)key;
    }
};

template <class K, class T, class KeyOfValue, class HF = HashFuc<K>>
class HashBucket
{
    typedef HashBucketNode<K, T> Node;

    template<class Key, class Value, class Ref, class Ptr, class KeyOfT, class Hash>  //clang error
	friend struct HTIterator;

    typedef HBIterator<K, T, T&, T*, KeyOfValue, HF> iterator;
    typedef HBIterator<K, T, const T&, const T*, KeyOfValue, HF> const_iterator;

    //迭代器    //to do
    const_iterator begin() const;   
    iterator begin();
    iterator end();
    const_iterator end() const;

    
    iterator find(const K& key)
    {
        size_t hashi = HF(key) % _ht.size();
        if(_ht[hashi] == nullptr)
            return iterator(nullptr);
        
        Node* cur = _ht[hashi];
        while(cur)
        {
            if(KeyOfValue(cur->_kv) == key)
                return iterator(cur, this, hashi);

            cur = cur->_next;
        }

        return cur;
    }

    std::pair<iterator, bool> insert(const T& val)    //插入
    {
        iterator it = find(KeyOfValue(kot(val)));
        if (it != nullptr)
        {
            return std::make_pair(it, false);
        }
            
        CheckCapacity();

        size_t hashi = HF(KeyOfValue(val)) % _ht.size();
        Node* node = new Node(val);

        node->_next = _ht[hashi];
        _ht[hashi] = node;
        _size++;
        
        return std::make_pair(iterator(node, this, hashi), true);
    }

    bool erase(const K& key);       //删除

    size_t size() { return _size; }
        
    bool empty() { return _size == 0; }

private:
	void CheckCapacity()
    {
        if(_size * 10 / _ht.size() >= 1)
        {
            HashBucket<K, V, KeyOfValue, HF> newHT;
            newHT._ht.resize(_ht.size() * 2);           // ToDo             
            for(size_t i = 0; i < _ht.size(); ++i)
            {
                newHT.insert();
            }

            _ht.swap(newHT._ht);
        }
    }

    std::vector<Node*> _ht;
    size_t _size;
};


// unordered_map中存储的是pair<K, V>的键值对，K为key的类型，V为value的类型，HF哈希函数类型
// unordered_map在实现时，只需将hashbucket中的接口重新封装即可
template<class K, class V, class HF = DefHashF<K>>
class unordered_map
{
    typedef HashBucket<K, pair<K, V>, KeyOfValue, HF> HT;
    // 通过key获取value的操作
	struct KeyOfValue
	{
		const K& operator()(const pair<K, V>& data)
		{ return data.first;}
	};
public:
	typename typedef HT::Iterator iterator;
public:
	unordered_map(): _ht()
	{}
	////////////////////////////////////////////////////
	iterator begin(){ return _ht.begin();}
	iterator end(){ return _ht.end();}
	////////////////////////////////////////////////////////////
	// capacity
	size_t size()const{ return _ht.size();}
	bool empty()const{return _ht.empty();}
	///////////////////////////////////////////////////////////
	// Acess
	V& operator[](const K& key)
	{
		pair<iterator, bool> ret = _ht.InsertUnique(pair<K, V>(key, V()));
        return ret.fisrt->second;
	}
	const V& operator[](const K& key)const;
	//////////////////////////////////////////////////////////
	// lookup
	iterator find(const K& key){ return _ht.Find(key);}
	size_t count(const K& key){ return _ht.Count(key);}
	/////////////////////////////////////////////////
	// modify
	pair<iterator, bool> insert(const pair<K, V>& valye)
	{ return _ht.Insert(valye);}

	iterator erase(iterator position)
	{ return _ht.Erase(position);}
    ////////////////////////////////////////////////////////////
	// bucket
	size_t bucket_count(){ return _ht.BucketCount();}
	size_t bucket_size(const K& key){ return _ht.BucketSize(key);}
private:
	HT _ht;
};
}
