#include <iostream>

using namespace std;

template <class K, class V>
struct BSTreeNode 
{
    K _key;
    V _value;
    BSTreeNode<K, V>* _left;
    BSTreeNode<K, V>* _right;
};

template<class K, class V>
class BSTree
{
typedef BSTreeNode<K, V> Node;
public:
	bool Insert(const K& key, const V& value);
	Node* Find(const K& key);
	bool Erase(const K& key);
	void _InOrder(Node* root);
	void InOrder();
private:
	Node* _root = nullptr;
};

template <class K, class V>
bool BSTreeNode::Insert(const K& key, const V& value)
{
    
}

