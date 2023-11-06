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
        adjust(size()-1);
    }
  private:
    void adjust(size_t child)
    {

    }


    Container c;
    Compare comp;
  };
};
