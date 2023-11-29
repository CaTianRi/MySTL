#include "unordered_set.hpp"
#include <vector>

using namespace std;


void test_set()
{
    bit::unordered_set<int> st;
    vector<int> nums {1,2,3,4,5,6,7,8,9,0};
    bit::unordered_set<int>::iterator it = st.begin();
    st.insert(11);
//    while(it != st.end())
//    {
//        cout << *it << " ";
//        ++it;
//    }
//    cout << endl;
}

int main()
{
    return 0;
} 
