#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <utility>
#include <functional>
#include <ForwardList.h>

namespace oleynikova {
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class Dictionary {
  public:
    Dictionary() = default;
    Dictionary(std::initializer_list< std::pair < Key, Value > > values);
    ~Dictionary() = default;
    typename ForwardList< std::pair< Key, Value > >::Iterator begin();
    typename ForwardList< std::pair< Key, Value > >::Iterator end();
    typename ForwardList< std::pair< Key, Value > >::ConstIterator cbegin() const;
    typename ForwardList< std::pair< Key, Value > >::ConstIterator cend() const;
    void erase(const Key& key);
    void merge(const Dictionary< Key, Value, Compare >& source);
    bool isEmpty() const noexcept;
    typename oleynikova::ForwardList< std::pair < Key, Value > >::Iterator find(const Key& key);
    typename oleynikova::ForwardList< std::pair < Key, Value > >::ConstIterator find(const Key& key) const;
    Value& operator[](const Key& key);

    private:
    ForwardList< std::pair< Key, Value > > storage_;
  };
}

template< typename Key, typename Value, typename Compare >
using ListIterator = typename oleynikova::ForwardList< std::pair < Key, Value > >::Iterator;

template< typename Key, typename Value, typename Compare >
oleynikova::Dictionary< Key, Value, Compare >::Dictionary(std::initializer_list< std::pair< Key, Value > > values) :
  storage_()
{
  for (auto val : values) {
    (*this)[val.first] = val.second;
  }
}

template< typename Key, typename Value, typename Compare >
ListIterator< Key, Value, Compare > oleynikova::Dictionary< Key, Value, Compare >::begin()
{
  return storage_.begin();
}

template< typename Key, typename Value, typename Compare >
ListIterator< Key, Value, Compare > oleynikova::Dictionary< Key, Value, Compare >::end()
{
  return storage_.end();
}

template< typename Key, typename Value, typename Compare>
typename oleynikova::ForwardList< std::pair<Key, Value>  >::ConstIterator oleynikova::Dictionary< Key, Value, Compare >::cbegin() const
{
  return storage_.cbegin();
}

template<typename Key, typename Value, typename Compare >
typename oleynikova::ForwardList< std::pair< Key, Value > >::ConstIterator oleynikova::Dictionary< Key, Value, Compare >::cend() const
{
  return storage_.cend();
}

template< typename Key, typename Value, typename Compare >
void oleynikova::Dictionary< Key, Value, Compare >::erase(const Key& key)
{
  ListIterator< Key, Value, Compare > prev = storage_.begin();
  ListIterator< Key, Value, Compare > next = prev;
  for (; prev != storage_.end(); prev++) {
    next++;
    if ((*prev).first == key ) {
      storage_.popFront();
      break;
    }
    else if ((*next).first == key) {
      storage_.eraseAfter(prev);
      break;
    }
    else if (next == storage_.end()) {
      break;
    }
  }
}

template< typename Key, typename Value, typename Compare >
void oleynikova::Dictionary< Key, Value, Compare >::merge(const Dictionary< Key, Value, Compare >& source)
{
 typename oleynikova::ForwardList< std::pair< Key, Value> >::ConstIterator it = source.storage_.cbegin();
  for (; it != source.storage_.cend(); it++) {
    (*this)[(*it).first] = (*it).second;
  }
}

template< typename Key, typename Value, typename Compare >
bool oleynikova::Dictionary< Key, Value, Compare >::isEmpty() const noexcept
{
  return storage_.isEmpty();
}

template< typename Key, typename Value, typename Compare >
typename oleynikova::ForwardList< std::pair < Key, Value > >::Iterator
oleynikova::Dictionary< Key, Value, Compare >::find(const Key & key)
{
  typename oleynikova::ForwardList< std::pair< Key, Value > >::Iterator it = storage_.begin();
  for (; it != storage_.end(); it++) {
    if ((*it).first == key) {
      return it;
    }
  }
  it = storage_.end();
  return it;
}

template< typename Key, typename Value, typename Compare >
typename oleynikova::ForwardList< std::pair< Key, Value > >::ConstIterator
oleynikova::Dictionary< Key, Value, Compare >::find(const Key& key) const
{
  typename oleynikova::ForwardList< std::pair< Key, Value > >::ConstIterator it = storage_.cbegin();
  for (; it != storage_.cend(); it++) {
    if ((*it).first == key) {
      return it;
    }
  }
  it = storage_.cend();
  return it;
}

template< typename Key, typename Value, typename Compare >
Value& oleynikova::Dictionary< Key, Value, Compare >::operator[](const Key& key)
{
  Compare comparator;
  std::pair< Key, Value > newPair;
  newPair.first = key;
  for (ListIterator< Key, Value, Compare > current = this->begin(); current != this->end(); current++) {
    ListIterator< Key, Value, Compare > next = current;
    next++;
    if (comparator((*current).first, newPair.first)) {
      if ((next == storage_.end()) || (comparator(newPair.first, (*next).first) )) {
        storage_.insertAfter(current, newPair);
        current++;
        return (*current).second;
      }
    }
    else if ((*current).first == key) {
      return (*current).second;
    }
  }
  storage_.pushFront(newPair);
  return storage_.getFront().second;
}

#endif
