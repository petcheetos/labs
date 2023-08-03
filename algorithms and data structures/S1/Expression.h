#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include <Stack.h>
#include <Queue.h>

namespace oleynikova {
  class Expression {
  public:
    Expression() = default;
    ~Expression() = default;

    bool checkOperator(const std::string& str);
    bool checkNumber(const std::string& str);
    bool checkPriority(const std::string& lStr, const std::string& rStr);
    void inputExpression(std::string& string);
    void convertExpression();
    friend long long getResult(std::string& string);
    long long calculate();

  private:
    Queue< std::string > queue;
    Queue< std::string > postfix;
    Stack < std::string > stack;
    Stack< long long > stackResult;
  };
  long long getResult(std::string& string);
}

#endif
