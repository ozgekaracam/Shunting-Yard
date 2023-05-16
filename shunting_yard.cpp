/*
Sources:
  Shunting-yard Algorithm
  -> https://en.wikipedia.org/wiki/Shunting-yard_algorithm
  Operator precedence in C and C++ 
  -> https://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B#Operator_precedence
*/
#include <iostream>
#include <iomanip>
#include <sstream>
#include <queue>
#include <stack> 

class Token {
public:
  enum class Type {
    Unknown, 
    Number, 
    LeftP, 
    RightP, 
    Operator
  };
  Type type;
  int precedence;
  std::string elementStr;
};

std::deque<Token> GetTokens(std::string expressionLine) {
  double doubleNr;
  std::string inputElement;
  Token token;
  std::deque<Token> tokenStack;

  std::istringstream iss(expressionLine);
  while(iss) {
    iss >> inputElement;
    if(iss) {
      token.elementStr = inputElement;
      token.precedence = -1;
      try {                                                                          
        doubleNr = std::stod(inputElement);                                                              
        token.type = Token::Type::Number;                                      
      }
      catch (const std::invalid_argument &) {  
        token.type = Token::Type::Unknown;
      }
      if (token.type == Token::Type::Unknown) {
        if (token.elementStr == "(" ) {
          token.type = Token::Type::LeftP;
        }
        else if (token.elementStr == ")" ) {
          token.type = Token::Type::RightP;
        }
        else {
          token.type = Token::Type::Operator;
          if (token.elementStr == "*" || token.elementStr == "/" || token.elementStr == "%") token.precedence = 3;
          else token.precedence = 2;  // + and -
        }
      }
      tokenStack.push_back(token);
    }
    else break; 
  }
  return tokenStack;
}

std::string FixPrecision(std::string x) {
  std::ostringstream strout ;
  std::string str;

  double doubleNr = std::stod(x);
  strout << std::setprecision(10) << doubleNr;
  str = strout.str() ;
  size_t end = str.find_last_not_of( '.' ) + 1;
  str.erase(end);
  return str;
}

std::queue<Token> ShuntingYard(std::deque<Token> tokenStack) {
  Token token;
  std::queue<Token> outputQueue;
  std::stack<Token> operatorStack;

  while(!tokenStack.empty()) {
    token = tokenStack.front();
    tokenStack.pop_front();
    if (token.type == Token::Type::Number) {
      token.elementStr = FixPrecision(token.elementStr);
      outputQueue.push(token);
    }
    else if (token.type == Token::Type::Operator) {
      Token o1 = token;
      while (!operatorStack.empty()) {
        Token o2 = operatorStack.top();
        if (o2.type != Token::Type::LeftP && (o1.precedence <= o2.precedence)) {
          operatorStack.pop();
          outputQueue.push(o2);
        }
        else break;
      }
      operatorStack.push(o1);
    }
    else if (token.type == Token::Type::LeftP) {
      operatorStack.push(token);
    }
    else if (token.type == Token::Type::RightP) {
      while(!operatorStack.empty() && operatorStack.top().type != Token::Type::LeftP) {
        outputQueue.push(operatorStack.top());
        operatorStack.pop();
      }
      if (operatorStack.top().type == Token::Type::LeftP) {
        operatorStack.pop();
      }
    }
    else break;
  }
  while(!operatorStack.empty()) {
    if (operatorStack.top().type != Token::Type::LeftP) {
      outputQueue.push(operatorStack.top());
      operatorStack.pop();
    }
    else break;
  }
  return outputQueue;
}

double CalculateResult(std::queue<Token> outputQueue) {
  std::vector<double> operandsV;

  while(!outputQueue.empty()) {
    Token token = outputQueue.front();
    outputQueue.pop();
    if (token.type == Token::Type::Number) {
      operandsV.push_back(std::stod(token.elementStr));
    }
    if (token.type == Token::Type::Operator) {
      double operandR = operandsV.back();
      operandsV.pop_back();
      double operandL = operandsV.back();
      operandsV.pop_back();
      if (token.elementStr == "*") {
        operandsV.push_back(operandL * operandR);
      }
      if (token.elementStr == "/") {
        operandsV.push_back(operandL / operandR);
      }
      if (token.elementStr == "%") {
        operandsV.push_back((double) ((int) operandL % (int) operandR));
      }
      if (token.elementStr == "+") {
        operandsV.push_back(operandL + operandR);
      }
      if (token.elementStr == "-") {
        operandsV.push_back(operandL - operandR);
      }
    }
  }
 return operandsV[0];
}

int main() {
  std::string line;
  std::vector<std::string> stringLineV;
  std::deque<Token> tokens;
  std::queue<Token> outputQueue;
  double result;

  while (std::getline(std::cin, line)) {
    if (line.empty()) break;
    stringLineV.push_back(line);
  }
  std::vector<std::string>::iterator it;
  for (it = stringLineV.begin(); it != stringLineV.end(); it++) {
    tokens = GetTokens(*it);
    outputQueue = ShuntingYard(tokens);
    result = CalculateResult(outputQueue);
    while (!outputQueue.empty()) {
      Token token = outputQueue.front();
      std::cout << token.elementStr << " ";
      outputQueue.pop();
    }
    std::cout << "= " << result << std::endl;
  }
  return 0;
}
