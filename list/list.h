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
            ,_perv(nullptr)
            {
            }
    };

    template <class T>
    struct _list_iterator
    {
        list_node<T> _node;
        
    };

    template <class T>
    class list 
    {
    public:
        typedef list_node<T> Node;
        typedef _list_iterator<T> iterator;
    private:
        Node* node;
    };
}
