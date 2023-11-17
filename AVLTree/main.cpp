#include "AVLTree.hpp"
#include <string>

using namespace std;

int main()
{
	const int N = 20;
	vector<int> v;
	v.reserve(N);
	//srand(time(0));

	for (size_t i = 0; i < N; i++)
	{
		v.push_back(rand());
		cout << v.back() << endl;
	}

	AVLTree<int, int> t;
	for (auto e : v)
	{
		if (e == 14604)
		{
			int x = 0;
		}

		t.Insert(make_pair(e, e));
		cout << "Insert:" << e << "->" << t.IsAVLTree() << endl;
	}

	cout << t.IsAVLTree() << endl;

    AVLTree<string, string> node;
    

    return 0;
}
