#ifndef SORTING_TESTER_H
#define SORTING_TESTER_H

#include <string>
#include <vector>
#include <iostream>
#include <deque>
#include <list>
#include <ForwardList.h>
#include "Sortings.h"

namespace oleynikova {
  template< typename ValueType, typename Compare >
  class SortingsTester {
  public:
    SortingsTester(std::vector< ValueType > rawData, std::ostream& out, Compare comparator);
    ~SortingsTester() = default;
    void testSelectionSort();
    void testMergeSort();
    void testQSort();
    void test();

  private:
    template< typename StructType >
    void print(const StructType& container);

    template< typename StructType >
    void copy(StructType& container);

    std::vector< ValueType > sourceData;
    std::ostream& ostream;
    Compare comparator;
  };

  int generateRandomNumber(const int min, const int max);
  float generateRandomNumber(const float min, const float max);
}

template< typename ValueType, typename Compare >
oleynikova::SortingsTester< ValueType, Compare >::SortingsTester(std::vector< ValueType > rawData, std::ostream& out, Compare comp) :
  sourceData(rawData),
  ostream(out),
  comparator(comp)
{}

template< typename ValueType, typename Compare >
void oleynikova::SortingsTester< ValueType, Compare >::testSelectionSort()
{
  std::deque< ValueType > deq;
  copy(deq);
  oleynikova::selectionSort< typename std::deque< ValueType >::iterator, Compare >(deq.begin(), deq.end());
  print(deq);

  std::list< ValueType > list;
  copy(list);
  oleynikova::selectionSort< typename std::list< ValueType >::iterator, Compare >(list.begin(), list.end());
  print(list);

  oleynikova::ForwardList< ValueType > forwardList;
  typename std::vector< ValueType >::iterator it = sourceData.begin();
  for (; it != sourceData.end(); it++) {
    forwardList.pushBack(*it);
  }
  oleynikova::selectionSort< typename oleynikova::ForwardList< ValueType >::Iterator, Compare >(forwardList.begin(), forwardList.end());
  print(forwardList);
}

template< typename ValueType, typename Compare >
void oleynikova::SortingsTester< ValueType, Compare >::testMergeSort()
{
  std::deque< ValueType > deq;
  copy(deq);
  oleynikova::quickSort< typename std::deque< ValueType >::iterator, Compare >(deq.begin(), deq.end(), comparator);
  print(deq);
}

template< typename ValueType, typename Compare >
void oleynikova::SortingsTester< ValueType, Compare >::testQSort()
{
  std::deque< ValueType > deq;
  copy(deq);
  oleynikova::quickSort< typename std::deque< ValueType >::iterator, Compare >(deq.begin(), deq.end(), comparator);
  print(deq);

  std::list< ValueType > list;
  copy(list);
  oleynikova::quickSort< typename std::list< ValueType >::iterator, Compare >(list.begin(), list.end(), comparator);
  print(list);
}

template< typename ValueType, typename Compare >
void oleynikova::SortingsTester< ValueType, Compare >::test()
{
  print(sourceData);
  testSelectionSort();
  testMergeSort();
  testQSort();
}

template< typename ValueType, typename Compare >
template< typename StructType >
void oleynikova::SortingsTester< ValueType, Compare >::print(const StructType& container)
{
  auto it = container.begin();
  ostream << (*it);
  it++;
  for (; it != container.end(); it++) {
    ostream << " " << (*it);
  }
  ostream << "\n";
}

template< typename ValueType, typename Compare >
template< typename StructType >
void oleynikova::SortingsTester< ValueType, Compare >::copy(StructType& container)
{
  typename std::vector< ValueType >::iterator it = sourceData.begin();
  for (; it != sourceData.end(); it++) {
    container.push_back(*it);
  }
}

#endif
