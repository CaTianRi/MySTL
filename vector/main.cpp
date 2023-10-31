#include "vector.h"

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
}

int main()
{
    test_1();
    return 0;
}
