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
    unordered_map<string,set<string>> possible_allergen_words;
    set<string> not_allergens;
    unordered_map<string,int> ingredients;
    stringstream parser;
    int allergen_idx;
    int appearances = 0;

    while(getline(cin,line)){
        allergen_idx = line.find("(contains");
        parser << line.substr(0,allergen_idx);
        string tmp;
        set<string> mystery_words;
        while(parser >> tmp){
            cout << "Mystery word " << tmp << '\n';
            mystery_words.insert(tmp);
            if(!ingredients.count(tmp)){
                ingredients[tmp] = 0;
            }
            ingredients[tmp] += 1;
        }
        parser.clear();
        parser << line.substr(allergen_idx+9);
        while(parser >> tmp){
            cout << "Allergen " << tmp.substr(0,tmp.length()-1) << '\n';
            string allergen = tmp.substr(0,tmp.length()-1);
            if(possible_allergen_words.find(allergen) != possible_allergen_words.end()){
                set<string> intersect;
                std::set_intersection(possible_allergen_words[allergen].begin(),possible_allergen_words[allergen].end(),
                                      mystery_words.begin(),mystery_words.end(),std::inserter(intersect,intersect.begin()));
                for(string intersect_word : intersect){
                    cout << "Intersect word: " << intersect_word << '\n';
                }
                possible_allergen_words[allergen] = intersect;
            } else {
                possible_allergen_words[allergen] = mystery_words;
            }
        }
        mystery_words.clear();
        parser.clear();
    }
    for (auto& ingredient_counts : ingredients){
        bool not_allergen = true;
        for(auto& possible_allergen : possible_allergen_words){
            if(possible_allergen.second.find(ingredient_counts.first) != possible_allergen.second.end()){
                not_allergen = false;
            }
        }
        if(not_allergen){
            cout << "Non allergen: " << ingredient_counts.first << " - Count: " << ingredient_counts.second << '\n';
            not_allergens.insert(ingredient_counts.first);
            appearances += ingredient_counts.second;
        }
    }
    cout << "Not allergen: ";
    for (string not_allergen : not_allergens){
        cout << not_allergen << ",";
    }
    cout << '\n';
    cout << "Number of appearances of non allergens: " << appearances << '\n';
}
