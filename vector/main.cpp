#include "vector.hpp"

using namespace std;

void test_1()
{
    bit::vector<int> nums;
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(3);
    nums.push_back(4);
    nums.push_back(5);
    nums.push_back(6);

    for(auto it : nums)
        cout << it << " ";
    cout << endl;

    bit::vector<int>::iterator it = nums.begin();
    while(it != nums.end())
    {
        if(*it % 2 == 0)
            *it += 10;
        cout << *it << " ";
        ++it;
    }
    cout << endl;

    for(size_t i = 0; i < nums.size(); ++i)
        cout << nums[i] << " ";
    cout << endl << endl;
}

void test_2()
{
    int i = 0;
    bit::vector<int*> v1;
    v1.resize(10);
    bit::vector<string> v2;
    v2.resize(10, "xxx");

    for(auto e : v1)
    {
        cout << e << " ";
    }
    cout << endl;

    for(auto e : v2)
    {
        cout << e << " ";
    }
    cout << endl << endl;
}

int main()
{
    test_1();
    test_2();
    return 0;
}
