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

void test_vector3()
{
    using namespace bit;
    vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	v.push_back(7);

	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;

	vector<int>::iterator it = v.begin() + 2;
	v.insert(it, 30);
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;

	//v.insert(v.begin(), 30);
	v.insert(v.begin()+3, 30);
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl << endl;
}

void test_vector4()
{
    bit::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	v.push_back(7);

	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;

	auto pos = v.begin();
	v.erase(pos);

	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;

	v.erase(v.begin()+3);
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl << endl;
}

void test_5()
{
    bit::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	v.push_back(7);

    bit::vector<int>::reverse_iterator it = v.rbegin();
    while(it != v.rend())
    {
        cout << *it << " ";
        ++it;
    }
    cout << endl;
}

int main()
{
    test_1();
    test_2();
    test_vector3();
    test_vector4();
    test_5();
    return 0;
}
