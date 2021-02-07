#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <vector>
#include <bitset>
using namespace std;

int main(){
    string line;
    stringstream parser;
    set<int> valid_nums;
    string field;
    bool finding_invalid = false;
    long long sum = 0;

    while(getline(cin,line)){
        string tmp = "";
        if (line == "your ticket:"){
            finding_invalid = true;
            // cout << "Valid numbers: ";
            // for (auto &valid_num: valid_nums){
            //     cout << valid_num << ',';
            // }
            // cout << '\n';
            continue;
        }
        if (finding_invalid && line.find(',') != string::npos){
            parser << line;
            while(getline(parser,tmp,',')){
                int field = atoi(tmp.c_str());
                // cout << "field: " << field << '\n';
                if (valid_nums.find(field) == valid_nums.end()){
                    sum += field;
                }
            }
            parser.clear();
        } else {
          parser << line;
          while (getline(parser, tmp, ' ')) {
            // cout << "Word: " << tmp << '\n';
            if (tmp.find('-') != string::npos) {
              int delim_idx = tmp.find('-');
              int bound1 = atoi(tmp.substr(0, delim_idx).c_str());
              int bound2 =
                  atoi(tmp.substr(delim_idx + 1, tmp.length()).c_str());
              // cout << "Bounds 1 and 2: " << bound1 << ' ' << bound2 << '\n';
              for(int i = bound1; i <= bound2; i++){
                  valid_nums.insert(i);
              }
            }
          }
          parser.clear();
        }
    }
    cout << "Sum of invalid numbers: " << sum << '\n';
}
