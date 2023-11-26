#include "Close_Hash.hpp"
#include <iostream>

using namespace std;

void TestHT1()
{
    Close_Hash::HashTable<int, int> ht;
	int a[] = { 4,14,24,34,5,7,1 };
	for (auto e : a)
	{
		ht.Insert(make_pair(e, e));
	}

	ht.Insert(make_pair(3, 3));
	ht.Insert(make_pair(3, 3));
	ht.Insert(make_pair(-3, -3));
	ht.print();

	ht.Erase(3);
	ht.print();

	if (ht.Find(3) != -1)
	{
		cout << "3存在" << endl;
	}
	else
	{
		cout << "3不存在" << endl;
	}

	ht.Insert(make_pair(3, 3));
	ht.Insert(make_pair(23, 3));
	ht.print();
}


int main()
{
    TestHT1();
    return 0;
}
