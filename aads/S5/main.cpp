#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdexcept>
#include <outputFunctions.h>
#include <TreeIterators.h>
#include <BinaryTree.h>
#include "FunctorStruct.h"

int main(int argc, char* argv[])
{
  if (argc != 3) {
    std::cerr << "invalid arguments";
    return 1;
  }
  std::ifstream inputFile;
  inputFile.open(argv[2], std::ios::in);
  if (!inputFile.is_open()) {
    std::cerr << "file did not open";
    return 1;
  }
  oleynikova::BinaryTree< int, std::string > tree;
  if (strcmp(argv[1], "descending") == 0) {
    tree.setStrategy(oleynikova::BinaryTree< int, std::string >::TraversalStrategy::Postorder);
  }
  else if (strcmp(argv[1], "breadth") == 0) {
    tree.setStrategy(oleynikova::BinaryTree< int, std::string >::TraversalStrategy::Breadth);
  }
  else if (strcmp(argv[1], "ascending") != 0) {
    std::cerr << "invalid arguments";
    return 1;
  }
  while (!inputFile.eof()) {
    std::string str = "";
    inputFile >> str;
    int key = 0;
    try {
      key = std::stoi(str);
    }
    catch (const std::out_of_range& e) {
      std::cerr << "incorrect value";
      return 1;
    }
    catch (const std::invalid_argument& e) {}
    inputFile >> str;
    if (str != "") {
      tree.insert(key, str);
    }
  }
  if (tree.isEmpty()) {
    oleynikova::printEmpty(std::cout);
    return 0;
  }
  oleynikova::NodeSumm functor;
  try {
    functor = tree.traverse(functor);
  }
  catch (const std::runtime_error& e) {
    std::cout << e.what() << "\n";
    return 1;
  }
  std::cout << functor.keyResult << " " << functor.stringResult << "\n";
  inputFile.close();
  return 0;
}
