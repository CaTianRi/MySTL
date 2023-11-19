#include <iostream>
#include <utility>

enum Color
{
    RED,
    BLACK
};

template <class K, class V>
struct RBTreeNode
{
    RBTreeNode<K, V>* _left;
    RBTreeNode<K, V>* _right;
    RBTreeNode<K, V>* _parent;
    Color _col;
    std::pair<K, V> _kv;

    RBTreeNode(const std::pair<K, V>& kv)
        :_left(nullptr)
        ,_right(nullptr)
        ,_parent(nullptr)
        ,_kv(kv)
        ,_col(RED)
    {}
};

template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree()
	{
		_root = new Node;
		_root->_pLeft = _root;
		_root->_pRight = _root;
	}

    // 在红黑树中插入值为data的节点，插入成功返回true，否则返回false
    // 注意：为了简单起见，本次实现红黑树不存储重复性元素
	bool Insert(const std::pair<K, V>& data);
    
    // 检测红黑树中是否存在值为data的节点，存在返回该节点的地址，否则返回nullptr
    Node* Find(const std::pair<K, V>& data);
    
    // 获取红黑树最左侧节点
	Node* LeftMost();
    
    // 获取红黑树最右侧节点
	Node* RightMost();
    
    // 检测红黑树是否为有效的红黑树，注意：其内部主要依靠_IsValidRBTRee函数检测
	bool IsValidRBTRee();
private:
	bool _IsValidRBTRee(Node* pRoot, size_t blackCount, size_t pathBlack);
    // 左单旋
	void RotateL(Node* pParent);
    // 右单旋
	void RotateR(Node* pParent);
    // 为了操作树简单起见：获取根节点
	Node*& GetRoot();
private:
	Node* _root;
};

template <class K, class V> 
bool RBTree<K, V>::Insert(const std::pair<K, V>& data)
{
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
            false;
    }

    cur = new Node;
    cur->_parent = parent;

    if(!parent->_left)
        parent->_left = cur;
    else 
        parent->_right = cur;

    while (parent && parent->_col == RED)
    {
        Node* grandParent = parent->_parent;
        if(parent == grandParent->_left)
        {
            Node* uncle = parent->_right;
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
                    RotateR(parent);
                    parent->_col = BLACK;
                    grandParent->_col = RED;
                }
                else 
                {   //双旋
                   RotateL(parent);
                   RotateL(grandParent);
                   grandParent->_col = RED;
                   parent->_col = BLACK;
                }
                break;
            }
        }
        else 
        {
            Node* uncle = grandParent->_right;

            if(uncle->_col == BLACK)
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

                }
                else 
                {

                }
                break;
            }
        }
    }
}

template <class K, class V>
void RBTree<K, V>::RotateL(Node* parent)
{
    Node* subR = parent->_right;
    Node* subRL = subR->_left;

    Node* grandParent = parent->_parent;
    subR->_parent = grandParent;
    parent->_right = subR->_left;
    subR->_left = parent;
    parent->_parent = subR;

    if(subRL)
        subRL->_parent = parent;
    if(_root == parent)
    {
        _root = subR;
    }
    else 
    {
        if(parent == grandParent->_left)
            grandParent->_left = subR;
        else 
            grandParent->_right = subR;
    }
}

template <class K, class V>
void RBTree<K, V>::RotateR(Node* parent)
{
    Node* subL = parent->_left;
    Node* subLR = subL->_right;
    Node* grandParent = parent->_parent;

    subL->_right = parent;
    parent->_left = subLR;
    subL->_parent = grandParent;
    parent->_parent = subL;
    if (subLR)
        subLR->_parent = parent;

    if(parent == _root)
        _root = subL;
    else 
    {
        if(parent == grandParent->_left)
            grandParent->_left = subL;
        else
            grandParent->_right = subL;
    }
}
