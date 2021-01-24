#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <utility>
#include <vector>
using namespace std;

tuple<bool,set<int>,int> find_loop(vector<string> instructions){
    int accumulator = 0;
    set<int> visited_lines;
    int idx = 0;
    string instruction;
    int last_executed_idx;
    // string offset_str;
    int offset;
    while (idx >= 0 && idx < instructions.size()) {
      if (visited_lines.find(idx) != visited_lines.end()) {
          cout << "Infinite loop detected, accumulator value at: " << accumulator << '\n';
          return {true,visited_lines,*visited_lines.end()--};
      }
      visited_lines.insert(idx);
      last_executed_idx = idx;
      instruction = instructions[idx].substr(0, 3);
      offset = stoi(instructions[idx].substr(3, instructions[idx].length()));
      cout << instruction << " " << offset << '\n';
      if (instruction == "jmp") {
        idx += offset;
      } else {
        if (instruction == "acc") {
          accumulator += offset;
        }
        idx++;
      }
    }

    // Return if it's a loop and last visited idx before loop
    // If it's not a loop return accumulator
    return {false,visited_lines,accumulator};
}

int main(){
    string line;
    vector<string> instructions;
    while(getline(cin,line)){
        // cout << line << '\n';
        instructions.push_back(line);
    }
    bool isit_loop = true;
    // while(isit_loop){
    tuple<bool, set<int>, int> attempt = find_loop(instructions);
    isit_loop = get<0>(attempt);
    if (isit_loop) { // One of the nop/jmp instruction is wrong
      set<int> visited_lines = get<1>(attempt);
      for (int i : visited_lines) {
        string visited_instruction = instructions[i].substr(0,3);
        string offset = instructions[i].substr(3);
        if (visited_instruction == "nop" || visited_instruction == "jmp") {
          string new_instruction;
          if (visited_instruction == "jmp") {
            new_instruction = "nop" + offset;
          } else if (visited_instruction == "nop") {
            new_instruction = "jmp" + offset;
          }
          vector<string> new_instructions;
          new_instructions = instructions;
          new_instructions[i] = new_instruction;
          tuple<bool, set<int>, int> attempt = find_loop(new_instructions);
          isit_loop = get<0>(attempt);
          if (!isit_loop) {
            cout << "Correct Accumulator: " << get<2>(attempt) << '\n';
            return 0;
          }
        }
      }
    }
    return 0;
}
