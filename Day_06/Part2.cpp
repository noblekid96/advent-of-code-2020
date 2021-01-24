#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
// #include <tuple>
// #include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

int main(){
    ifstream infile;
    infile.open("input.txt");

    string line;
    set<char> common_questions_answered;
    bool new_group = true;
    int total_sum;
    while (getline(infile, line)) {
      if (line.length() == 0) {
        total_sum += common_questions_answered.size();
        common_questions_answered.clear();
        new_group = true;
      } else {
        if (new_group) {
          for (char c : line) {
            common_questions_answered.insert(c);
          }
          new_group = false;
        } else {
          set<char> updated_common_questions_answered;
          for (char c : line) {
            if (common_questions_answered.find(c) !=
                common_questions_answered.end()) {
              updated_common_questions_answered.insert(c);
            }
          }
          common_questions_answered = updated_common_questions_answered;
        }
      }
    }
    total_sum += common_questions_answered.size();
    cout << "Total sum: " << total_sum << '\n';
}
