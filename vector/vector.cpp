#include "vector.h"

using namespace bit;

template <class T>
vector<T>::vector(int n, const T& value)
{
    resize(n);
    for(size_t i = 0; i < n; ++i)
        push_back(value);
}

template <class T>
vector<T>::vector(size_t n, const T& value)
{
    resize(n);
    for(size_t i = 0; i < n; ++i)
        push_back(value);
}

template <typename T>
template <typename InputIterator>
vector<T>::vector(InputIterator first, InputIterator last)
{
    while(first != last)
    {
        push_back(*first);
        ++first;
    }
}

template <class T>
vector<T>::vector(const vector<T>& v)
{
    reserve(v.capacity());
    for(auto& it : v)
        push_back(it);
}

template<class T>
vector<T>& vector<T>::operator= (vector<T> v)
{
    swap(v);

    return *this;
}

template <class T> 
void vector<T>::reserve(size_t n)
{
    if(n <= size())
        return;

    T* temp = new T[n]; 
    size_t sz = size();
    if(_start)
    {
        for(size_t i = 0; i < sz; ++i)
        {
            temp[i] = _start[i];
        }
        delete[] _start;
    }
    _start = temp;
    _endOfStorage  = _start + n;
    _finish = _start + sz;
}

template <class T>
void vector<T>::resize(size_t n, const T& value)
{
    if(n > size())
        reserve(n);
    for (int i = 0; i < n; ++i)
    {
        _start[i] = value;
    }
}
