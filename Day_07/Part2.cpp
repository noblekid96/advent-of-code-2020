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

int dfs(string color){
    int result = 1;
    if (matrix.find(color) != matrix.end()){
        for (auto const &colors: matrix[color]){
            int recursive_result = colors.second * dfs(colors.first);
            result += recursive_result;
        }
        return result;
    }
    return result;
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
    int num_bags = dfs("shiny gold");
    cout << "Number bags: " << num_bags - 1;
    return 0;
}
