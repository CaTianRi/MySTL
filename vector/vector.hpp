#pragma once
#include <iostream>
#include "../list/list.h"
#include <cassert>

namespace bit 
{
    template<class T>
    class vector 
    {
    public:
        // Vector的迭代器是一个原生指针
        typedef T* iterator;

        typedef const T* const_iterator;

        typedef Reverse_iterator<iterator, T&, T*> reverse_iterator;

        typedef Reverse_iterator<const_iterator, const T&, const T*> const_reverse_iterator;
            
        // reverse_iterator rbegin() { return end(); }  

        reverse_iterator rend() { return --begin(); }

        const_reverse_iterator rbegin() const { return --end(); }

        const_reverse_iterator rend() const { return --begin(); }

        iterator begin() { return _start; }

        iterator end() { return _finish; }

        const_iterator begin() const { return _start; }

        const_iterator end() const { return _finish; }
        // construct and destroy
        vector();

        vector(int n, const T& value = T());

        vector(size_t n, const T& value = T()); //重载size_t，避免使用到迭代器版本

        template<class InputIterator>
        vector(InputIterator first, InputIterator last);

        vector(const vector<T>& v);

        vector<T>& operator= (vector<T> v);

        ~vector();
        // capacity
        size_t size() const { return _finish - _start; };

        size_t capacity() const { return _endOfStorage - _start; };

        void reserve(size_t n);

        void resize(size_t n, const T& value = T());

        ///////////////access///////////////////////////////
        T& operator[](size_t pos);

        const T& operator[](size_t pos)const;

        ///////////////modify/////////////////////////////
        void push_back(const T& x);

        void pop_back();

        void swap(vector<T>& v);

        iterator insert(iterator pos, const T& x);

        iterator erase(iterator pos);
    private:
        iterator _start = nullptr; // 指向数据块的开始
        iterator _finish = nullptr; // 指向有效数据的尾
        iterator _endOfStorage = nullptr; // 指向存储容量的尾
    };

    template <class T>
    vector<T>::vector(int n, const T& value)
    {
        resize(n);
        for(size_t i = 0; i < n; ++i)
            push_back(value);
    }

    template <class T>
    vector<T>::vector()
        :_start(nullptr)
        ,_finish(nullptr)
        ,_endOfStorage(nullptr)
    {
    }
    
    template <class T>
    vector<T>::vector(size_t n, const T& value)
    {
        reserve(n);
        for(auto& it : value)
            push_back(it);
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
    
    //vector<T>还未实例化，在函数前加一个typename就是告诉编译器，这是一个类型，等它实例化再去类里面取
    template <class T>
    typename vector<T>::iterator vector<T>::insert(iterator pos, const T& x)
    {
        assert(pos <= _finish && pos >= _start);
        if(_finish == _endOfStorage)
        {
            size_t len = pos - _start;
            reserve(capacity() == 0 ? 4 : capacity() * 2);
            pos = _start + len;
        }
        iterator end = _finish;
        while(end > pos)
        {
            *end = *(end-1);
            end--;
        }

        *pos = x;
        _finish++;

        return pos;
    }
    
    template<class T>
    typename vector<T>::iterator vector<T>::erase(iterator pos)
    {
        assert(pos < _finish && pos >= _start);
        iterator it = pos + 1;
        while(it != _finish)
        {
            *(it-1) = *it;
            ++it;
        }
        _finish--;

        return pos;
    }
};
