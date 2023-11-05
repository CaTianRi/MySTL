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

    priority_queue(InputIterator first, InputIterator last);

    bool empty() const;

    size_t size() const;

    T& top() const;

    void push(const T& x);

    void pop();
  private:
    Container c;
    Compare comp;
  };
};
