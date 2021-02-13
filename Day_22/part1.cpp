
#include <cstdlib>
#include <deque>
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
    deque<int> player1_stack;
    deque<int> player2_stack;
    int total_num_cards = 0;
    getline(cin,line); // Throw away
    while(getline(cin,line)){
        cout << line << '\n';
        if(line.find(':') == string::npos){
            if(line.length() > 0){
              player1_stack.push_back(atoi(line.c_str()));
              total_num_cards++;
            }
        } else {
            break;
        }
    }
    while(getline(cin,line)){
        player2_stack.push_back(atoi(line.c_str()));
        total_num_cards ++;
    }
    cout << total_num_cards << '\n';
    bool finished = false;
    int winner_score = 0;
    while(!finished){
        int player1_card = player1_stack.front();
        player1_stack.pop_front();
        int player2_card = player2_stack.front();
        player2_stack.pop_front();
        if(player1_card > player2_card){
            player1_stack.push_back(player1_card);
            player1_stack.push_back(player2_card);
        } else if (player2_card > player1_card){
            player2_stack.push_back(player2_card);
            player2_stack.push_back(player1_card);
        }
        cout << player1_stack.size() <<" "<< player2_stack.size() << '\n';
        if(player1_stack.size() == total_num_cards){
            cout << "Player 1 winning stack: ";
            for(int i = 0 ; i < player1_stack.size(); i ++){
                cout << player1_stack[i] << " ";
                winner_score += (i+1) * player1_stack[player1_stack.size()-(i+1)];
            }
            cout << '\n';
            cout << "Player 1 won with a score of: ";
            cout << winner_score << '\n';
            break;
        } else if (player2_stack.size() == total_num_cards){
            cout << "Player 2 winning stack: ";
            for(int i = 0 ; i < player2_stack.size(); i ++){
                cout << player2_stack[i] << " ";
                winner_score += (i+1) * player2_stack[player2_stack.size()-(i+1)];
            }
            cout << '\n';
            cout << "Player 2 won with a score of: ";
            cout << winner_score << '\n';
            break;
        }
    }
}
