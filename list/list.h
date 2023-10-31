#include <iostream>

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
    };

    template <class T, class Ref, class Ptr>
    class ListIterator
    {
        typedef list_node<T> Node;
        typedef ListIterator<T, Ref, Ptr> self;
    public:
        ListIterator(Node* node = nullptr)
            :_node(node) 
        {}

        ListIterator(const self& l) :_node(l._node) {} 

        T& operator*() { return _node->_data; };
        T* operator->() { return _node->_next; };

        self& operator++() 
        {
            _node = _node->_next;
            return _node;
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

            return _node;
        }

        self& operator--(int)
        {
            self tem(_node);
            _node = _node->prev;
            return tem;
        }

        bool operator!=(const self& l)
        {
            return _node != l._node;
        }

        bool operator==(const self& l)
        {
            return _node == l._node;
        }

    private:
        Node* _node;
    };

    template <class T>
    class list 
    {
    public:
        typedef list_node<T> Node;
        typedef ListIterator<T, T&, T*> iterator;
        typedef ListIterator<const T, const T&, const T*> const_iterator;

        // list();
        list() { init(); };
        list(int n, const T& value = T());
        list(const list<T>& l);
        list<T>& operator=(const list<T>& l); // or const list<T> l
        ~list();
        
        //list iterator
        iterator begin() { return _node->_next; }
        iterator end() { return _node; }
        const_iterator begin() const { return _node->_next; }
        const_iterator end() const { return _node; }
        
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
        for(int i = 0; i < n; ++i)
        {
            push_back(value);
        }
    }

    template <class T>
    void list<T>::push_back(const T& val)
    {
        Node* cur = new Node(val);
        cur->_next = _node;
        cur->_perv = _node->_perv;
        _node->_perv = cur;
    }

    template <class T>
    void list<T>::pop_back()
    {
        delete _node->_perv;
    }


}
