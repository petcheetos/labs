#ifndef BINARY_TREE
#define BINARY_TREE

#include <functional>
#include <algorithm>
#include <initializer_list>
#include <cassert>

namespace oleynikova {

  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class BinaryTree {
  public:
    enum TraversalStrategy {
      Preorder,
      Postorder,
      Breadth
    };
    class ConstIterator;
    class Iterator;

    BinaryTree();
    explicit BinaryTree(TraversalStrategy traversalStrategy);
    BinaryTree(std::initializer_list< std::pair < const Key, Value > > list);
    BinaryTree(const BinaryTree< Key, Value, Compare >& obj);
    BinaryTree(BinaryTree< Key, Value, Compare >&& obj) noexcept;
    BinaryTree& operator=(const BinaryTree< Key, Value, Compare >& obj);
    BinaryTree& operator=(BinaryTree< Key, Value, Compare >&& obj) noexcept;
    ~BinaryTree();

    template< typename F >
    F traverse(F f) const;

    Value& operator[](const Key& key);
    Iterator find(const Key& key);
    ConstIterator find(const Key& key) const;
    bool isEmpty() const noexcept;
    void merge(const BinaryTree< Key, Value, Compare >& other);
    void setStrategy(TraversalStrategy traversal);

    void insert(const Key& key, const Value& value);
    Iterator insert(Iterator pos, const std::pair< Key, Value >& value);
    void insert(std::initializer_list< std::pair< Key, Value > > list);
    template< class P >
    std::pair< Iterator, bool > insert(P&& value);
    template< class InputIt >
    void insert(InputIt first, InputIt last);

    template< class... Args >
    std::pair< Iterator, bool > emplace(Args&&... args);

    void erase(const Key& key);
    Iterator erase(Iterator pos);
    Iterator erase(Iterator first, Iterator last);
    Iterator erase(ConstIterator first, ConstIterator last);

    Iterator getUpperBound(const Key& key);
    Iterator getLowerBound(const Key& key);

    Iterator begin();
    Iterator end();
    ConstIterator cbegin() const;
    ConstIterator cend() const;

  private:
    struct Node {
      Node(const Key& key, const Value& value, Node* left = nullptr, Node* right = nullptr) :
        data(std::pair< Key, Value >(key, value)),
        left(left),
        right(right),
        height(1)
      {}
      std::pair< Key, Value > data;
      Node* left;
      Node* right;
      unsigned char height;
    };

    void fixHeight(Node* node);
    unsigned char getHeight(Node* node) const;
    int getBalanceFactor(Node* node);
    Node* insertNode(Node* node, const Key& key, const Value& value);

    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* bigRotateLeft(Node* node);
    Node* bigRotateRight(Node* node);
    Node* balance(Node* node);

    void deleteTree(Node* node);
    Node* remove(Node* node, const Key& key);
    Node* removeMin(Node* node);
    Node* findMin(Node* node);

    void swap(BinaryTree< Key, Value, Compare >& obj) noexcept;

    Node* root;
    TraversalStrategy strategy;
  };
}

template< typename Key, typename Value, typename Compare >
oleynikova::BinaryTree< Key, Value, Compare >::BinaryTree():
  root(nullptr),
  strategy(TraversalStrategy::Preorder)
{}

template<typename Key, typename Value, typename Compare>
oleynikova::BinaryTree<Key, Value, Compare>::BinaryTree(TraversalStrategy traversalStrategy):
  root(nullptr),
  strategy(traversalStrategy)
{}

template< typename Key, typename Value, typename Compare >
oleynikova::BinaryTree< Key, Value, Compare >::BinaryTree(std::initializer_list< std::pair< const Key, Value > > list):
  BinaryTree()
{
  for (const auto& elem : list) {
    insert(elem.first, elem.second);
  }
}

template< typename Key, typename Value, typename Compare >
oleynikova::BinaryTree< Key, Value, Compare >::BinaryTree(const oleynikova::BinaryTree< Key, Value, Compare >& obj):
  BinaryTree()
{
  typename oleynikova::BinaryTree< Key, Value, Compare >::ConstIterator ptr = obj.cbegin();
  typename oleynikova::BinaryTree< Key, Value, Compare >::ConstIterator end = obj.cend();
  while (ptr != end) {
    insert((*ptr).first, (*ptr).second);
    ptr++;
  }
}

template< typename Key, typename Value, typename Compare >
oleynikova::BinaryTree< Key, Value, Compare >::BinaryTree(oleynikova::BinaryTree< Key, Value, Compare >&& obj) noexcept:
  root(obj.root)
{}

template< typename Key, typename Value, typename Compare >
oleynikova::BinaryTree< Key, Value, Compare >&
oleynikova::BinaryTree< Key, Value, Compare >::operator=(const oleynikova::BinaryTree< Key, Value, Compare >& obj)
{
  if (this != &obj) {
    BinaryTree< Key, Value, Compare > temp(obj);
    swap(temp);
  }
  return *this;
}

template< typename Key, typename Value, typename Compare >
oleynikova::BinaryTree< Key, Value, Compare >&
oleynikova::BinaryTree< Key, Value, Compare >::operator=(BinaryTree< Key, Value, Compare >&& obj) noexcept
{
  if (this != &obj) {
    swap(obj);
  }
  return *this;
}

template< typename Key, typename Value, typename Compare >
oleynikova::BinaryTree< Key, Value, Compare >::~BinaryTree()
{
  deleteTree(root);
}

template< typename Key, typename Value, typename Compare >
template< typename F >
F oleynikova::BinaryTree< Key, Value, Compare >::traverse(F f) const
{
  typename oleynikova::BinaryTree< Key, Value, Compare >::ConstIterator it = cbegin();
  typename oleynikova::BinaryTree< Key, Value, Compare >::ConstIterator endit = cend();
  for (; it != endit; it++) {
    f(*it);
  }
  return f;
}

template< typename Key, typename Value, typename Compare >
Value& oleynikova::BinaryTree<Key, Value, Compare>::operator[](const Key& key)
{
  std::pair< Key, Value > newPair;
  newPair.first = key;
  typename oleynikova::BinaryTree< Key, Value, Compare >::Iterator it = find(key);
  if (it == end()) {
    insert(newPair.first, newPair.second);
    it = find(key);
  }
  return (*it).second;
}

template< typename Key, typename Value, typename Compare >
typename oleynikova::BinaryTree< Key, Value, Compare >::Iterator oleynikova::BinaryTree< Key, Value, Compare >::find(const Key& key)
{
  typename oleynikova::BinaryTree< Key, Value, Compare >::Iterator it = begin();
  typename oleynikova::BinaryTree< Key, Value, Compare >::Iterator endIt = end();
  for (; it != endIt; it++) {
    if ((*it).first == key) {
      return it;
    }
  }
  return endIt;
}

template< typename Key, typename Value, typename Compare >
typename oleynikova::BinaryTree< Key, Value, Compare >::ConstIterator
oleynikova::BinaryTree< Key, Value, Compare >::find(const Key& key) const
{
  typename oleynikova::BinaryTree< Key, Value, Compare >::ConstIterator it = cbegin();
  typename oleynikova::BinaryTree< Key, Value, Compare >::ConstIterator endIt = cend();
  for (; it != endIt; it++) {
    if ((*it).first == key) {
      return it;
    }
  }
  return endIt;
}

template< typename Key, typename Value, typename Compare >
bool oleynikova::BinaryTree< Key, Value, Compare >::isEmpty() const noexcept
{
  return (root == nullptr);
}

template< typename Key, typename Value, typename Compare >
void oleynikova::BinaryTree< Key, Value, Compare >::merge(const BinaryTree< Key, Value, Compare >& obj)
{
  typename oleynikova::BinaryTree< Key, Value, Compare >::ConstIterator it = obj.cbegin();
  typename oleynikova::BinaryTree< Key, Value, Compare >::ConstIterator endIt = obj.cend();
  while (it != endIt) {
    insert((*it).first, (*it).second);
    it++;
  }
}

template< typename Key, typename Value, typename Compare >
void oleynikova::BinaryTree< Key, Value, Compare >::setStrategy(TraversalStrategy traversal)
{
  strategy = traversal;
}

template< typename Key, typename Value, typename Compare >
void oleynikova::BinaryTree< Key, Value, Compare >::insert(const Key& key, const Value& value)
{
  root = insertNode(root, key, value);
}

template< typename Key, typename Value, typename Compare >
typename oleynikova::BinaryTree< Key, Value, Compare >::Iterator
oleynikova::BinaryTree< Key, Value, Compare >::insert(Iterator pos, const std::pair< Key, Value >& value)
{
  insert(value.first, value.second);
  typename oleynikova::BinaryTree< Key, Value, Compare >::Iterator it = begin();
  typename oleynikova::BinaryTree< Key, Value, Compare >::Iterator endIt = end();
  for (; it != endIt; it++) {
    if ((*it).first == value.fisrt) {
      return it;
    }
  }
  return it;
}

template< typename Key, typename Value, typename Compare >
void oleynikova::BinaryTree< Key, Value, Compare >::insert(std::initializer_list< std::pair< Key, Value > > list)
{
  for (const auto& value : list) {
    insert(value.first, value.second);
  }
}

template< typename Key, typename Value, typename Compare >
template< class P >
std::pair< typename oleynikova::BinaryTree< Key, Value, Compare >::Iterator, bool>
oleynikova::BinaryTree< Key, Value, Compare >::insert(P&& value)
{
  return emplace(std::forward< P >(value));
}

template< typename Key, typename Value, typename Compare >
template< class InputIt >
void oleynikova::BinaryTree< Key, Value, Compare >::insert(InputIt first, InputIt last)
{
  InputIt it = first;
  while (it != last) {
    insert(*it);
    it++;
  }
}

template< typename Key, typename Value, typename Compare >
template< class... Args >
std::pair< typename oleynikova::BinaryTree< Key, Value, Compare >::Iterator, bool >
oleynikova::BinaryTree< Key, Value, Compare >::emplace(Args&&... args)
{
  std::pair< Key, Value > newValue(std::forward< Args >(args)...);
  typename oleynikova::BinaryTree< Key, Value, Compare >::Iterator it = getLowerBound(newValue.first);
  std::pair< typename oleynikova::BinaryTree< Key, Value, Compare >::Iterator, bool > pair(it, false);
  Compare comparator;
  if ((comparator(newValue.first, (*it).first)) || (it == end())) {
    it = insert((*it).first, newValue.second);
    pair.second = true;
    return pair;
  }
  return pair;
}

template< typename Key, typename Value, typename Compare >
void oleynikova::BinaryTree< Key, Value, Compare >::erase(const Key& key)
{
  root = remove(root, key);
}

template < typename Key, typename Value, typename Compare >
typename oleynikova::BinaryTree< Key, Value, Compare >::Iterator oleynikova::BinaryTree< Key, Value, Compare >::erase(typename
  oleynikova::BinaryTree< Key, Value, Compare >::Iterator pos) {
  if (pos == end()) {
    return end();
  }
  typename oleynikova::BinaryTree< Key, Value, Compare >::Iterator it = pos;
  it++;
  erase((*pos).first);
  return it;
}

template < typename Key, typename Value, typename Compare >
typename oleynikova::BinaryTree< Key, Value, Compare >::Iterator
oleynikova::BinaryTree< Key, Value, Compare >::erase(typename oleynikova::BinaryTree< Key, Value, Compare >::Iterator first,
  typename BinaryTree< Key, Value, Compare >::Iterator last)
{
  Iterator it = first;
  while (it != last) {
    Iterator curr = it;
    it++;
    erase(curr);
  }
  return it;
}

template < typename Key, typename Value, typename Compare >
typename oleynikova::BinaryTree< Key, Value, Compare >::Iterator
oleynikova::BinaryTree< Key, Value, Compare >::erase(typename oleynikova::BinaryTree< Key, Value, Compare >::ConstIterator first,
  typename BinaryTree< Key, Value, Compare >::ConstIterator last)
{
  ConstIterator it = first;
  while (it != last) {
    ConstIterator curr = it;
    it++;
    erase(curr);
  }
  return it;
}

template< typename Key, typename Value, typename Compare >
typename oleynikova::BinaryTree< Key, Value, Compare >::Iterator
oleynikova::BinaryTree< Key, Value, Compare >::getUpperBound(const Key& key)
{
  Iterator it = getLowerBound(key);
  if (key == (*it).first) {
    it++;
  }
  return it;
}

template< typename Key, typename Value, typename Compare >
typename oleynikova::BinaryTree< Key, Value, Compare >::Iterator
oleynikova::BinaryTree< Key, Value, Compare >::getLowerBound(const Key& key)
{
  typename oleynikova::BinaryTree< Key, Value, Compare >::Iterator it = begin();
  typename oleynikova::BinaryTree< Key, Value, Compare >::Iterator endIt = end();
  Compare comparator;
  while (it != endIt) {
    if (!comparator(key, (*it).first)) {
      return it;
    }
    it++;
  }
  return it;
}

template< typename Key, typename Value, typename Compare >
typename oleynikova::BinaryTree< Key, Value, Compare >::Iterator oleynikova::BinaryTree< Key, Value, Compare >::begin()
{
  return Iterator(root, strategy);
}

template< typename Key, typename Value, typename Compare >
typename oleynikova::BinaryTree< Key, Value, Compare >::Iterator oleynikova::BinaryTree< Key, Value, Compare >::end()
{
  return Iterator(nullptr);
}

template< typename Key, typename Value, typename Compare >
typename oleynikova::BinaryTree< Key, Value, Compare >::ConstIterator oleynikova::BinaryTree< Key, Value, Compare >::cbegin() const
{
  return ConstIterator(root, strategy);
}

template< typename Key, typename Value, typename Compare >
typename oleynikova::BinaryTree< Key, Value, Compare >::ConstIterator oleynikova::BinaryTree< Key, Value, Compare >::cend() const
{
  return ConstIterator(nullptr);
}

template< typename Key, typename Value, typename Compare >
void oleynikova::BinaryTree< Key, Value, Compare >::fixHeight(Node* node)
{
  unsigned char temp = std::max(getHeight(node->right), getHeight(node->left)) + 1;
  node->height = temp;
}

template< typename Key, typename Value, typename Compare >
unsigned char oleynikova::BinaryTree< Key, Value, Compare >::getHeight(Node* node) const
{
  if (node != nullptr) {
    return node->height;
  }
  else {
    return 0;
  }
}

template< typename Key, typename Value, typename Compare >
int oleynikova::BinaryTree< Key, Value, Compare >::getBalanceFactor(Node *node)
{
  return getHeight(node->right) - getHeight(node->left);
}

template< typename Key, typename Value, typename Compare >
typename oleynikova::BinaryTree< Key, Value, Compare >::Node*
oleynikova::BinaryTree< Key, Value, Compare >::insertNode(Node* node, const Key& key, const Value& value)
{
  Compare comparator;
  if (node == nullptr) {
    return new Node(key, value);
  }
  if (comparator(key, node->data.first)) {
    node->left = insertNode(node->left, key, value);
  }
  else if (comparator(node->data.first, key)) {
    node->right = insertNode(node->right, key, value);
  }
  else {
    node->data.second = value;
    return node;
  }
  return balance(node);
}

template< typename Key, typename Value, typename Compare >
typename oleynikova::BinaryTree< Key, Value, Compare >::Node* oleynikova::BinaryTree< Key, Value, Compare >::rotateLeft(Node* node)
{
  Node* newRoot = node->right;
  node->right = newRoot->left;
  newRoot->left = node;
  fixHeight(node);
  fixHeight(newRoot);
  return newRoot;
}

template< typename Key, typename Value, typename Compare >
typename oleynikova::BinaryTree< Key, Value, Compare >::Node* oleynikova::BinaryTree< Key, Value, Compare >::rotateRight(Node* node)
{
  Node* newRoot = node->left;
  node->left = newRoot->right;
  newRoot->right = node;
  fixHeight(node);
  fixHeight(newRoot);
  return newRoot;
}

template< typename Key, typename Value, typename Compare >
typename oleynikova::BinaryTree< Key, Value, Compare >::Node* oleynikova::BinaryTree< Key, Value, Compare >::bigRotateLeft(Node* node)
{
  node->right = rotateRight(node->right);
  node = rotateLeft(node);
  return node;
}

template< typename Key, typename Value, typename Compare >
typename oleynikova::BinaryTree< Key, Value, Compare >::Node* oleynikova::BinaryTree< Key, Value, Compare >::bigRotateRight(Node* node)
{
  node->left = rotateLeft(node->left);
  node = rotateRight(node);
  return node;
}

template< typename Key, typename Value, typename Compare >
typename oleynikova::BinaryTree< Key, Value, Compare >::Node* oleynikova::BinaryTree< Key, Value, Compare >::balance(Node* node)
{
  fixHeight(node);
  int balanceFactor = getBalanceFactor(node);
  if (balanceFactor == 2) {
    if (getBalanceFactor(node->right) < 0) {
      return bigRotateLeft(node);
    }
    return rotateLeft(node);
  }
  if (balanceFactor == -2) {
    if (getBalanceFactor(node->left) > 0) {
      return bigRotateRight(node);
    }
    return rotateRight(node);
  }
  return node;
}

template< typename Key, typename Value, typename Compare >
void oleynikova::BinaryTree< Key, Value, Compare >::deleteTree(Node* node)
{
  if (node) {
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
  }
}

template< typename Key, typename Value, typename Compare >
typename oleynikova::BinaryTree< Key, Value, Compare >::Node*
oleynikova::BinaryTree< Key, Value, Compare >::remove(Node* node, const Key& key)
{
  Compare comparator;
  if (node == nullptr) {
    return node;
  }

  if (comparator(key, node->data.first)) {
    node->left = remove(node->left, key);
  }
  else if (comparator(node->data.first, key)) {
    node->right = remove(node->right, key);
  }
  else {
    Node* left = node->left;
    Node* right = node->right;
    delete node;
    if (right == nullptr) {
      return left;
    }
    Node* temp = findMin(right);
    temp->right = removeMin(right);
    temp->left = left;
    return balance(temp);
  }
  return balance(node);
}

template< typename Key, typename Value, typename Compare >
typename oleynikova::BinaryTree< Key, Value, Compare >::Node* oleynikova::BinaryTree< Key, Value, Compare >::removeMin(Node* node)
{
  if (!node->left) {
    return node->right;
  }
  node->left = removeMin(node->left);
  return balance(node);
}

template< typename Key, typename Value, typename Compare >
typename oleynikova::BinaryTree< Key, Value, Compare >::Node* oleynikova::BinaryTree< Key, Value, Compare >::findMin(Node* node)
{
  if (node->left) {
    return findMin(node->left);
  }
  else {
    return node;
  }
}

template< typename Key, typename Value, typename Compare >
void oleynikova::BinaryTree< Key, Value, Compare >::swap(oleynikova::BinaryTree< Key, Value, Compare >& obj) noexcept
{
  std::swap(root, obj.root);
}

#endif
