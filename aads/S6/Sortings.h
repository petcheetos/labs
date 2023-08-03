#ifndef SORTINGS_H
#define SORTINGS_H

#include <vector>

namespace oleynikova {

  template< typename Iterator, typename Compare >
  void selectionSort(Iterator left, Iterator right);

  template< typename RandomIterator, typename Compare >
  void mergeSort(RandomIterator left, RandomIterator right, Compare comparator);

  template< typename RandomIterator, typename Compare >
  void quickSort(RandomIterator left, RandomIterator right, Compare comparator);

  template< typename RandomIterator, typename Compare >
  RandomIterator partition(RandomIterator left, RandomIterator right, Compare comparator);
  template< typename RandomIterator, typename Compare >
  void merge(RandomIterator left, RandomIterator middle, RandomIterator right, Compare comparator);
}

template< typename Iterator, typename Compare >
void oleynikova::selectionSort(Iterator left, Iterator right)
{
  Compare comparator;
  while (left != right) {
    Iterator next = left;
    next++;
    Iterator min = left;
    while (next != right) {
      if (comparator((*next), (*min))) {
        min = next;
      }
      next++;
    }
    if ((*min) != (*left)) {
      std::swap((*min), (*left));
    }
    left++;
  }
}

template< typename RandomIterator, typename Compare >
void oleynikova::mergeSort(RandomIterator left, RandomIterator right, Compare comparator)
{
  if (left < right) {
    RandomIterator middle = left + (right - left) / 2;
    mergeSort(left, middle, comparator);
    mergeSort(middle + 1, right, comparator);
    merge(left, middle, right, comparator);
  }
}

template< typename RandomIterator, typename Compare >
void oleynikova::quickSort(RandomIterator left, RandomIterator right, Compare comparator)
{
  if (std::distance(left, right) >= 2) {
    RandomIterator pivot = partition(left, right, comparator);
    quickSort(left, pivot, comparator);
    quickSort(std::next(pivot), right, comparator);
  }
}

template< typename RandomIterator, typename Compare >
RandomIterator oleynikova::partition(RandomIterator left, RandomIterator right, Compare comparator)
{
  RandomIterator pivot = left;
  RandomIterator temp = std::next(left);
  for (RandomIterator i = std::next(left); i != right; ++i) {
    if (comparator((*i), (*pivot))) {
      std::swap((*temp), (*i));
      ++temp;
    }
  }
  std::swap((*pivot), *(std::prev(temp)));
  return prev(temp);
}

template< typename RandomIterator, typename Compare >
void oleynikova::merge(RandomIterator left, RandomIterator middle, RandomIterator right, Compare comparator)
{
  std::vector< typename RandomIterator::value_type > merged;
  RandomIterator i = left;
  RandomIterator j = middle + 1;
  while ((i <= middle) && (j <= right)) {
    if (comparator((*i), (*j))) {
      merged.push_back(*i);
      i++;
    }
    else {
      merged.push_back(*j);
      j++;
    }
  }
  while (i <= middle) {
    merged.push_back(*i);
    i++;
  }
  while (j <= right) {
    merged.push_back(*j);
    j++;
  }
  for (auto it = merged.begin(); it != merged.end(); it++) {
    *left = *it;
    left++;
  }
}

#endif
