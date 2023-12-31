#pragma once
#include <iostream>
#include <new>
#include <system_error>
#include <utility>

enum Color
{
    RED,
    BLACK
};
template <class T>
struct RBTreeNode
{
    RBTreeNode<T>* _left;
    RBTreeNode<T>* _right;
    RBTreeNode<T>* _parent;
    Color _col;
    T _data;

    RBTreeNode(const T& data = T())
        :_left(nullptr)
        ,_right(nullptr)
        ,_parent(nullptr)
        ,_data(data)
        ,_col(RED)
    {}
};

template <class T, class Ref, class Ptr>
struct _TreeIterator
{
    typedef RBTreeNode<T> Node;
    typedef _TreeIterator<T, Ref, Ptr> self;
    typedef _TreeIterator<T, T&, T*> iterator;  //仿SGI-STL
    Node* _node;

    _TreeIterator(Node* node)
        :_node(node)
    {}

    _TreeIterator(const iterator& _it) //构造函数，方便set中的inset函数中的pair拷贝
        :_node(_it._node)
    {
    }
    
    Ref operator*()const
    {
        return _node->_data;
    }

    Ptr operator->()const
    {
        return &operator*();
    }

    self& operator--()
    {
        Node* cur = _node;
        if(cur->_col == RED && cur->_parent->_parent == cur)
        {
            cur = cur->_right;
        }
        if(cur->_left)
        {
            cur = cur->_left;
            while(cur->_right)
                cur = cur->_right;
        }
        else
        {
            Node* parent = cur->_parent;
            while(parent && cur == parent->_left)
            {
                cur = parent;
                parent = parent->_parent;
            }
            cur = parent;
        }
        _node = cur;

        return *this;
    }

    self&& operator--(int)
    {
        self tem = *this;
        Node* cur = _node;
        if(cur->_col == RED && cur->_parent->_parent == cur)
        {
            cur = cur->_right;
        }
        if(cur->_left)
        {
            cur = cur->_left;
            while(cur->_right)
                cur = cur->_right;
        }
        else
        {
            Node* parent = cur->_parent;
            while(parent && cur == parent->_left)
            {
                cur = parent;
                parent = parent->_parent;
            }
            cur = parent;
        }
        _node = cur;

        return tem;
    }

    self& operator++()
    {
        if(_node->_right)
        {
            Node* cur = _node->_right;
            while(cur->_left)
                cur = cur->_left;

            _node = cur;
        }
        else 
        {
            Node* cur = _node;
            Node* parent = cur->_parent;
            while(parent && cur == parent->_right)
            {
                cur = parent;
                parent = parent->_parent;
            }
            _node = parent;
        }

        return *this;
    }

    bool operator!=(const self& s)
    {
        return _node != s._node;
    }

    bool operator==(const self& s)
    {
        return _node == s._node;
    }
};


template<class K, class T, class KeyOfT>
class RBTree
{
public:
	typedef RBTreeNode<T> Node;
    typedef _TreeIterator<T, T&, T*> iterator;
    typedef _TreeIterator<T, const T&, const T*> const_iterator;
	RBTree()
	{
		_root = new Node;
		_root->_left = _root;
		_root->_right = _root;
	}

    const_iterator begin() const 
    {
        return const_iterator(LeftMost());
    }

    const_iterator end() const 
    {
        return const_iterator(_root);
    }

    iterator begin()
    {
        return iterator(LeftMost());
    }

    iterator end()
    {
        return iterator(_root);
    }

    // 在红黑树中插入值为data的节点，插入成功返回true，否则返回false
    // 注意：为了简单起见，本次实现红黑树不存储重复性元素
    std::pair<iterator, bool> Insert(const T& data);

    // 检测红黑树中是否存在值为data的节点，存在返回该节点的地址，否则返回nullptr
    iterator Find(const K& data);
    const_iterator Find(const K& data) const;
    
    // 获取红黑树最左侧节点
	Node* LeftMost()const;

    // 中序遍历
    void InOrder() 
    {
        _InOrder(GetRoot());
        std::cout << std::endl;
    }
    
    // 获取红黑树最右侧节点
	Node* RightMost()const;
    
    // 检测红黑树是否为有效的红黑树，注意：其内部主要依靠_IsValidRBTRee函数检测
	bool IsValidRBTRee();
private:
	bool _IsValidRBTRee(Node* pRoot, size_t blackCount, const size_t pathBlack);
    // 左单旋
	void RotateL(Node* pParent);
    // 右单旋
	void RotateR(Node* pParent);
    // 为了操作树简单起见：获取根节点
	Node*& GetRoot() const { return _root->_parent; }

    void rebalance(Node*& cur, Node*& parent)
    {
        while (parent != _root && parent->_col == RED)
        {
            Node* grandParent = parent->_parent;
            if(parent == grandParent->_left)
            {
                Node* uncle = grandParent->_right;
                if(uncle && uncle->_col == RED)
                {
                     parent->_col = uncle->_col = BLACK;
                     grandParent->_col = RED;

                     cur = grandParent;
                     parent = cur->_parent;
                }
                else 
                {
                    if(cur == parent->_left)
                    {   //右旋
                        RotateR(grandParent);
                        parent->_col = BLACK;
                        grandParent->_col = RED;
                    }
                    else 
                    {   //双旋
                       RotateL(parent);
                       RotateR(grandParent);
                       grandParent->_col = RED;
                       cur->_col = BLACK;
                    }
                    break;
                }
            }
            else 
            {
                Node* uncle = grandParent->_left;

                if(uncle && uncle->_col == BLACK)
                {
                     parent->_col = uncle->_col = BLACK;
                     grandParent->_col = RED;
                     cur = grandParent;
                     parent = cur->_parent;
                }
                else 
                {
                    if(cur == parent->_right)
                    {
                        RotateL(grandParent);
                        parent->_col = BLACK;
                        grandParent->_col = RED;
                    }
                    else 
                    {
                       RotateR(parent);
                       RotateL(grandParent);
                       grandParent->_col = RED;
                       cur->_col = BLACK;
                    }
                    break;
                }
            }
        }
        GetRoot()->_col = BLACK;
    }
private:
    void _InOrder(Node* root);
	Node* _root = nullptr;
    KeyOfT kot;
};


template <class K, class T, class KeyOfT>
typename RBTree<K, T, KeyOfT>::const_iterator RBTree<K, T, KeyOfT>::Find(const K& data) const
{
    Node* cur = GetRoot();
    while(cur)
    {
        if(kot(cur->_data) < data)
        {
            cur = cur->_right;
        }
        else if(kot(cur->_data) > data)
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

template <class K, class T, class KeyOfT>
typename RBTree<K, T, KeyOfT>::iterator RBTree<K, T, KeyOfT>::Find(const K& data) 
{
    Node* cur = GetRoot();
    while(cur)
    {
        if(kot(cur->_data) < data)
        {
            cur = cur->_right;
        }
        else if(kot(cur->_data) > data)
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

template <class K, class T, class KeyOfT>
void RBTree<K, T, KeyOfT>::_InOrder(Node* root)
{
    if(!root)   
        return;

    _InOrder(root->_left);
    std::cout << root->_data << " ";
    _InOrder(root->_right);
}


template <class K, class T, class KeyOfT>
typename RBTree<K, T, KeyOfT>::Node* RBTree<K, T, KeyOfT>::LeftMost()const
{
    return _root->_left;
}

template <class K, class T, class KeyOfT>
typename RBTree<K, T, KeyOfT>::Node* RBTree<K, T, KeyOfT>::RightMost()const
{
    return _root->_right;
}


template <class K, class T, class KeyOfT>
bool RBTree<K, T, KeyOfT>::IsValidRBTRee()
{
    if(!GetRoot() || GetRoot()->_col == RED)  return false;
    
    size_t pathBlack = 0;
    Node* cur = GetRoot();
    while(cur)
    {
        if(cur->_col == BLACK)
            ++pathBlack;
        cur = cur->_left;
    }
    int blackCount = 0;

    return _IsValidRBTRee(GetRoot(), blackCount, pathBlack);
}

template <class K, class T, class KeyOfT>
bool RBTree<K, T, KeyOfT>::_IsValidRBTRee(Node* pRoot, size_t blackCount, const size_t pathBlack)
{
    if(!pRoot)
    {
        if(blackCount != pathBlack)
        {
            std::cout << "有连续的红色结点" << std::endl;
            return false;
        }
        return true;
    }

    if(pRoot->_col == RED && pRoot->_parent->_col == RED)
    {
        std::cout << "有连续的红色结点" << std::endl;
        return false;
    }

    if(pRoot->_col == BLACK)
        ++blackCount;

    return _IsValidRBTRee(pRoot->_left, blackCount, pathBlack)
        && _IsValidRBTRee(pRoot->_right, blackCount, pathBlack);
}


template <class K, class T, class KeyOfT>   //或者改iterator为Node*。
std::pair<typename RBTree<K, T, KeyOfT>::iterator, bool> RBTree<K, T, KeyOfT>::Insert(const T& data)
{
    if(GetRoot() == nullptr)
    {
        Node* node = new Node(data);
        node->_col = BLACK;
        node->_parent = _root;
        _root->_parent = node;
        _root->_left = _root->_parent;
        _root->_right = _root->_parent;

        return std::make_pair(iterator(GetRoot()), true);
    }

    Node* cur = GetRoot();
    Node* parent = nullptr;
    while(cur)
    {
        if(kot(cur->_data) < kot(data))
        {
            parent = cur;
            cur = cur->_right;
        }
        else if(kot(cur->_data) > kot(data))
        {
            parent = cur;
            cur = cur->_left;
        }
        else 
            return std::make_pair(iterator(cur), false);
    }

    cur = new Node(data);
    Node* ret = cur;
    cur->_parent = parent;

    if(kot(cur->_data) < kot(parent->_data))
    {
        if (parent == _root->_left)
            _root->_left = cur;

        parent->_left = cur;
    }
    else 
    {
        if(parent == _root->_right)
            _root->_right = cur;

        parent->_right = cur;
    }

    rebalance(cur, parent);

    return std::make_pair(ret, true);
}

template <class K, class V, class KeyOfT>
void RBTree<K, V, KeyOfT>::RotateL(Node* parent)
{
    Node* subR = parent->_right;
    Node* subRL = subR->_left;
    Node* parentParent = parent->_parent;

    parent->_right = subRL;
    parent->_parent = subR;
	subR->_parent = parentParent;
    subR->_left = parent;
    if(subRL)
        subRL->_parent = parent;

    if(GetRoot() == parent)
    {
        GetRoot() = subR;
    }
    else 
    {
        if(parent == parentParent->_left)
        {
            parentParent->_left = subR;
        }
        else 
        {
            parentParent->_right = subR;
        }
    }
}

template <class K, class V, class KeyOfT>
void RBTree<K, V, KeyOfT>::RotateR(Node* parent)
{
    Node* subL = parent->_left;
    Node* subLR = subL->_right;
    Node* parentParent = parent->_parent;

    subL->_right = parent;
    subL->_parent = parentParent;

    parent->_left = subLR;
    parent->_parent = subL;

    if(subLR)
        subLR->_parent = parent;

    if(parent == GetRoot())
        GetRoot() = subL;
    else
    {
        if(parent == parentParent->_left)
            parentParent->_left = subL;
        else
            parentParent->_right = subL;
    }
} 
