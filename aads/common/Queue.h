#ifndef QUEUE_H
#define QUEUE_H

#include <cstddef>
#include <ForwardList.h>

namespace oleynikova {

  template< typename T >
  class Queue {
  public:
    Queue() = default;
    ~Queue() = default;
    void push(const T& rhs);
    void pop();
    bool isEmpty() const;
    size_t getSize() const;
    T& getFront();
    T& getBack();
    const T& getFront() const;
    const T& getBack() const;
  private:
    oleynikova::ForwardList< T > storage_;
  };
}

template< typename T >
void oleynikova::Queue< T >::push(const T& rhs)
{
  storage_.pushBack(rhs);
}

template< typename T >
void oleynikova::Queue< T >::pop()
{
  storage_.popFront();
}

template< typename T >
bool oleynikova::Queue< T >::isEmpty() const
{
  return storage_.isEmpty();
}

template< typename T >
size_t oleynikova::Queue< T >::getSize() const
{
  return storage_.getSize();
}

template< typename T >
T & oleynikova::Queue<T>::getFront()
{
  return storage_.getFront();
}

template< typename T >
T & oleynikova::Queue<T>::getBack()
{
  return storage_.getBack();
}

template< typename T >
const T& oleynikova::Queue< T >::getFront() const
{
  return storage_.getFront();
}

template< typename T >
const T& oleynikova::Queue< T >::getBack() const
{
  return storage_.getBack();
}

#endif
