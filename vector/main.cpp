#include "vector.h"


void test_1()
{
    bit::vector<int> nums;
//    nums.push_back(1);
//    nums.push_back(2);
//    nums.push_back(3);
//    nums.push_back(4);
//    nums.push_back(5);
//    nums.push_back(6);
    for(auto& it : nums)
       std::cout << it << ' ';
    std::cout << std::endl;
}

int main()
{
    test_1();
    return 0;
}
