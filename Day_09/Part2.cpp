#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <vector>
#include <math.h>
using namespace std;

#define ll long long

int main(){
    int preamble_length = 25;
    string line;
    ll invalid_num;
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
            invalid_num = current_num;
            cout << "Invalid number: " << current_num  << '\n';
            break;
        }
    }
    vector<ll> prefix_sums = {nums[0]};
    for (int i = 1; i < nums.size(); i ++){
        prefix_sums.push_back(nums[i]+prefix_sums[i-1]);
    }
    for (int i = 0; i < prefix_sums.size(); i ++){
        if(nums[i] == invalid_num){
            break;
        }
        for (int j = 0; j < i; j ++){
            if(prefix_sums[i] - prefix_sums[j] == invalid_num){
                vector<ll> sub_array(nums.begin()+(j+1),nums.begin()+i);
                ll weakness = *min_element(nums.begin()+(j+1),nums.begin()+i) + *max_element(nums.begin()+(j+1),nums.begin()+i);
                cout << "XMAS weakness " << weakness << '\n';
            }
        }
    }
}
