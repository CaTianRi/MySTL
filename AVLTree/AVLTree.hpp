#include <iostream>
#include <cassert>
#include <pstl/glue_execution_defs.h>
#include <utility>

template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode(const std::pair<K, V> kv)
	: _left(nullptr)
	, _right(nullptr)
	, _parent(nullptr)
    , _kv(kv)
	, _bf(0)
	{}

	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
    std::pair<K, V> _kv;
	int _bf;   // 节点的平衡因子
};

// AVL: 二叉搜索树 + 平衡因子的限制
template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		: _root(nullptr)
	{}

    // 在AVL树中插入值为data的节点
	bool Insert(const std::pair<K, V> data);
    
    // AVL树的验证
	bool IsAVLTree()
	{
		return _IsAVLTree(_root);
	}

private:
    // 根据AVL树的概念验证pRoot是否为有效的AVL树
	bool _IsAVLTree(Node* pRoot);
	size_t _Height(Node* pRoot);
    // 右单旋
	void RotateR(Node* pParent);
    // 左单旋
	void RotateL(Node* pParent);
    // 右左双旋
	void RotateRL(Node* pParent);
    // 左右双旋
	void RotateLR(Node* pParent);

private:
	Node* _root;
};

template <class K, class V>
void AVLTree<K, V>::RotateR(Node* parent)
{
    Node* subL = parent->_left;
    Node* subLR = subL->_right;
    Node* parentParent = parent->_parent;

    subL->_left = parent;
    parent->_left = subL;
    subL->_parent = parentParent;
    parent->_parent = subL;
    if(parent == _root)
        _root = subL;
    else
    {
        if(parent == parentParent->_left)
            parentParent->_left = subL;
        else
            parentParent->_right = subL;

        subL->_parent = parentParent;
    }

    subL->_bf = parent->_bf = 0;
} 

template <class K, class V>
void AVLTree<K, V>::RotateRL(Node* parent)
{
    Node* subR = parent->_right;
    Node* subRL = subR->_left;
    int bf = subRL->_bf;

    RotateR(parent->_right);
    RotateL(parent);

    if(bf == 0)
    {
        parent->_bf = subR->_bf = subRL->_bf = 0;
    }
    else if(bf == 1)
    {
        parent->_bf = -1;
        subR->_bf = 0;
        subRL->_bf = 0;
    }
    else if(bf == -1)
    {
        subRL->_bf = 0;
        subR->_bf = 0;
        parent->_bf = 1;
    }
    else 
    {
        assert(false);
    }
}


template <class K, class V>
void AVLTree<K, V>::RotateLR(Node* parent)
{
    Node* subL = parent->_left;
    Node* subLR = subL->_right;
    int bf = subLR->_bf;

    RotateL(parent->_left);
    RotateR(parent);

    if(bf == 0)
    {
        parent->_bf = subL->_bf = subLR->_bf = 0;
    }
    else if(bf == -1)
    {
        parent->_bf = -1;
        subL->_bf = 0;
        subLR->_bf = 0;
    }
    else if(bf == 1)
    {
        parent->_bf = 0;
        subL->_bf = 0;
        subLR->_bf = 1;
    }
    else 
    {
        assert(false);
    }
}

template <class K, class V>
bool AVLTree<K, V>::Insert(const std::pair<K, V> data)
{
    if(!_root)
    {
        _root = new Node(data);
        return true;
    }

    Node* cur = _root;
    Node* parent = nullptr;
    
    while(cur)
    {
        if(cur->_kv.first < data.first)
        {
            parent = cur;
            cur = cur->_right;
        }
        else if(cur->_kv.first > data.first)
        {
            parent = cur;
            cur = cur->_left;
        }
        else 
            return false;
    }

    cur = new Node(data);
    cur->_parent = parent;
    
    if(!parent->_left)
    {
        parent->_left = cur;
    }
    else 
    {
        parent->_right = cur;
    }

    while(parent)
    {
        if(cur == parent->_left)
            parent->_bf--;
        else
            parent->_bf++;

        if(parent->_bf == 0)
            break;
        else if(parent->_bf == 1 || parent->_bf == -1)
        {
            cur = parent;
            parent = parent->_parent;
        }
        else if(parent->_bf == 2 || parent->_bf == -2)
        {
            if(parent->_bf == 2 && cur == 1)
            {
                RotateL(parent);
            }
            else if(parent->_bf == -2 && cur == -1)
            {
                RotateR(parent);
            }
            else if(parent->_bf == 2 && cur == -1)
            {
                RotateRL(parent);
            }
            else if(parent->_bf == -2 && cur == 1)
            {
                RotateLR(parent);
            }

            break;
        }
        else 
            assert(false);
    }
}

template <class K, class V>
void AVLTree<K, V>::RotateL(Node* parent)
{
    Node* subR = parent->_right;
    Node* subRL = subR->_left;
    Node* parentParent = parent->_parent;

    parent->_right = subR->_left;
    subR->_left = parent;
    subR->_parent = parent->_parent;
    parent->_parent = subR;
    if(subRL)
        subRL->_parent = parent;
    if(_root == parent)
    {
        _root = subR;
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
    parent->_bf = subR->_bf = 0;
}
