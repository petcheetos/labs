#ifndef DICTIONARY_FUNCTIONS
#define DICTIONARY_FUNCTIONS

#include <string>
#include <vector>
#include <initializer_list>
#include <functional>
#include <algorithm>
#include <iostream>
#include <outputFunctions.h>
#include <Stack.h>

namespace oleynikova {
  template< template< typename, typename, typename > class T, typename Key, typename Value, typename Compare = std::less< Key > >
  struct DictionaryOperations {
    DictionaryOperations() = delete;
    explicit DictionaryOperations(std::ostream& ostream);
    ~DictionaryOperations() = default;
    void inputDictionaries(std::istream& in);
    void doCommands(std::string& string);

  private:
    void print();
    void complement();
    void intersect();
    void unite();
    std::vector< std::string > commands_;
    T< Key, Value, Compare > dictionaries_;
    std::ostream& ostream_;
    T< std::string, std::function< void() >, std::less< std::string > > functions_;
  };

  std::vector< std::string > split(std::string str);

  template< template< typename, typename, typename > class T, typename Key, typename Value, typename Compare >
  T< Key, Value, Compare > complement(T< Key, Value, Compare >& left, T< Key, Value, Compare >& right);

  template< template< typename, typename, typename > class T, typename Key, typename Value, typename Compare >
  T< Key, Value, Compare > intersect(T< Key, Value, Compare >& left, T< Key, Value, Compare >& right);

  template< template< typename, typename, typename > class T, typename Key, typename Value, typename Compare >
  T< Key, Value, Compare > unite(T< Key, Value, Compare >& left, T< Key, Value, Compare >& right);
}

template< template< typename, typename, typename > class T, typename Key, typename Value, typename Compare >
oleynikova::DictionaryOperations< T, Key, Value, Compare >::DictionaryOperations(std::ostream& ostream):
  ostream_(ostream),
  functions_{
      {"print", [this]() {this->print(); }},
      {"complement", [this]() {this->complement(); }},
      {"intersect", [this]() {this->intersect(); }},
      {"union", [this]() {this->unite(); }} }
{}

template< template< typename, typename, typename > class T, typename Key, typename Value, typename Compare >
void oleynikova::DictionaryOperations< T, Key, Value, Compare >::inputDictionaries(std::istream& in)
{
  while (!in.eof()) {
    T< Key, Value, Compare > dictionary;
    std::string str = "";
    std::getline(in, str);
    Value inputData;
    std::vector< std::string > storage = split(str);
    for (size_t i = 1; i < storage.size(); i += 2) {
      inputData[std::stoi(storage[i])] = storage[i + 1];
    }
    dictionaries_[storage[0]] = inputData;
  }
}

template< template< typename, typename, typename > class T, typename Key, typename Value, typename Compare >
void oleynikova::DictionaryOperations< T, Key, Value, Compare >::doCommands(std::string& string)
{
  commands_ = split(string);
  std::string commandName = commands_[0];
  if (commands_.size() == 1 || dictionaries_.isEmpty()) {
    oleynikova::printInvalidCommand(ostream_);
  }
  auto it = functions_.find(commandName);
  if (it != functions_.end()) {
    it->second();
  }
  else {
    oleynikova::printInvalidCommand(ostream_);
  }
}

template< template< typename, typename, typename > class T, typename Key, typename Value, typename Compare >
void oleynikova::DictionaryOperations< T, Key, Value, Compare >::print()
{
  if (!(dictionaries_.find(commands_[1]) != dictionaries_.end())) {
    oleynikova::printInvalidCommand(ostream_);
  }
  else if (dictionaries_[commands_[1]].isEmpty()) {
    oleynikova::printEmpty(ostream_);
  }
  else {
    std::string name = commands_[1];
    ostream_ << name;
    auto it = dictionaries_[name].begin();
    for (; it != dictionaries_[name].end(); it++) {
      ostream_ << " " << (*it).first << " " << (*it).second;
    }
    ostream_ << "\n";
  }
}

template< template< typename, typename, typename > class T, typename Key, typename Value, typename Compare >
void oleynikova::DictionaryOperations< T, Key, Value, Compare >::complement()
{
  if ((commands_.size() != 4) || !((dictionaries_.find(commands_[2]) != dictionaries_.end())
    && (dictionaries_.find(commands_[3]) != dictionaries_.end()))) {
    oleynikova::printInvalidCommand(ostream_);
  }
  else {
    dictionaries_[commands_[1]] = oleynikova::complement(dictionaries_[commands_[2]], dictionaries_[commands_[3]]);
  }
}

template< template< typename, typename, typename > class T, typename Key, typename Value, typename Compare >
void oleynikova::DictionaryOperations< T, Key, Value, Compare >::intersect()
{
  if ((commands_.size() != 4) || !((dictionaries_.find(commands_[2]) != dictionaries_.end())
    && (dictionaries_.find(commands_[3]) != dictionaries_.end()))) {
    oleynikova::printInvalidCommand(ostream_);
  }
  else {
    dictionaries_[commands_[1]] = oleynikova::intersect(dictionaries_[commands_[2]], dictionaries_[commands_[3]]);
  }
}

template< template< typename, typename, typename > class T, typename Key, typename Value, typename Compare >
void oleynikova::DictionaryOperations< T, Key, Value, Compare >::unite()
{
  if ((commands_.size() != 4) || !((dictionaries_.find(commands_[2]) != dictionaries_.end())
    && (dictionaries_.find(commands_[3]) != dictionaries_.end()))) {
    oleynikova::printInvalidCommand(ostream_);
  }
  else {
    dictionaries_[commands_[1]] = oleynikova::unite(dictionaries_[commands_[2]], dictionaries_[commands_[3]]);
  }
}

template< template< typename, typename, typename > class T, typename Key, typename Value, typename Compare >
T< Key, Value, Compare > oleynikova::complement(T< Key, Value, Compare >& left, T< Key, Value, Compare >& right)
{
  T< Key, Value, Compare > newDictionary = right;
  newDictionary.merge(left);
  auto it = newDictionary.begin();
  auto endIt = newDictionary.end();
  while (it != endIt) {
    if ((left.find((*it).first) != left.cend()) && (right.find((*it).first) != right.cend())) {
      auto toDelete = it;
      it++;
      newDictionary.erase((*toDelete).first);
    }
    else {
      it++;
    }
  }
  return newDictionary;
}

template< template< typename, typename, typename > class T, typename Key, typename Value, typename Compare >
T< Key, Value, Compare > oleynikova::intersect(T< Key, Value, Compare >& left, T< Key, Value, Compare >& right)
{
  T< Key, Value, Compare > newDictionary = right;
  newDictionary.merge(left);
  auto it = newDictionary.begin();
  auto endIt = newDictionary.end();
  oleynikova::Stack< std::pair < Key, Value > > stack;
  for (; it != endIt; it++) {
    if (!((left.find((*it).first) != left.cend()) & (right.find((*it).first) != right.cend()))) {
      stack.push(*it);
    }
  }
  while (!stack.isEmpty()) {
    newDictionary.erase(stack.getTop().first);
    stack.pop();
  }
  return newDictionary;
}

template< template< typename, typename, typename > class T, typename Key, typename Value, typename Compare >
T< Key, Value, Compare > oleynikova::unite(T< Key, Value, Compare >& left, T< Key, Value, Compare >& right)
{
  T< Key, Value, Compare > newDictionary = right;
  newDictionary.merge(left);
  return newDictionary;
}

#endif

