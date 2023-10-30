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
            vector<T>();
            vector<T>(size_t size, size_t val);
    };
};
