#ifndef STACK_H
#define STACK_H

#include <cstddef>
#include <ForwardList.h>

namespace oleynikova {

  template< typename T >
  class Stack {
  public:
    Stack() = default;
    ~Stack() = default;
    void push(const T& rhs);
    void pop();
    bool isEmpty() const;
    size_t getSize() const;
    T& getTop();
    const T& getTop() const;

  private:
    oleynikova::ForwardList< T > storage_;
  };
}

template< typename T >
void oleynikova::Stack< T >::push(const T& rhs)
{
  storage_.pushFront(rhs);
}

template< typename T >
void oleynikova::Stack< T >::pop()
{
  storage_.popFront();
}

template< typename T >
bool oleynikova::Stack< T >::isEmpty() const
{
  return storage_.isEmpty();
}

template< typename T >
size_t oleynikova::Stack< T >::getSize() const
{
  return storage_.getSize();
}

template< typename T >
T & oleynikova::Stack< T >::getTop()
{
  return storage_.getFront();
}

template< typename T >
const T& oleynikova::Stack< T >::getTop() const
{
  return storage_.getFront();
}

#endif
