#include "Myset.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void test_RBT()
{
	cout << "------------------------------ RBTree_test() ------------------------------" << endl;
	vector<int> v {9,8,7,6,5,4,3,2,1,0};

	size_t begin2 = clock();
	RBTree<int, int, bit::set<int>::SetKeyOfT> t;
	for (auto e : v)
	{
		t.Insert(e);
	}
	size_t end2 = clock();

	cout << "Insert:" << end2 - begin2 << endl;

	t.IsValidRBTRee();
    t.InOrder();

	cout << "------------------------------------------------------------------------------" << endl;
}

void test_set()
{
	cout << "--------------------------------- Set_test() ---------------------------------" << endl;
    bit::set<int> s;
	s.insert(4);
	s.insert(1);
	s.insert(2);
	s.insert(3);
	s.insert(2);
	s.insert(0);
	s.insert(10);
	s.insert(5);

	bit::set<int>::iterator it = s.begin();
	while (it != s.end())
	{
//		*it += 1;

		cout << *it << " ";
		++it;
	}
	cout << endl;

	// key޸
	it = s.begin();
//	*it = 100;

	for (auto e : s)
	{
		cout << e << " ";
	}
	cout << endl;
	cout << "------------------------------------------------------------------------------" << endl;
}




int main()
{
	test_set();
    return 0;
}
