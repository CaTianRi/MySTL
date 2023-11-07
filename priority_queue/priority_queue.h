#include <vector>
#include <functional>

namespace bit
{

    template <class T, class Container = std::vector<T>, class Compare = std::less<T> >
    class priority_queue
    {
    public:
        priority_queue() {}

        template <class InputIterator>
        priority_queue(InputIterator first, InputIterator last)
        :c(first, last)
        {
            for(int i = (size()-2) / 2; i >= 0; --i)
            {
                adjust_down(i);
            }
        }

        bool empty() const
        {
            return c.empty();
        }

        size_t size() const
        {
            return c.size();
        }

        const T& top() const 
        {
            return c[0];
        }

        T& top()
        {
            return c[0];
        }

        void push(const T& x)
        {
            c.push_back(x);
            adjust_up(size()-1);
        }

        void pop()
        {
            std::swap(c[0], c[size()-1]);
            c.pop_back();
            adjust_down(0);
        }
    private:
        void adjust_down(int parent)
        {
            int child = parent * 2 + 1;
            while(child < size())
            {
                if(child + 1 < size() && comp(c[child], c[child+1]))
                    child++;
                
                if(comp(c[parent], c[child]))
                {
                    std::swap(c[child], c[parent]);
                    parent = child;
                    child = child * 2 + 1;
                }
                else 
                    break;
            }
        }

        void adjust_up(int child)
        {
            int parent = (child - 1) / 2;
            while(child > 0)
            {
                if(comp(c[parent], c[child]))
                {
                    std::swap(c[child], c[parent]);
                    child = parent;
                    parent = (child - 1) / 2;
                }
                else 
                    break;
            }
        }
        

        Container c;
        Compare comp;
    };
};
