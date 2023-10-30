#pragma once

#include <iostream>

namespace bit 
{
    template<class T>
    class vector 
    {
        private:
            T* _data;
            size_t _capacity;
            size_t _size;
        public:
            // Vector的迭代器是一个原生指针
            typedef T* iterator;

            typedef const T* const_iterator;

            iterator begin();

            iterator end();

            const_iterator cbegin();

            const_iterator cend() const;
    };
};
