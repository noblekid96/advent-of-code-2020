#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <vector>
#include <set>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long long_t;

int main(){
    string line;
    unordered_map<string,vector<string>> possible_allergen_words;
    set<string> not_allergens;
    stringstream parser;
    int allergen_idx;

    while(getline(cin,line)){
        allergen_idx = line.find("(contains");
        parser << line.substr(0,allergen_idx);
        vector<string> line_allergens;
        string tmp;
        while(parser >> tmp){
            cout << "Mystery word " << tmp << '\n';
        }
        parser.clear();
        parser << line.substr(allergen_idx+9);
        while(parser >> tmp){
            cout << "Allergen " << tmp.substr(0,tmp.length()-1) << '\n';
        }
        parser.clear();
    }
}
