#include "list.h"

using namespace std;

void test_list1()
{
    using namespace bit;

	list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(5);
    for(auto it : lt)
    {
        cout << it << " ";
    }
    cout << endl;
	// 封装屏蔽底层差异和实现细节
	// 提供统一的访问修改遍历方式12
	list<int>::iterator it = lt.begin();
	while (it != lt.end())
	{
		*it += 20;

		cout << *it << " ";
		++it;
	}
	cout << endl;

	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl << endl;

	/*set<int> s;
	s.insert(1);
	s.insert(3);
	s.insert(2);
	s.insert(4);

	set<int>::iterator sit = s.begin();
	while (sit != s.end())
	{
		cout << *sit << " ";
		++sit;
	}
	cout << endl;*/
}

void test_list2()
{
    bit::list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(5);

    bit::list<int> lt1(lt);

	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;

	for (auto e : lt1)
	{
		cout << e << " ";
	}
	cout << endl;

    bit::list<int> lt2;
	lt2.push_back(10);
	lt2.push_back(200);
	lt2.push_back(30);
	lt2.push_back(40);
	lt2.push_back(50);

	lt1 = lt2;
	for (auto e : lt1)
	{
		cout << e << " ";
	}
	cout << endl;

	for (auto e : lt2)
	{
		cout << e << " ";
	}
	cout << endl;
}

struct AA
{
	AA(int a1 = 0, int a2 = 0)
		:_a1(a1)
		,_a2(a2)
	{}

	int _a1;
	int _a2;
};

void test_list3()
{
    bit::list<AA> lt;
	lt.push_back(AA(1, 1));
	lt.push_back(AA(2, 2));
	lt.push_back(AA(3, 3));

    bit::list<AA>::iterator it = lt.begin();
	while (it != lt.end())
	{
		//cout << (*it)._a1<<" "<<(*it)._a2 << endl;
		cout << it->_a1 << " " << it->_a2 << endl;
		cout << it.operator->()->_a1 << " " << it.operator->()->_a1 << endl;


		++it;
	}
	cout << endl;

	int* p = new int;
	*p = 1;

	AA* ptr = new AA;
	ptr->_a1 = 1;

}

void test_reverse()
{
    bit::list<int> lt;
    lt.push_back(1);
    lt.push_back(2);
    lt.push_back(3);
    lt.push_back(4);
    lt.push_back(5);
    
    bit::list<int>::reverse_iterator it = lt.rbegin();

    while(it != lt.rend())
    {
        cout << *it << " ";
		++it;
    }
    cout << endl;

	bit::list<AA> lt2;
	lt2.push_back(AA(1, 1));
	lt2.push_back(AA(2, 2));
	lt2.push_back(AA(3, 3));
	bit::list<AA>::reverse_iterator it2 = lt2.rbegin();
	while (it2 != lt2.rend())
	{
		//cout << (*it)._a1<<" "<<(*it)._a2 << endl;
		cout << it2->_a1 << " " << it2->_a2 << endl;
		cout << it2.operator->()->_a1 << " " << it2.operator->()->_a1 << endl;

		++it2;
	}
	cout << endl;
}

class A 
{
public:
    void print() {cout << _aa << ' ' << _a2<< " ";}
    int _b;
    A(){};

private:
    int _aa = 1;
    int _a2 = 2;
};

int main()
{
    test_list1();
    test_list2();
    test_list3();
	test_reverse();

    return 0;
}
