#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <string>
#include <iosfwd>
#include <Dictionary.h>

namespace oleynikova {
  struct Symbol {
    Symbol(char c, int freq);
    char sym;
    int frequency;
  };

  class HuffmanCoding {
  public:
    explicit HuffmanCoding(std::string sourceData);
    void encode();
    void printCodes(std::ostream& out);
    std::string getEncoded();

  private:
    struct HuffmanTreeNode {
      HuffmanTreeNode(Symbol sym, HuffmanTreeNode* leftNode = nullptr, HuffmanTreeNode* rightNode = nullptr);
      Symbol symbol;
      HuffmanTreeNode* left;
      HuffmanTreeNode* right;
    };

    struct Compare {
      bool operator()(const HuffmanTreeNode* left, const HuffmanTreeNode* right);
    };

    void getAlphabet();
    void buildHuffmanTree();
    void createCodes(HuffmanCoding::HuffmanTreeNode* node, std::string code = "");

    HuffmanTreeNode* root;
    std::string sourceData;
    std::string resultData;
    oleynikova::Dictionary< char, int > alphabet;
    oleynikova::Dictionary< char, std::string > codes;
  };
}

#endif
