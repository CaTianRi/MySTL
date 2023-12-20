#include <vector>
#include <limits.h>
#include <unordered_map>

using namespace std;

namespace martax
{
    template<class V, class E, E MAX_E = INT_MAX, bool isDec = false>
    class graph
    {
    public:
        graph(const V& value, size_t n)
        {
            for(size_t i = 0; i < n; ++i)
            {
                _value.push_back(value[i]);
                _map[value[i]] = i;
            }
        }

        void add(const E edge)
        {

        }
    private:
        vector<V> _value;
        unordered_map<V, int> _map;
        vector<vector<E>> _nums;
    };
};
