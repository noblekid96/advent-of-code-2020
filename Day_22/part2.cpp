
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

// int recursive_combat(deque<int>& player1_stack,deque<int>& player2_stack){
//     bool finished = false;
// }

void calculate_winner(int winner, deque<int> &winner_stack) {
  int winner_score = 0;
  cout << "Player " << winner << " winning stack: ";
  for (int i = 0; i < winner_stack.size(); i++) {
    cout << winner_stack[i] << " ";
    winner_score += (i + 1) * winner_stack[winner_stack.size() - (i + 1)];
  }
  cout << '\n';
  cout << "Player " << winner << " won with a score of: ";
  cout << winner_score << '\n';
  exit(0);
}

int crab_combat(deque<int>& player1_stack,deque<int>& player2_stack){
    bool finished = false;
    int total_num_cards = player1_stack.size() + player2_stack.size();
    int winner_score = 0;
    set<deque<int>> visited_stack1;
    set<deque<int>> visited_stack2;
    int round = 1;
    while(!finished){
        if(visited_stack1.count(player1_stack) or visited_stack2.count(player2_stack)){
            cout << "Infinite loop detected, player 1 wins" << '\n';
            return 1;
            // calculate_winner(1,player1_stack);
        }
        visited_stack1.insert(player1_stack);
        visited_stack2.insert(player2_stack);
        //DEBUG
        cout << "-- Round " << round << "--" << '\n';
        cout << "Player 1's deck:";
        for(int card: player1_stack){
           cout << card << ' ';
        }
        cout << '\n';

        cout << "Player 2's deck:";
        for(int card: player2_stack){
           cout << card << ' ';
        }
        cout << '\n';
        //DEBUG END
        int player1_card = player1_stack.front();
        cout << "Player 1 plays: " << player1_card << '\n';
        int player2_card = player2_stack.front();
        cout << "Player 2 plays: " << player2_card << '\n';

        int winner;
        if(player1_card <= player1_stack.size()-1 && player2_card <= player2_stack.size()-1){
            cout << "Going to recursive combat..." << '\n';
            cout << "Player 1 card: " << player1_card << " Player 1 stack size: " << player1_stack.size() << '\n';
            cout << "Player 2 card: " << player2_card << " Player 2 stack size: " << player2_stack.size() << '\n';
          deque<int> rec_player1_stack;
          deque<int> rec_player2_stack;
          copy(player1_stack.begin() + 1,
               player1_stack.begin() + 1 + player1_card,
               inserter(rec_player1_stack, rec_player1_stack.begin()));
          copy(player2_stack.begin() + 1,
               player2_stack.begin() + 1 + player2_card,
               inserter(rec_player2_stack, rec_player2_stack.begin()));
          winner = crab_combat(rec_player1_stack, rec_player2_stack);
        } else if(player1_card > player2_card){
            winner = 1;
        } else if (player2_card > player1_card){
            winner = 2;
        }

        if(winner == 1){
            player1_stack.pop_front();
            player2_stack.pop_front();
            player1_stack.push_back(player1_card);
            player1_stack.push_back(player2_card);
        } else if (winner == 2){
            player1_stack.pop_front();
            player2_stack.pop_front();
            player2_stack.push_back(player2_card);
            player2_stack.push_back(player1_card);
        }
        cout << player1_stack.size() <<" "<< player2_stack.size() << '\n';

        // Winning condition
        if (player1_stack.size() == total_num_cards) {
          return 1;
        } else if (player2_stack.size() == total_num_cards) {
          return 2;
        }
        round++;
    }
    // Should not reach here?
    cout << "Reach bad exit condition" << '\n';
    return 1;
}

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
    int winner = crab_combat(player1_stack, player2_stack);
    if(winner == 1){
      calculate_winner(1, player1_stack);
    } else if (winner == 2) {
      calculate_winner(2, player2_stack);
    }
}
