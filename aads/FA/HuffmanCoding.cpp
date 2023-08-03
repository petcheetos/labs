#include "HuffmanCoding.h"
#include <iostream>
#include "PriorityQueue.h"

oleynikova::Symbol::Symbol(char c, int freq) :
  sym(c),
  frequency(freq)
{}

oleynikova::HuffmanCoding::HuffmanCoding(std::string sourceData):
  root(nullptr),
  sourceData(sourceData)
{}

void oleynikova::HuffmanCoding::encode()
{
  getAlphabet();
  buildHuffmanTree();
  createCodes(root);
  for (size_t i = 0; i < sourceData.length(); i++) {
    resultData += codes[sourceData[i]];
  }
}

void oleynikova::HuffmanCoding::printCodes(std::ostream& out)
{
  out << "Codes:\n";
  for (auto it = codes.begin(); it != codes.end(); it++) {
    if (it->first == ' ') {
      out << "<space>: " << it->second << "\n";
    }
    else if (it->first == '\n') {
      out << "<line feed>: " << it->second << "\n";
    }
    else {
      out << it->first << ": " << it->second << "\n";
    }
  }
  out << "\n";
}

std::string oleynikova::HuffmanCoding::getEncoded()
{
  return resultData;
}

oleynikova::HuffmanCoding::HuffmanTreeNode::HuffmanTreeNode(Symbol sym, HuffmanTreeNode* leftNode, HuffmanTreeNode* rightNode) :
  symbol(sym),
  left(leftNode),
  right(rightNode)
{}

bool oleynikova::HuffmanCoding::Compare::operator()(const HuffmanTreeNode* left, const HuffmanTreeNode* right)
{
  return left->symbol.frequency < right->symbol.frequency;
}

void oleynikova::HuffmanCoding::getAlphabet()
{
  for (size_t i = 0; i < sourceData.size(); i++) {
    char c = sourceData[i];
    alphabet[c] += 1;
  }
}

void oleynikova::HuffmanCoding::buildHuffmanTree()
{
  oleynikova::PriorityQueue< HuffmanTreeNode*, oleynikova::HuffmanCoding::Compare > pq;
  for (const auto& pair : alphabet) {
    Symbol symbol(pair.first, pair.second);
    HuffmanTreeNode* newNode = nullptr;
    newNode = new HuffmanTreeNode(symbol);
    pq.push(newNode);
  }
  HuffmanTreeNode* left = nullptr;
  HuffmanTreeNode* right = nullptr;
  HuffmanTreeNode* parent = nullptr;
  while (pq.getSize() > 1) {
    left = pq.top();
    pq.pop();
    right = pq.top();
    pq.pop();
    Symbol temp('\0', left->symbol.frequency + right->symbol.frequency);
    parent = new HuffmanTreeNode(temp, left, right);
    pq.push(parent);
  }
  root = pq.top();
  createCodes(root);
}

void oleynikova::HuffmanCoding::createCodes(HuffmanTreeNode* node, std::string code)
{
  if (!node) {
    return;
  }
  if (!node->left && !node->right) {
    codes[node->symbol.sym] = code;
  }
  createCodes(node->left, code + "0");
  createCodes(node->right, code + "1");
}
