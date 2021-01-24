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

#define ll long long

int main(){
    string line;
    vector<int> adapters;
    while(getline(cin,line)){
        adapters.push_back(stoi(line));
    }
    sort(adapters.begin(),adapters.end());
    unordered_map<int,int> differences;
    for ( int i = 1; i <= 3; i++ ){
        differences[i] = 0;
    }
    differences[3] += 1;
    differences[adapters[0] - 0] += 1;
    for(int i = 1; i < adapters.size(); i ++ ){
        differences[adapters[i] - adapters[i-1]] += 1;
    }
    cout << differences[1] * differences[3] << '\n';
}
