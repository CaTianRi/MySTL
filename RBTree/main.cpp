#include "Myset.hpp"
#include "MyMap.hpp"
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

    RBTree<int, int, bit::set<int>::SetKeyOfT>::iterator it = t.RightMost();
    while(it != nullptr)
    {
        cout << *it << " ";
		--it;
    }
    cout << endl;

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

	auto ret = s.find(10);
	cout << *ret << endl;


	cout << endl;
	cout << "------------------------------------------------------------------------------" << endl;
}

void test_Map()
{
	cout << "------------------------------ MyMap_test  ------------------------------" << endl;
    	bit::map<string, string> dict;
	dict.insert(make_pair("sort", ""));
	dict.insert(make_pair("sort", "xx"));
	dict.insert(make_pair("left", ""));
	dict.insert(make_pair("right", "ұ"));

	bit::map<string, string>::iterator it = dict.begin();
	while (it != dict.end())
	{
		// error
//		it->first += 'x';
//		it->second += 'y';

		cout << it->first << ":" << it->second << endl;
		++it;
	}
	cout << endl;

	string arr[] = { "㽶", "","ƻ", "", "ƻ", "", "ƻ", "ƻ", "", "ƻ", "㽶", "ƻ", "㽶" };
	bit::map<string, int> countMap;
	for (auto& e : arr)
	{
		countMap[e]++;
	}

	for (auto& kv : countMap)
	{
		cout << kv.first << ":" << kv.second << endl;
	}
	cout << endl;

	cout << "------------------------------------------------------------------------------" << endl;
}


int main()
{
    test_RBT();
	test_set();
    test_Map();
    return 0;
}
