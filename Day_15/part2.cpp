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
    string starting_num;
    int turn = 1;
    int last_spoken;
    int number_this_turn;
    unordered_map<int,vector<int>> numbers_spoken_turns;
    while(getline(cin,starting_num,',')){
        numbers_spoken_turns[atoi(starting_num.c_str())] = {turn,turn};
        last_spoken = atoi(starting_num.c_str());
        turn ++;
    }
    while(turn <= 30000000){
        number_this_turn = numbers_spoken_turns[last_spoken][1] - numbers_spoken_turns[last_spoken][0];
        if (numbers_spoken_turns.find(number_this_turn) == numbers_spoken_turns.end()){
            numbers_spoken_turns[number_this_turn] = {turn,turn};
        } else {
            numbers_spoken_turns[number_this_turn] = {numbers_spoken_turns[number_this_turn][1],turn};
        }
        last_spoken = number_this_turn;
        turn++;
    }
    cout << "30000000th number to be spoken: " << last_spoken << '\n';
}
