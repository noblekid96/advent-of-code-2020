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

unordered_map<string ,unordered_map<string, int>> matrix;

bool dfs(string color){
    if (matrix.find(color) != matrix.end()){
        if(matrix[color].find("shiny gold") != matrix[color].end()){
            return true;
        } else {
            for (auto const &colors: matrix[color]){
                bool recursive_result = dfs(colors.first);
                if(recursive_result){
                    return recursive_result;
                }
            }
            return false;
        }
    }
    return false;
}


int main(){
    ifstream infile;
    infile.open("input.txt");

    string line;
    string rule;
    set<string> numbers = {"1","2","3","4","5","6","7","8","9"};
    while (getline(infile,rule)){
        stringstream ss(rule);
        vector<string> words;
        string word;
        while(ss >> word){
            words.push_back(word);
        }
        string container = words[0] + " " + words[1];
        string color;
        unordered_map<string, int> containees;
        for ( int i = 0; i < words.size(); i ++ ){
            if (numbers.find(words[i]) != numbers.end()){
                color = words[i+1] + " " + words[i+2];
                containees[color] = stoi(words[i]);
            }
        }
        matrix[container] = containees;
    }
    set<string> results;
    for (auto const &i : matrix) {
        bool can_get = dfs(i.first);
        if(can_get){
           results.insert(i.first);
        }
    }
    for (string color: results){
        cout << color << '\n';
    }
    cout << "Possible bags: " << results.size();
    return 0;
}
