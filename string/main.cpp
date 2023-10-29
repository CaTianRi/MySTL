#include "string.h"

using namespace std;

void test_1()
{
    bit::string str("Hello World");
    for(auto it : str)
        cout << it;
    cout << endl;

    str.push_back('x');
    str += "here!";
    cout << str << endl;
    cout << (void*)str.c_str() << endl << endl;
}

void test_2()
{
    bit::string str;
    bit::string s2;

    cin >> str;
    cout << str << endl;
    s2 = str;

    cout << (str == s2) << endl;
    cout << (str < s2) << endl;
    cout << (str > s2) << endl;
    cout << (str <= s2) << endl;
    cout << (str <= s2) << endl;
}

void test_3()
{
    bit::string s1 = "https://edu.bitejiuyeke.com/personInf/student?userId=15533";
    size_t i1 = s1.find(':');
    bit::string sub1;
    if(i1 != string::npos)
        sub1 = s1.substr(0,i1);

    bit::string sub2;
    size_t i2 = s1.find('/', i1+3);
    if(i2 != string::npos)
        sub2 = s1.substr(i1+3, (i2 - (i1 + 3)));

    bit::string sub3 = s1.substr(i2+1);

    cout << s1<< endl;
    cout << sub1 << endl;
    cout << sub2 << endl;
    cout << sub3 << endl << endl;
}

void test_4()
{
    bit::string s1 = "hello world";
    s1.insert(5, "abcx");
    cout << s1 << endl;
    s1.insert(0,"abcd");
    cout << s1 << endl;
    s1.erase(1);
    cout << s1 << endl << endl;
}


int main()
{
    test_1();
    test_2();
    test_3();
    test_4();

    return 0;
}
