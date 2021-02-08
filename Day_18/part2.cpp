#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <vector>
using namespace std;


typedef unsigned long long long_t;

long_t eval(string input);
string parse(string input);

string parse(string input) {
  stringstream parser;
  parser << input;
  stack<char> paranthesises;
  bool in_paran = false;
  string inner_expression;
  string simplified_expression;
  for (char c : input) {
    if (!in_paran) {
      // Not in paranthesis..
      if (c == '(') {
        // Track paranthesis
        in_paran = true;
        paranthesises.push(c);
      } else {
        simplified_expression.push_back(c);
      }
    } else {
      // in paranthesis..
      if (c == '(') {
          paranthesises.push(c);
            inner_expression.push_back(c);
      } else if (c == ')') {
        paranthesises.pop();
        if (paranthesises.size() == 0) {
          in_paran = false;
          simplified_expression += to_string(eval(inner_expression));
          inner_expression = "";
        } else {
          inner_expression.push_back(c);
        }
      } else {
        inner_expression.push_back(c);
      }
    }
  }
  // cout << "Final expression: " << simplified_expression << '\n';
  return simplified_expression;
}

long_t eval(string input){
    stringstream parser;
    string expanded_input = parse(input);
    string symbol;
    long_t operand_a;
    long_t operand_b;
    string arithmetic_operator;
    bool can_operate = false;
    string final_expression;
    vector<long_t> to_sum;
    long_t final_product = 1;
    parser << expanded_input;
    getline(parser,symbol,' ');
    operand_a = 0;
    operand_b = atoll(symbol.c_str());

    while(getline(parser,symbol,' ')){
        // if (symbol == "+" || symbol == "*"){
        if (symbol == "+" || symbol == "*"){
            arithmetic_operator = symbol;
        } else {
            if (arithmetic_operator == "+"){
              if (operand_a != 0) {
                to_sum.push_back(operand_a);
              }
              operand_a = operand_b;
              operand_b = atoll(symbol.c_str());
              // cout << "Symbol: " << symbol << '\n';
              // cout << operand_a << ',' << operand_b << '\n';
              operand_b += operand_a;
              // to_sum.push_back(product);
              operand_a = 0;
              // operand_b = 0;
            } else {
              if (operand_a != 0) {
                to_sum.push_back(operand_a);
              }
              operand_a = operand_b;
              operand_b = atoll(symbol.c_str());
            }
        }
    }
    if (operand_a != 0) {
      to_sum.push_back(operand_a);
    }
    if (operand_b != 0) {
      to_sum.push_back(operand_b);
    }
    for (long_t num : to_sum) {
      // cout << num <<',';
      final_product *= num;
    }
    // cout << '\n';
    // cout << final_product << '\n';
    return final_product;
}


int main(){
    string input;
    long_t sum = 0;
    while(getline(cin,input)){
        long_t line_ans = eval(input);
        sum += line_ans;
    }
    cout << "Sum of all lines results: " << sum << '\n';

}
