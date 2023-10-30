#pragma once

#include <iostream>
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

        iterator begin() { return _start; }

        iterator end() { return _finish; }

        const_iterator begin() const { return _start; }

        const_iterator end() const { return _finish; }
        // construct and destroy
        vector();

        vector(int n, const T& value = T());

        vector(size_t n, const T& value = T());

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
    
   

};
