#include "Expression.h"
#include <cstddef>
#include <stdexcept>
#include <limits>

void oleynikova::Expression::inputExpression(std::string& string)
{
  std::string temp = "";
  for (size_t i = 0; i < string.length(); i++) {
    if (string[i] != ' ') {
      temp += string[i];
    }
    else {
      queue.push(temp);
      temp = "";
    }
  }
  queue.push(temp);
}

void oleynikova::Expression::convertExpression()
{
  size_t size = queue.getSize();
  for (size_t i = 0; i < size; i++) {
    std::string temp = queue.getFront();
    if (temp == "(") {
      stack.push(queue.getFront());
      queue.pop();
    }
    else if (temp == ")") {
      while (stack.getTop() != "(") {
        postfix.push(stack.getTop());
        stack.pop();
      }
      stack.pop();
      queue.pop();
    }
    else if (checkNumber(temp)) {
      postfix.push(queue.getFront());
      queue.pop();
    }
    else if (checkOperator(temp)) {
      if ((stack.getSize() != 0) && (!checkPriority(stack.getTop(), temp)) && checkOperator(stack.getTop())) {
        postfix.push(stack.getTop());
        stack.pop();
      }
      stack.push(queue.getFront());
      queue.pop();
    }
    else {
      throw std::runtime_error("Math expression is not correct");
    }
  }
  for (size_t i = 0; i < stack.getSize(); i++) {
    if (stack.getTop() == "(") {
      throw std::runtime_error("Math expression is not correct");
    }
    postfix.push(stack.getTop());
    stack.pop();
  }
}

long long oleynikova::getResult(std::string& string)
{
  Expression expression;
  expression.inputExpression(string);
  expression.convertExpression();
  return expression.calculate();
}

long long oleynikova::Expression::calculate()
{
  const long long MAX_LONG = std::numeric_limits< long long >::max();
  const long long MIN_LONG = std::numeric_limits< long long >::min();  std::string currentStr = "";
  while (!postfix.isEmpty()) {
    currentStr = postfix.getFront();
    if (checkNumber(currentStr)) {
      const char* temp = currentStr.c_str();
      errno = 0;
      long long number = std::strtoll(temp, nullptr, 0);
      if (errno == ERANGE) {
        throw std::runtime_error("Overflow");
      }
      stackResult.push(number);
    }
    else {
      long long temp = stackResult.getTop();
      stackResult.pop();
      long long prev = stackResult.getTop();
      long long newTop = 0;
      stackResult.pop();
      if (currentStr == "+") {
        if (temp > (MAX_LONG - prev)) {
          throw std::runtime_error("Overflow");
        }
        newTop = temp + prev;
      }
      else if (currentStr == "-") {
        if (temp < (MIN_LONG + prev)) {
          throw std::runtime_error("Underflow");
        }
        newTop = prev - temp;
      }
      else if (currentStr == "*") {
        if ((temp > (MAX_LONG / prev)) || (temp < (MIN_LONG / prev))) {
          throw std::runtime_error("Overflow");
        }
        newTop = prev * temp;
      }
      else if (currentStr == "/") {
        newTop = prev / temp;
      }
      else if (currentStr == "%") {
        newTop = prev % temp;
        if (newTop < 0) {
          newTop = newTop + temp;
        }
      }
      stackResult.push(newTop);
    }
    postfix.pop();
  }
  return stackResult.getTop();
}

bool oleynikova::Expression::checkOperator(const std::string& str)
{
  std::string symbols = "+-/%*";
  for (size_t i = 0; i < symbols.length(); i++) {
    if (str[0] == symbols[i]) {
      return true;
    }
  }
  return false;
}

bool oleynikova::Expression::checkNumber(const std::string& str)
{
  for (size_t i = 0; i < str.length(); i++) {
    if (!isdigit(str[i])) {
      return false;
    }
  }
  return true;
}

bool oleynikova::Expression::checkPriority(const std::string& lStr, const std::string& rStr)
{
  const std::string temp1 = "+-";
  const std::string temp2 = "*%/";
  bool res1 = 0;
  bool res2 = 0;
  for (size_t i = 0; i < temp1.length(); i++) {
    if (lStr[0] == temp1[i]) {
      res1 = 1;
    }
  }
  for (size_t i = 0; i < temp2.length(); i++) {
    if (rStr[0] == temp2[i]) {
      res2 = 1;
    }
  }
  return res1 && res2;
}
