#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <cstddef>
#include <cassert>
#include <utility>
#include <memory>

namespace oleynikova {
  template < typename T >
  class ForwardList {
  public:
    class Iterator;
    class ConstIterator;

    ForwardList();
    explicit ForwardList(const std::initializer_list< T >& values);
    ForwardList(const ForwardList< T > &obj);
    ForwardList(ForwardList< T > &&) noexcept;
    ~ForwardList();
    ForwardList< T >& operator=(const ForwardList< T > &obj);
    ForwardList< T >& operator=(ForwardList< T > &&obj) noexcept;
    void pushBack(const T& rhs);
    void pushFront(const T& rhs);
    void popFront();
    bool isEmpty() const noexcept;
    void swap(ForwardList< T >& obj) noexcept;
    size_t getSize() const noexcept;
    T& getBack();
    T& getFront();
    const T& getBack() const;
    const T& getFront() const;
    Iterator eraseAfter(const Iterator& prev);
    Iterator insertAfter(const Iterator& prev, const T& data);
    Iterator begin() noexcept;
    Iterator end() noexcept;
    ConstIterator cbegin() const noexcept;
    ConstIterator cend() const noexcept;
    ConstIterator begin() const noexcept;
    ConstIterator end() const noexcept;

  private:
    class Node {
    public:
      explicit Node(const T& data, Node* pNext = nullptr):
        data_(data),
        pNext_(pNext)
      {}
      ~Node() = default;
      T data_;
      Node* pNext_;
    };
    size_t count_;
    Node* head_;
  };
}

template< typename T >
class oleynikova::ForwardList< T >::ConstIterator {
public:
  ConstIterator();
  explicit ConstIterator(typename ForwardList< T >::Node* head);
  ~ConstIterator() = default;
  ConstIterator& operator++();
  ConstIterator operator++(int);
  const T& operator*() const;
  const T* operator->() const;
  bool operator==(const ConstIterator& obj) const;
  bool operator!=(const ConstIterator& obj) const;

  friend class ForwardList< T >;
protected:
  typename ForwardList< T >::Node* current_;
};

template< typename T >
oleynikova::ForwardList< T >::ConstIterator::ConstIterator():
  current_(nullptr)
{}

template< typename T >
oleynikova::ForwardList< T >::ConstIterator::ConstIterator(typename ForwardList< T >::Node* head):
  current_(head)
{}

template< typename T >
typename oleynikova::ForwardList< T >::ConstIterator& oleynikova::ForwardList< T >::ConstIterator::operator++()
{
  assert(current_ != nullptr);
  current_ = current_->pNext_;
  return *this;
}

template< typename T >
typename oleynikova::ForwardList< T >::ConstIterator oleynikova::ForwardList< T >::ConstIterator::operator++(int)
{
  assert(current_ != nullptr);
  ConstIterator it(current_);
  current_ = current_->pNext_;
  return it;
}

template< typename T >
const T& oleynikova::ForwardList< T >::ConstIterator::operator*() const
{
  assert(current_ != nullptr);
  return current_->data_;
}

template< typename T >
const T* oleynikova::ForwardList< T >::ConstIterator::operator->() const
{
  assert(current_ != nullptr);
  return std::pointer_traits< const T* >::pointer_to(**this);
}

template< typename T >
bool oleynikova::ForwardList< T >::ConstIterator::operator==(const ConstIterator& obj) const
{
  return current_ == obj.current_;
}

template< typename T >
bool oleynikova::ForwardList< T >::ConstIterator::operator!=(const ConstIterator& obj) const
{
  return !(*this == obj);
}

template< typename T >
class oleynikova::ForwardList< T >::Iterator: public ConstIterator {
public:
  Iterator& operator++();
  Iterator operator++(int);
  T& operator*() const;
  T* operator->() const;
};

template< typename T >
typename oleynikova::ForwardList< T >::Iterator& oleynikova::ForwardList< T >::Iterator::operator++()
{
  ConstIterator::operator++();
  return *this;
}

template< typename T >
typename oleynikova::ForwardList< T >::Iterator oleynikova::ForwardList< T >::Iterator::operator++(int)
{
  Iterator it = *this;
  ConstIterator::operator++();
  return it;
}

template< typename T >
T& oleynikova::ForwardList< T >::Iterator::operator*() const
{
  return const_cast< T& >(ConstIterator::operator*());
}

template< typename T >
T* oleynikova::ForwardList< T >::Iterator::operator->() const
{
  return const_cast< T* >(ConstIterator::operator->());
}

template< typename T >
oleynikova::ForwardList< T >::ForwardList():
  count_(0),
  head_(nullptr)
{}

template< typename T >
oleynikova::ForwardList< T >::ForwardList(const std::initializer_list< T >& values):
  count_(0),
  head_(nullptr)
{
  for (auto val : values) {
    pushBack(val);
  }
}

template< typename T >
oleynikova::ForwardList< T >::ForwardList(const ForwardList< T >& obj):
  count_(0),
  head_(nullptr)
{
  for (ConstIterator it = obj.cbegin(); it != obj.cend(); it++) {
    pushBack((*it));
  }
}

template< typename T >
oleynikova::ForwardList< T >::ForwardList(ForwardList< T >&& obj) noexcept:
  count_(obj.count_),
  head_(obj.head_)
{
  obj.count_ = 0;
  obj.head_ = nullptr;
}

template< typename T >
oleynikova::ForwardList< T >::~ForwardList()
{
  while (count_) {
    popFront();
  }
}

template< typename T >
oleynikova::ForwardList< T >& oleynikova::ForwardList< T >::operator=(const ForwardList< T >& obj)
{
  if (this != &obj) {
    ForwardList< T > temp(obj);
    swap(temp);
  }
  return *this;
}

template< typename T >
oleynikova::ForwardList< T >& oleynikova::ForwardList< T >::operator=(ForwardList< T >&& obj) noexcept
{
  if (this != &obj) {
    swap(obj);
  }
  return *this;
}

template< typename T >
void oleynikova::ForwardList< T >::pushBack(const T& rhs)
{
  if (head_ == nullptr) {
    head_ = new Node(rhs);
  }
  else {
    Node *current = this->head_;
    while (current->pNext_ != nullptr) {
      current = current->pNext_;
    }
    current->pNext_ = new Node(rhs);
  }
  count_++;
}

template< typename T>
void oleynikova::ForwardList< T >::pushFront(const T& rhs)
{
  head_ = new Node(rhs, head_);
  count_++;
}

template< typename T >
void oleynikova::ForwardList< T >::popFront()
{
  Node *temp = head_;
  Node *next = head_->pNext_;
  head_ = next;
  delete temp;
  count_--;
}

template< typename T >
bool oleynikova::ForwardList< T >::isEmpty() const noexcept
{
  return !count_;
}

template< typename T >
void oleynikova::ForwardList< T >::swap(ForwardList< T >& obj) noexcept
{
  std::swap(head_, obj.head_);
  std::swap(count_, obj.count_);
}

template< typename T >
size_t oleynikova::ForwardList< T >::getSize() const noexcept
{
  return count_;
}

template< typename T >
T& oleynikova::ForwardList< T >::getBack()
{
  const ForwardList< T >& constList = static_cast<const ForwardList&>(*this);
  const T& constElement = constList.getBack();
  T& element = const_cast<T&>(constElement);
  return element;
}

template< typename T >
T& oleynikova::ForwardList< T >::getFront()
{
  return head_->data_;
}

template< typename T >
const T& oleynikova::ForwardList< T >::getBack() const
{
  Node* current = head_;
  while (current->pNext_ != nullptr) {
    current = current->pNext_;
  }
  return current->data_;
}

template< typename T >
const T & oleynikova::ForwardList< T >::getFront() const
{
  return head_->data_;
}

template< typename T >
typename oleynikova::ForwardList< T >::Iterator oleynikova::ForwardList< T >::begin() noexcept
{
  Iterator it;
  it.current_ = head_;
  return it;
}

template< typename T >
typename oleynikova::ForwardList< T >::Iterator oleynikova::ForwardList< T >::end() noexcept
{
  Iterator it;
  it.current_ = head_;
  while (it.current_ != nullptr) {
    it++;
  }
  return it;
}

template< typename T >
typename oleynikova::ForwardList< T >::ConstIterator oleynikova::ForwardList< T >::cbegin() const noexcept
{
  return begin();
}

template< typename T >
typename oleynikova::ForwardList< T >::ConstIterator oleynikova::ForwardList< T >::cend() const noexcept
{
  return end();
}

template< typename T >
typename oleynikova::ForwardList< T >::ConstIterator oleynikova::ForwardList< T >::begin() const noexcept
{
  ConstIterator it;
  it.current_ = head_;
  return it;
}

template< typename T >
typename oleynikova::ForwardList< T >::ConstIterator oleynikova::ForwardList< T >::end() const noexcept
{
  ConstIterator it;
  it.current_ = head_;
  while (it.current_ != nullptr) {
    it++;
  }
  return it;
}

template< typename T >
typename oleynikova::ForwardList< T >::Iterator oleynikova::ForwardList< T >::eraseAfter(const Iterator &prev)
{
  Iterator prevIt = prev;
  Iterator temp;
  if (prevIt.current_ == nullptr || prevIt.current_->pNext_ == nullptr) {
    return temp;
  }
  Node* toDelete = prevIt.current_->pNext_;
  prevIt.current_->pNext_ = toDelete->pNext_;
  Iterator it;
  it.current_ = toDelete->pNext_;
  delete toDelete;
  count_--;
  return it;
}

template< typename T >
typename oleynikova::ForwardList< T >::Iterator oleynikova::ForwardList< T >::insertAfter(const Iterator& prev, const T& data)
{
  Iterator newIt;
  newIt.current_ = new Node(data);
  Iterator prevIt = prev;
  prevIt++;
  (newIt.current_)->pNext_ = prevIt.current_;
  (prev.current_)->pNext_ = newIt.current_;
  count_++;
  return newIt;
}

#endif
