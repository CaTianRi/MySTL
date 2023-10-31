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
        typedef list_node<T>* Node;
        typedef ListIterator<T, Ref, Ptr> self;
    public:
        ListIterator();
        T& operator*();
        T* operator->();
        self& operator++();
        self operator++(int);
        self& operator--();
        self& operator--(int);
        bool operator!=(const self& l);
        bool operator==(const self& l);
    private:
        Node _node;
    };

    template <class T>
    class list 
    {
    public:
        typedef list_node<T> Node;
        typedef ListIterator<T, T&, T*> iterator;
        typedef ListIterator<const T, const T&, const T*> const_iterator;

        // list();
        list();
        list(int n, const T& value = T());
        list(const list<T>& l);
        list<T>& operator=(const list<T>& l); // or const list<T> l
        ~list();
        
        //list iterator
        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;
        
        //list capacity
        size_t size() const;
        bool empty() const;

        //list access
        T& front();
        const T& front() const;
        T& back();
        const T& back() const;

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
        Node* node;
    };
}
