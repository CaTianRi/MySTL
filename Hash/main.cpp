#include "unordered_set.hpp"
#include "unordered_map.hpp"
#include <vector>

using namespace std;

void test_set() {
    const int n = 100000;
    srand((unsigned int)time(nullptr));
    vector<int> nums;
    for(int i = 0; i < n; ++i)
    {
        nums.push_back(random() + i);
    }
    
    bit::unordered_set<int> st(nums.begin(), nums.end());
    st.insert(11);
    bit::unordered_set<int>::iterator it = st.begin();
    while (it != st.end()) {
        cout << *it << " ";
        ++it;
    }
    cout << endl;

    for (auto it : nums) {
        st.erase(it);
    }

    for (auto it : st)
        cout << it << " ";

    cout << endl << endl;
}

void test_map()
{
    const int n = 100000;
    srand((unsigned int)time(nullptr));
    vector<pair<int, int>> nums;
    for(int i = 0; i < n; ++i)
    {
        nums.push_back({random() + i, (random() + i) % 7});
    }

    size_t begin = clock();
    bit::unordered_map<int,int> hash(nums.begin(), nums.end());    

    hash.insert({12,13});
    hash.insert({13,14});
    for(auto it : hash)
        cout << it.first << ":" << it.second << endl;
    cout << endl;

    for(auto it : nums)
        hash.erase(it.first);

    bit::unordered_map<int,int>::iterator it1 = hash.begin();
    //(*it1).first = 1;
    (*it1++).second = 0;
    (*it1).second = 1;

    hash[3] = 4;
    hash[100] = 2;

    for(auto it : hash)
        cout << it.first << ":" << it.second << endl;
    cout << endl;
    
    size_t end = clock();
    cout << "clock():" << end - begin << endl;

    cout << endl;
}

void test_string()
{
    vector<string> arr {"INSERT", "charu", "erase", "interface", "iterator"};
    bit::unordered_set<string> st(arr.begin(), arr.end());
    for (auto it : st)
        cout << it << " ";
    cout << endl;
}

int main() {
    test_set();
    test_map();
    test_string();
    return 0;
}
