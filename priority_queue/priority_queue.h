#include <vector>
#include<vector>
#include <functional>

namespace bit
{

    template <class T, class Container = std::vector<T>, class Compare = std::less<T> >
    class priority_queue
    {
    public:
        priority_queue();

        template <class InputIterator>
        priority_queue(InputIterator first, InputIterator last)
        {

        }

        bool empty() const
        {
            return c.empty();
        }

        size_t size() const
        {
            return c.size();
        }

        T& top() const 
        {
            return c.front();
        }

        void push(const T& x)
        {
            
        }

        void pop()
        {
            c.pop();
            adjust_down(size()-1);
        }
    private:
        void adjust_down(size_t parent)
        {
            size_t child = parent * 2 + 1;
            while(child < size())
            {
                if(child + 1 < size() && comp(c[child], c[child+1]))
                    child++;
                
                if(comp(c[child], c[parent]))
                {
                    std::swap(c[child], c[parent]);
                    parent = child;
                    child = child * 2 + 1;
                }
                else 
                    break;
            }
        }

        void adjust_up(size_t child)
        {
            size_t parent = (child - 1) / 2;
            while(child > 0)
            {
                if(comp(c[child], c[parent]))
                {
                    swap(c[child], c[parent]);
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
