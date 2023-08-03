#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <ForwardList.h>

namespace oleynikova {

  template< typename T, typename Compare >
  class PriorityQueue {
  public:
    PriorityQueue() = default;
    ~PriorityQueue() = default;
    void push(const T& rhs);
    void pop();
    bool isEmpty() const;
    size_t getSize() const;
    const T& top() const;
  private:
    oleynikova::ForwardList< T > storage_;
    Compare comparator_;
  };
}

template< typename T, typename Compare >
void oleynikova::PriorityQueue< T, Compare >::push(const T& rhs)
{
  if ((storage_.isEmpty()) || (comparator_(rhs, storage_.getFront()))) {
    storage_.pushFront(rhs);
  }
  else {
    typename oleynikova::ForwardList< T >::Iterator prev = storage_.begin();
    typename oleynikova::ForwardList< T >::Iterator curr = prev;
    curr++;
    while ((curr != storage_.end()) && (!(comparator_(rhs, *curr)))) {
      prev++;
      curr++;
    }
    storage_.insertAfter(prev, rhs);
  }
}

template< typename T, typename Compare >
void oleynikova::PriorityQueue< T, Compare >::pop()
{
  if (!isEmpty()) {
    storage_.popFront();
  }
}

template< typename T, typename Compare >
bool oleynikova::PriorityQueue< T, Compare >::isEmpty() const
{
  return storage_.isEmpty();
}

template< typename T, typename Compare >
size_t oleynikova::PriorityQueue< T, Compare >::getSize() const
{
  return storage_.getSize();
}

template< typename T, typename Compare >
const T& oleynikova::PriorityQueue< T, Compare >::top() const
{
  return storage_.getFront();
}

#endif
