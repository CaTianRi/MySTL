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
vector<T>::~vector()
{
    delete [] _start;
    _start = nullptr;
    _finish = nullptr;
    _endOfStorage = nullptr;
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
    if(n <= size())
        _finish = _start + n;
    else 
    {
        reserve(n);
        while(_finish < _start + n)
        {
            *_finish = value;
            ++_finish;
        }
    }
}

template <class T>
T& vector<T>::operator[](size_t pos)
{
    assert(pos <= size());

    return _start[pos];
}

template <class T>
const T& vector<T>::operator[](size_t pos)const
{
    return _start[pos];
}

template <class T>
void vector<T>::push_back(const T& x)
{
    if(_finish == _endOfStorage)
        reserve(capacity() == 0 ? 4 : capacity() * 2);

    *_finish = x;
    ++_finish;
}

template <class T>
void vector<T>::pop_back()
{
    assert(_finish != _start);

    --_finish;
}

template <class T>
void vector<T>::swap(vector<T>& v)
{
    std::swap(_start, v._start);
    std::swap(_endOfStorage, v._endOfStorage);
    std::swap(_finish, v._finish);
}


template <class T>
vector<T>::iterator vector<T>::insert(iterator pos, const T& x)
{
    
}
