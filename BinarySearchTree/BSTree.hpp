#include <iostream>

using namespace std;

template <class K, class V>
struct BSTreeNode 
{
    K _key;
    V _value;
    BSTreeNode(const K& key, const V& value)
        :_key(key)
        ,_value(value)
        ,_left(nullptr)
        ,_right(nullptr)
    {}

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
void BSTree<K, V>::_InOrder(Node* root)
{
    if(!root)   return;

    _InOrder(root->_left);
    cout << root->_key << " : " << root->_value << endl;
    _InOrder(root->_right);
}

template <class K, class V>
void BSTree<K, V>::InOrder()
{
    _InOrder(_root);
}


template <class K, class V>
bool BSTree<K, V>::Erase(const K& key)
{
    Node* cur = _root;
    Node* prev = nullptr;
    while(cur)
    {
        if(cur->_key < key)
        {
            prev = cur;
            cur = cur->_right;
        }
        else if(cur->_key > key)
        {
            prev = cur;
            cur = cur->_left;
        }
        else 
            break;
    }
    if(cur == nullptr)
        return false;

    if(cur->_left && cur->_right)
    {
        Node* subRight = cur->_left;
        Node* parent = cur;
        while(subRight->_right)
        {
            parent = subRight;
            subRight = subRight->_right;
        }

        swap(cur->_key, subRight->_key);
        swap(cur->_value, subRight->_value);

        if(parent == cur)
        {
            delete subRight;
        }
        else if(subRight->_left)
        {
            parent->_right = subRight->_left;
        }
    }
    else if(cur->_right || cur->_left)
    {
        if(cur == _root)
        {
            _root = _root->_left ? _root->_left : _root->_right;
        }
        else if(cur->_left)
        {
            if(prev->_left == cur)
            {
                prev->_left = cur->_left;
            }
            else 
            {
                prev->_right = cur->_left;
            }
        }
        else 
        {
            if(prev->_right == cur)
            {
                prev->_right = cur->_right;
            }
            else 
            {
                prev->_left = cur->_right;
            }
        }
    }

    return true;
}

template <class K, class V>
typename BSTree<K, V>::Node* BSTree<K, V>::Find(const K& key)
{
    if(!_root)
        return nullptr;

    Node* cur = _root;
    while(cur)
    {
        if(cur->_key < key)
        {
            cur = cur->_right;
        }
        else if(cur->_key > key)
        {
            cur = cur->_left;
        }
        else 
        {
            return cur;
        }
    }

    return nullptr;
}

template <class K, class V>
bool BSTree<K, V>::Insert(const K& key, const V& value)
{
    if(!_root)
    {
        _root = new Node(key, value);
        return true;
    }

    Node* cur = _root;
    Node* prev = nullptr;
    while(cur)
    {
        prev = cur;
        if(cur->_key < key)
        {
            cur = cur->_right;
        }
        else if(cur->_key > key)
        {
            cur = cur->_left;
        }
        else 
        {
            return false;
        }
    }
    cur = new Node(key, value);

    if(prev->_key < key)
    {
        prev->_right = cur;
    }
    else 
    {
        prev->_left = cur;
    }

    return true;
}

