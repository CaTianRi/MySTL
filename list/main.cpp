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
	cout << endl;

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

int main()
{
    test_list1();
    return 0;
}
