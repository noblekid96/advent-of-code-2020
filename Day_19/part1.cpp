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
using namespace std;

typedef unsigned long long long_t;

vector<string> valids(unordered_map<int,vector<vector<int>>>& ruleset,unordered_map<int,char>& hard_rules, int rule_num){
    if(hard_rules.find(rule_num) != hard_rules.end()){
        // cout << hard_rules[rule_num] << '\n';
        return vector<string>{string(1,hard_rules[rule_num])};
    } else if (rule_num == 0){
        vector<string> results;
        vector<vector<string>> valid_subrules_combos;
        for(int sub_rule: ruleset[0][0]){
            vector<string> valid_subrule_combos = (valids(ruleset,hard_rules,sub_rule));
            valid_subrules_combos.push_back(valid_subrule_combos);
        }
        if(valid_subrules_combos.size() == 2){
            for(string combo_1 : valid_subrules_combos[0]){
                for(string combo_2: valid_subrules_combos[1]){
                    // cout << combo_1 << ',' << combo_2 << '\n';
                    results.push_back(combo_1 + combo_2);
                }
            }
        } else if (valid_subrules_combos.size() == 3 ) {
            for(string combo_1 : valid_subrules_combos[0]){
                for(string combo_2: valid_subrules_combos[1]){
                    for(string combo_3: valid_subrules_combos[2]){
                    // cout << combo_1 << ',' << combo_2 << '\n';
                        results.push_back(combo_1 + combo_2 + combo_3);
                    }
                }
            }
        }
        return results;
    } else {
        vector<string> results;
        vector<vector<string>> valid_subrules_combos;
        for(vector<int> sub_rules: ruleset[rule_num]){
            vector<vector<string>> valid_branch_combos;
            for(int sub_rule: sub_rules){
                vector<string> valid_combos = (valids(ruleset,hard_rules,sub_rule));
                // vector<string> valid_combos_2 = (valids(ruleset,hard_rules,sub_rules[1]));
                valid_branch_combos.push_back(valid_combos);
            }
            if(valid_branch_combos.size()==1){
                for(string combo_1: valid_branch_combos[0]){
                    results.push_back(combo_1);
                }
            } else if (valid_branch_combos.size() ==2){
              vector<string> valid_combos_1 = valid_branch_combos[0];
              vector<string> valid_combos_2 = valid_branch_combos[1];
              for (string combo_1 : valid_combos_1) {
                for (string combo_2 : valid_combos_2) {
                  // cout << combo_1 << ',' << combo_2 << '\n';
                  results.push_back(combo_1 + combo_2);
                }
              }
            }
        }
        return results;
    }
}

int main(){
    string line;
    stringstream parser;
    unordered_map<int,vector<vector<int>>> ruleset;
    unordered_map<int,char> hard_rules;
    vector<string> input_combos;
    while(getline(cin,line)){
        if(line.find(':') == string::npos){
            input_combos.push_back(line);
            continue;
        }
        string tmp;
        int rule_num;
        vector<int> rules;
        vector<vector<int>> rule_rules;
        bool is_hard = false;
        parser << line;
        getline(parser,tmp,' ');
        rule_num = atoi(tmp.c_str());
        // cout << rule_num << '\n';
        ruleset[rule_num] = rule_rules;
        while(getline(parser,tmp,' ')){
            // cout << tmp << '\n';
            if (tmp.find('"') != string::npos){
                hard_rules[rule_num] = tmp.at(1);
                ruleset.erase(rule_num);
                is_hard = true;
                break;
            }
            if (tmp == "|"){
                ruleset[rule_num].push_back(rules);
                rules.clear();
            } else {
                rules.push_back(atoi(tmp.c_str()));
            }
        }
        if(!is_hard){
            ruleset[rule_num].push_back(rules);
        }
        parser.clear();
    }
    for (auto &rule: ruleset){
        cout << "Rule number " << rule.first << " rules: ";
        for (vector<int> &set: rule.second){
            cout << "[ ";
            for (int& rule_num: set){
                cout << rule_num << ' ';
            }
            cout << ']';
        }
        cout << '\n';
    }
    for (auto &rule: hard_rules){
        cout << "Rule number " << rule.first << " rule: " << rule.second << '\n';
    }
    vector<string> valid_combos= valids(ruleset,hard_rules,0);
    set<string> unique_combos;
    for (string combo: valid_combos){
        // cout << "Valid combo: " << combo << '\n';
        unique_combos.insert(combo);
    }
    int match_0 = 0;
    for(string combo: input_combos){
        if (unique_combos.find(combo) != unique_combos.end()){
            match_0 ++;
        }
    }
    cout << "Number of messages that match rule 0 is: " << match_0 << '\n';
}
