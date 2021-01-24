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
    int preamble_length = 25;
    string line;
    vector<ll> nums;
    while(getline(cin,line)){
        nums.push_back(stoll(line));
    }
    for (int i = preamble_length; i < nums.size(); i ++ ){
        ll current_num = nums[i];
        set<ll> previous_n_nums(nums.begin()+i-preamble_length,nums.begin()+i);
        bool valid_sum = false;
        for (ll p: previous_n_nums){
            if (previous_n_nums.find(current_num-p) != previous_n_nums.end()){
                valid_sum = true;
                break;
            }
        }
        if(!valid_sum){
            cout << "Invalid number: " << current_num  << '\n';
            return 0;
        }
    }
}
