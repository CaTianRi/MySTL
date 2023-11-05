#include "stack.h" 
#include <iostream>

using namespace std;

int main() 
{
    bit::stack<int> stk;
    stk.push(0);
    stk.push(1);
    stk.push(2);
    stk.push(3);
    stk.push(4);
    
    while(!stk.empty())
    {
        std::cout << stk.top() << " ";
        stk.pop();
    }
    cout << endl;

    bit::queue<int> que;
    que.push(5);
    que.push(4);
    que.push(3);
    que.push(2);
    que.push(1);
    que.push(0);
    
    while(!que.empty())
    {
        cout << que.front() << " ";
        que.pop();
    }
    cout << endl;

    return 0;
}
