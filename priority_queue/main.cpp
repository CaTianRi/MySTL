#include "priority_queue.h"
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    std::vector<int> nums {1,2,3,4,5,6,7,8,9,0};
 //   bit::priority_queue<int> que(nums.begin(), nums.end());
    bit::priority_queue<int> que;

    for(int i = 0; i < nums.size(); ++i)
    {
        que.push(nums[i]);
    }
    
    while(!que.empty())
    {
        cout << que.top() << " ";
        que.pop();
    }
    cout << endl;

    return 0;
}
