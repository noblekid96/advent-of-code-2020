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
    int max = adapters[adapters.size()-1];
    ll dp[max+1] = { 0 };
    dp[0] = 1;
    for(int i = 0; i < adapters.size(); i ++ ){
        for(int j = 1; j <= 3; j++){
            if (adapters[i] - j >= 0){
                dp[adapters[i]] += dp[adapters[i]-j];
            }
        }
    }
    for ( int i = 0 ; i < max+1 ; i ++){
        cout << "DP index: " << i << " value: " << dp[i] << '\n';

    }
    cout << dp[max] << '\n';
}
