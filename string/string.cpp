#include "string.h"


using namespace bit;

const size_t string::npos = -1;

string::string(string&& str)
{
    std::cout << "string(string&& str)" << std::endl;
    swap(str);
}

string& string::operator=(string&& str)
{
    std::cout << "operator=(string&& str)" << std::endl;
    swap(str);
    return *this;
}

std::ostream& bit::operator<<(std::ostream& _cout, const bit::string& s)
{
    for(auto it : s)
        _cout << it;

    return _cout;
}

std::istream& bit::operator>>(std::istream& _cin, bit::string& s)
{
    char ch;
    _cin.get(ch);
    char arr[129];
    int i = 0;
    while(ch != ' ' && ch != '\n')
    {
        if(i == 128)
        {
            arr[i] = '\0';
            s += arr;
            i = 0;
        }
        arr[i++] = ch;
        _cin.get(ch);
    }
    
    if(i != 0)
    {
        arr[i] = '\0';
        s += arr;
    }

    return _cin;
}

string::string(const char* str)
    :_size(strlen(str))
    ,_capacity(_size)
    ,_str(new char[_capacity + 1])
{
    std::cout << "string(const char* str)" << std::endl;
    strcpy(_str, str);
}

string::string(const string& s)
:_size(s._size)
,_capacity(s._capacity)
,_str(new char[_capacity+1])
{
    std::cout << "string(const string* str)" << std::endl;
    strcpy(_str, s._str);
}

string::~string()
{
    std::cout << "~string()" << std::endl;
    delete[] _str;
    _size = 0;
    _capacity = 0;
}

string& string::operator=(const string& s)
{
    std::cout << "operator=(const string&)" << std::endl;
    if(this != &s)  //地址比较，非内容比较
    {   
        char* tem = new char[s._capacity + 1];
        strcpy(tem, s._str);
        delete[] _str;
        _str = tem;
    }

    return *this;
}

void string::reserve(size_t n)
{
    if(_capacity >= n)
        return;

    _capacity = n;
    char * s = new char[n+1];
    strcpy(s, _str);
    delete [] _str;
    _str = s;
}


void string::push_back(char c)
{
    if(_size == _capacity)
        reserve(_capacity * 2);

    _str[_size++] = c;
}

string& string::operator+=(char c)
{
    push_back(c);
    return *this;
}

void string::append(const char* str)
{
    int len = strlen(str);
    if(_size + len > _capacity)
        reserve(_size + len);

    strcpy(_str + _size, str);
    _size += len;
}

string& string::operator+=(const char* str)
{
    append(str);
    return *this;
}

void string::clear()
{
    _str[0] = '\0';
    _size = 0;
}

void string::swap(string& s)
{
    std::swap(s._str, _str);
    std::swap(s._size, _size);
    std::swap(_capacity, s._capacity);
}

const char* string::c_str()const
{
    return _str;
}

size_t string::size()const
{
    return _size;
}

size_t string::capacity()const
{
    return _capacity;
}

bool string::empty()const
{
    return !_size;
}

void string::resize(size_t n, char c = '\0')
{
    if(n > _capacity)
    {
        reserve(n);
        while(_size < n)
        {
            _str[_size++] = c;
        }

        _str[_size] = '\0';
    }
    else 
    {
        _str[n] = '\0';
        _size = n;
    }
}

char& string::operator[](size_t index)
{
    assert(index <= _size);

    return _str[index];
}

const char& string::operator[](size_t index)const
{
    assert(index <= _size);

    return _str[index];
}

bool string::operator<(const string& s)
{
    for(int i = 0; i < _size; ++i)
    {
        if(s._str[i] < _str[i])
            return true;
    }

    return false;
}

bool string::operator<=(const string& s)
{
    return operator<(s) || operator==(s);
}

bool string::operator>(const string& s)
{
    return !operator<=(s);
}

bool string::operator==(const string& s)
{
    for(int i = 0; i < _size; ++i)
    {
        if(_str[i] != s._str[i])
            return false;
    }
    return true;
}

bool string::operator!=(const string& s)
{
    return !operator==(s);
}

bool string::operator>=(const string& s)
{
    return operator>(s) || operator==(s);
}

size_t string::find (char c, size_t pos) const
{
    while(pos < _size)
    {
        if(_str[pos] == c)
            return pos;
        ++pos;
    }

    return npos;
}

void string::Next(const char* str, int* next) const
{
    int i = 1, j = 0;
    next[1] = 0;
    int n = strlen(str);
    while(i < n)
    {
        if(j == 0 || str[i-1] == str[j-1])
        {
            ++i, ++j;
            if(str[i-1] != str[j-1]) 
                next[i] = j;
            else 
                next[i] = next[j];
        }
        j = next[j];
    }
}

size_t string::find (const char* s, size_t pos) const
{
    int n = _size;
    int m = strlen(s);
    int i = pos, j = 1;
    int next[m];
    Next(s, next);
    while (i <= n && j <= m)
    {
        if(j == 0 || _str[i-1] == s[j-1])
        {
            ++i, ++j;
        }
        else 
            j = next[j];
    }
    if(j > m)
        return i - m - 1;
    else 
        return npos;
}

string& string::insert(size_t pos, char c)
{
    assert(pos <= _size);

    if(_size >= _capacity)
        reserve(_capacity * 2);
    int end = _size + 1;
    while(end > pos)
    {
        _str[end] = _str[end-1];
        end--;
    }

    _str[pos] = c;
    _size++;

    return *this;
}

string& string::insert(size_t pos, const char* str)
{
    assert(pos <= _size);

    size_t n = strlen(str);
    int end = _size;
    if(_size + n > _capacity)
        reserve(_size + n);
    
    while(end >= (int)pos)
    {
        _str[end + n] = _str[end];
        --end;
    }
    
    strncpy(_str+pos, str, n);
    _size += n;

    return *this;
}

string& string::erase(size_t pos, size_t len)
{
    assert(pos < _size);

    if(len == npos || pos + len >= _size)
    {
        _str[pos] = '\0';
        _size = pos;   
    }
    else 
    {
        size_t begin = pos + len;
        while (begin <= _size)
        {
            _str[begin -len] = _str[begin++];
        } 
        _size -= len;
    }

    return *this;
}

string string::substr(size_t pos, size_t len)
{
    string tem;
    size_t end = len + pos;
    if(len == npos || pos + len >= _size)
    {
        len = _size - pos;
        end = _size;
    }

    tem.reserve(len);
    for(int i = pos; i < end; ++i)
    {
        tem += _str[i];
    }

    return tem;
}

