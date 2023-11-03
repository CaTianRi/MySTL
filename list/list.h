#include <iostream>
#include <cassert>

namespace bit 
{
    template <class T>
    struct list_node
    {
        T _data;
        list_node<T>* _next;
        list_node<T>* _perv;
        list_node(const T& data = T())
            :_data(data)
            ,_next(nullptr)
            ,_perv(nullptr) {}
    };
    
    template <class Iterator, class Ref, class Ptr>
    struct Reverse_iterator 
    {
        Iterator _it;
        Reverse_iterator(Iterator it) :_it(it) {}
        typedef Reverse_iterator<Iterator, Ref, Ptr> self;
        Ref operator*()
        {
            return *_it;
        }
        
        Ptr operator->()
        {
            return _it.operator->();
        }

        self& operator++()
        {
            --_it;

            return *this;
        }

        self operator++(int)
        {
            self tem(*this);
            --_it;

            return tem;
        }

        self& operator--()
        {
            ++_it;
            
            return *this;
        }

        self operator--(int)
        {
            self tem(*this);
            ++_it;

            return tem;
        }

        bool operator!=(const self& l)
        {
            return _it != l._it;
        }

        bool operator==(const self& l)
        {
            return _it == l._it;
        }
    };

    template <class T, class Ref, class Ptr>
    class ListIterator
    {
        typedef list_node<T> Node;
        typedef ListIterator<T, Ref, Ptr> self;
    public:
        Node* _node;
        ListIterator(Node* node = nullptr)
            :_node(node) 
        {}

        ListIterator(const self& l) :_node(l._node) {} 

        Ref operator*() { return _node->_data; };
        Ptr operator->() { return &_node->_data; };

        self& operator++() 
        {
            _node = _node->_next;
            return *this;
        };

        self operator++(int)
        {
            self tem(*this);
            _node = _node->_next;

            return tem;
        }

        self& operator--()
        {
            _node = _node->_perv;

            return *this;
        }

        self& operator--(int)
        {
            self tem(_node);
            _node = _node->prev;

            return *this;
        }

        bool operator!=(const self& l)
        {
            return _node != l._node;
        }

        bool operator==(const self& l)
        {
            return _node == l._node;
        }
    };

    template <class T>
    class list 
    {
    public:
        typedef list_node<T> Node;
        typedef ListIterator<T, T&, T*> iterator;
        typedef ListIterator<T, const T&, const T*> const_iterator;
        typedef Reverse_iterator<iterator, T&, T*> reverse_iterator;
        typedef Reverse_iterator<const_iterator, const T&, const T*> const_reverse_iterator;

        // list();
        list() { init(); };
        list(int n, const T& value = T());
        list(const list<T>& l);
        list<T>& operator=(list<T> l); // or const list<T> 
        ~list() ;
        
        //list iterator
        iterator begin() { return _node->_next; }
        iterator end() { return _node; }
        const_iterator begin() const { return _node->_next; }
        const_iterator end() const { return _node; }

        // reverse_iterator
        reverse_iterator rbegin() { return reverse_iterator(_node->_perv); }
        reverse_iterator rend() { return reverse_iterator(_node); }
        const_reverse_iterator  rbegin() const { return reverse_iterator(_node->_perv); }
        const_reverse_iterator rend() const { return reverse_iterator(_node); }

        
        //list capacity
        size_t size() const { return _node->_perv - _node; }
        bool empty() const { return _node->_next == _node; }

        //list access
        T& front() { return _node->_next; }
        const T& front() const { return _node->_next; } 
        T& back() { return _node->_perv; }
        const T& back() const { return _node->_perv; }

        //list Modify
        void push_back(const T& val);
        void pop_back();
        void pop_front();
        iterator insert(iterator pos, const T& val);
        iterator erase(iterator pos);
        void clear();
        void swap(list<T>& l);
    private:
        void init();
        Node* _node;
    };

    template <class T>
    void list<T>::init()
    {
        _node = new Node;
        _node->_perv = _node;
        _node->_next = _node;
    }

    template <class T>
    list<T>::list(int n, const T& value)
    {
        init();
        for(int i = 0; i < n; ++i)
        {
            push_back(value);
        }
    }

    template <class T>
    list<T>::list(const list<T>& l)
    {
        init();
        for(auto it : l)
            push_back(it);
    }

    template <class T>
    list<T>& list<T>::operator=(list<T> l)
    {
        swap(l);
        return *this;
    }

    template <class T>
    list<T>::~list()
    {
        while(size())
        {
            pop_back();
        }
        delete _node;
        _node = nullptr;
    }

    template <class T>
    void list<T>::push_back(const T& val)
    {
        Node* cur = new Node(val);
        cur->_next = _node;
        cur->_perv = _node->_perv;
        _node->_perv->_next = cur;
        _node->_perv = cur;
      //  insert(end(), val);
    }

    template <class T>
    void list<T>::pop_back()
    {
        assert(size() > 0);

        Node* pev = _node->_perv->_perv;
        delete _node->_perv;
        _node->_perv = pev;
        pev->_next = _node;
    }
    
    template <class T>
    void list<T>::pop_front()
    {
        assert(size() > 0);

        Node* tem = _node->_next->_next;
        delete _node->_next;
        tem->_perv = _node;
        _node->_next = tem;
    }
    
    template <class T>
    typename list<T>::iterator list<T>::insert(iterator pos, const T& val)
    {
        Node* cur = pos._node, * perv = cur->_perv;
        Node* node = new Node(val);
        perv->_next = node;
        node->_perv = perv;
        node->_next = cur;
        cur->_perv = node;

        return node;
    }

    template <class T>
    typename  list<T>::iterator list<T>::erase(iterator pos)
    {
        Node* cur = pos._node;
        Node* perv = cur->_perv;
        cur->_next->_perv = perv;
        perv->_next = cur->_next;
 
        delete cur;
        return perv->_next;
    }
    
    template <class T>
    void list<T>::clear()
    {
        while(size())
            pop_back();
    }

    template <class T>
    void list<T>::swap(list<T>& l)
    {
        std::swap(_node, l._node);
    }
}
