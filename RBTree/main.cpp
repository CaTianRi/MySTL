#include "Myset.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void test_set()
{
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
		*it += 1;

		cout << *it << " ";
		++it;
	}
	cout << endl;

	// key޸
	it = s.begin();
	*it = 100;

	for (auto e : s)
	{
		cout << e << " ";
	}
	cout << endl;
}

int main()
{
	const int N = 10000;
	vector<int> v;
	v.reserve(N);
	srand(time(0));

	for (size_t i = 0; i < N; i++)
	{
		v.push_back(rand() + i);
		//cout << v.back() << endl;
	}

	size_t begin2 = clock();
	RBTree<int, int, bit::set<int>::SetKeyOfT> t;
	for (auto e : v)
	{
		if (e == 29365)
		{
			int i = 0;
		}

		//cout << "Insert:" << e << "->";
		t.Insert(e);
		//cout << t.IsBalance() << endl;
	}
	size_t end2 = clock();

	cout << "Insert:" << end2 - begin2 << endl;

	cout << t.IsValidRBTRee() << endl;
//	cout << t.Height() << endl;
//	cout << t.Size() << endl;
//
//	size_t begin1 = clock();
//	for (auto e : v)
//	{
//		t.Find(e);
//	}
//
//	for (size_t i = 0; i < N; i++)
//	{
//		t.Find((rand() + i));
//	}
//
//	size_t end1 = clock();
//
//	cout << "Find:" << end1 - begin1 << endl;
//
//	return 0;
//}
    return 0;
}
