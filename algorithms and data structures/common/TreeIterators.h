#ifndef TREE_ITERATORS_H
#define TREE_ITERATORS_H

#include <cassert>
#include <Stack.h>
#include <Queue.h>
#include <BinaryTree.h>

namespace oleynikova {

  template< typename Key, typename Value, typename Compare >
  class BinaryTree< Key, Value, Compare >::ConstIterator {
  public:
    ConstIterator(typename oleynikova::BinaryTree< Key, Value, Compare >::Node* node, typename
      oleynikova::BinaryTree< Key, Value, Compare >::TraversalStrategy traversal = Preorder);
    ~ConstIterator() = default;
    ConstIterator& operator++();
    ConstIterator operator++(int);

    const std::pair< Key, Value >& operator*() const;
    const std::pair< Key, Value >* operator->() const;

    bool operator==(const ConstIterator& obj) const noexcept;
    bool operator!=(const ConstIterator& obj) const noexcept;

    friend class BinaryTree< Key, Value, Compare >;
  protected:
    typename BinaryTree< Key, Value, Compare >::Node* current_;
    Stack< typename oleynikova::BinaryTree< Key, Value, Compare >::Node* > stack_;
    Queue< typename oleynikova::BinaryTree< Key, Value, Compare >::Node* > queue_;
    typename oleynikova::BinaryTree< Key, Value, Compare >::TraversalStrategy strategy_;
  };

  template< typename Key, typename Value, typename Compare >
  class BinaryTree< Key, Value, Compare >::Iterator : public ConstIterator {
  public:
    Iterator(typename oleynikova::BinaryTree< Key, Value, Compare >::Node* node, typename
      oleynikova::BinaryTree< Key, Value, Compare >::TraversalStrategy traversal = Preorder);
    Iterator& operator++();
    Iterator operator++(int);
    std::pair< Key, Value >& operator*();
    std::pair< Key, Value >* operator->();
  };
}

template< typename Key, typename Value, typename Compare >
oleynikova::BinaryTree< Key, Value, Compare >::ConstIterator::ConstIterator(Node* node, TraversalStrategy traversal):
  current_(node),
  strategy_(traversal)
{
  if (strategy_ == oleynikova::BinaryTree< Key, Value, Compare >::TraversalStrategy::Preorder) {
    while (current_ != nullptr) {
      stack_.push(current_);
      current_ = current_->left;
    }
    if (stack_.isEmpty()) {
      current_ = nullptr;
    }
    else {
      current_ = stack_.getTop();
    }
  }
  else if (strategy_ == oleynikova::BinaryTree< Key, Value, Compare >::TraversalStrategy::Postorder) {
    while (current_ != nullptr) {
      stack_.push(current_);
      current_ = current_->right;
    }
    if (stack_.isEmpty()) {
      current_ = nullptr;
    }
    else {
      current_ = stack_.getTop();
    }
  }
  else if (strategy_ == oleynikova::BinaryTree< Key, Value, Compare >::TraversalStrategy::Breadth) {
    queue_.push(current_);
  }
}

template< typename Key, typename Value, typename Compare >
typename oleynikova::BinaryTree< Key, Value, Compare >::ConstIterator&
oleynikova::BinaryTree< Key, Value, Compare >::ConstIterator::operator++()
{
  assert(current_ != nullptr);
  if (strategy_ == oleynikova::BinaryTree< Key, Value, Compare >::TraversalStrategy::Preorder) {
    stack_.pop();
    Node* node = current_->right;
    while (node != nullptr) {
      stack_.push(node);
      node = node->left;
    }
    if (stack_.isEmpty()) {
      current_ = nullptr;
    }
    else {
      current_ = stack_.getTop();
    }
  }
  else if (strategy_ == oleynikova::BinaryTree< Key, Value, Compare >::TraversalStrategy::Postorder) {
    stack_.pop();
    Node* node = current_->left;
    while (node != nullptr) {
      stack_.push(node);
      node = node->right;
    }
    if (stack_.isEmpty()) {
      current_ = nullptr;
    }
    else {
      current_ = stack_.getTop();
    }
  }
  else if (strategy_ == oleynikova::BinaryTree< Key, Value, Compare >::TraversalStrategy::Breadth) {
    if (current_->left != nullptr) {
      queue_.push(current_->left);
    }
    if (current_->right != nullptr) {
      queue_.push(current_->right);
    }
    queue_.pop();
    if (!queue_.isEmpty()) {
      current_ = queue_.getFront();
    }
    else {
      current_ = nullptr;
    }
  }
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename oleynikova::BinaryTree< Key, Value, Compare >::ConstIterator
oleynikova::BinaryTree< Key, Value, Compare >::ConstIterator::operator++(int)
{
  assert(current_ != nullptr);
  ConstIterator it = (*this);
  ++(*this);
  return it;
}

template< typename Key, typename Value, typename Compare >
const std::pair< Key, Value >& oleynikova::BinaryTree< Key, Value, Compare >::ConstIterator::operator*() const
{
  assert(current_ != nullptr);
  return current_->data;
}

template< typename Key, typename Value, typename Compare >
const std::pair< Key, Value >* oleynikova::BinaryTree< Key, Value, Compare >::ConstIterator::operator->() const
{
  assert(current_ != nullptr);
  return std::pointer_traits< const std::pair< Key, Value >* >::pointer_to(**this);
}

template< typename Key, typename Value, typename Compare >
bool oleynikova::BinaryTree< Key, Value, Compare >::ConstIterator::operator==(const
  oleynikova::BinaryTree< Key, Value, Compare >::ConstIterator& obj) const noexcept
{
  return (current_ == obj.current_);
}

template< typename Key, typename Value, typename Compare >
bool oleynikova::BinaryTree< Key, Value, Compare >::ConstIterator::operator!=(const
  oleynikova::BinaryTree< Key, Value, Compare >::ConstIterator& obj) const noexcept
{
  return !((*this) == obj);
}

template< typename Key, typename Value, typename Compare >
oleynikova::BinaryTree< Key, Value, Compare >::Iterator::Iterator(Node* node, TraversalStrategy traversal):
  ConstIterator(node, traversal)
{}

template< typename Key, typename Value, typename Compare >
typename oleynikova::BinaryTree< Key, Value, Compare >::Iterator& oleynikova::BinaryTree< Key, Value, Compare >::Iterator::operator++()
{
  ConstIterator::operator++();
  return (*this);
}

template< typename Key, typename Value, typename Compare >
typename oleynikova::BinaryTree< Key, Value, Compare >::Iterator oleynikova::BinaryTree< Key, Value, Compare >::Iterator::operator++(int)
{
  Iterator it = *this;
  ConstIterator::operator++();
  return it;
}

template< typename Key, typename Value, typename Compare >
std::pair< Key, Value >& oleynikova::BinaryTree< Key, Value, Compare >::Iterator::operator*()
{
  return const_cast<std::pair< Key, Value >&>(ConstIterator::operator*());
}

template< typename Key, typename Value, typename Compare >
std::pair< Key, Value >* oleynikova::BinaryTree< Key, Value, Compare >::Iterator::operator->()
{
  return const_cast<std::pair< Key, Value >*>(ConstIterator::operator->());
}

#endif
