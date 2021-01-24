#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <vector>
using namespace std;

int main(){
    string line;
    int accumulator = 0;
    set<int> visited_lines;
    vector<string> instructions;
    while(getline(cin,line)){
        // cout << line << '\n';
        instructions.push_back(line);
    }
    int idx = 0;
    string instruction;
    // string offset_str;
    int offset;
    while (idx >= 0 && idx < instructions.size()) {
      if (visited_lines.find(idx) != visited_lines.end()) {
          cout << "Infinite loop detected, accumulator value at: " << accumulator << '\n';
          return 0;
      }
      visited_lines.insert(idx);
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
}
