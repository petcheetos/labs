#include "Commands.h"
#include <fstream>
#include <iostream>
#include "HuffmanCoding.h"

oleynikova::Commands::Commands(std::istream& in, std::ostream& out):
  istream(in),
  ostream(out),
  functions{
    {"-help", [this]() {this->printInfo(); }},
    {"-input", [this]() {this->inputUserData(); }},
    {"-unite", [this]() {this->unite(); }},
    {"-code", [this]() {this->printHuffmanEncodeResult();}},}
{}

void oleynikova::Commands::printInfo()
{
  std::cout << "\nUsing command line arguments:\n";
  std::cout << "[input|output] <filename>\t to read or write to file\n";
  std::cout << "[files] <inputfile> <outputfile> to read and write to file\n";
  std::cout << "Commands:\n";
  std::cout << "-help : show information\n-unite <filename> : merge read data with data from file\n";
  std::cout << "-code : encode text and output result\n-input : start input from standard input\n";
  std::cout << "-clear : clear the output file in case using output file and standart input\n-quit : quit the program\n\n";
}

void oleynikova::Commands::inputData()
{
  const std::string END = "<end>";
  while (!istream.eof()) {
    std::string str;
    std::getline(istream, str);
    if (str == END) {
      return;
    }
    if (!istream.eof()) {
      str += "\n";
    }
    source += str;
  }
}

void oleynikova::Commands::unite()
{
  std::string fileName = "";
  std::cin >> fileName;
  std::ifstream secondFile(fileName, std::ios::in);
  if (!secondFile.is_open()) {
    printInvalidCommand();
    secondFile.close();
    return;
  }
  Commands temp(secondFile, ostream);
  temp.inputData();
  source += temp.source;
  secondFile.close();
}

void oleynikova::Commands::printHuffmanEncodeResult()
{
  ostream << "\nOriginal text: " << source << "\n";
  oleynikova::HuffmanCoding huffmanTree(source);
  huffmanTree.encode();
  result = huffmanTree.getEncoded();
  huffmanTree.printCodes(ostream);
  ostream << "Encoded text: " << result << "\n\n";
}

void oleynikova::Commands::printInvalidCommand()
{
  istream.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  std::cout << "<invalid command>" << "\n";
}

void oleynikova::Commands::inputCommand(int& exit)
{
  std::string command = "";
  std::cin >> command;
  if (command == "-quit" || std::cin.eof()) {
    exit = 1;
    return;
  }
  if (command == "-clear") {
    exit = 2;
    return;
  }
  auto it = functions.find(command);
  if (it != functions.end()) {
    it->second();
  }
  else {
    printInvalidCommand();
  }
}

void oleynikova::Commands::inputUserData()
{
  std::cout << "Enter the source code and type <end>\n";
  source = "";
  inputData();
}

std::string oleynikova::Commands::getSourceData()
{
  return source;
}

std::string oleynikova::Commands::getResultData()
{
  return result;
}
