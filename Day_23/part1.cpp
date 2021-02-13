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
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

int main(){
    string input;
    getline(cin,input);
    deque<int> cups;
    vector<int> picked;
    int current_cup;
    int destination;
    int destination_idx = 0;
    int move_idx = 0;
    int max;
    set<int> marked_for_removal;
    for(char c: input){
        cups.push_back(c - '0');
    }
    destination = cups[0];
    max = cups.size();
    for(int i = 1 ; i <= 100; i ++){
        cout << "-- Move " << i << "--" << '\n';
        cout << "cups: ";
        for(int cup: cups){
            cout << cup << ' ';
        }
        cout << '\n';
        current_cup = cups[move_idx];
        for(int j = move_idx + 1; j <= move_idx+3 ; j ++){
            picked.push_back(cups[j%max]);
            marked_for_removal.insert(j%max);
        }
        set<int>::reverse_iterator rit;
        for(rit=marked_for_removal.rbegin();rit!=marked_for_removal.rend(); ++rit){
            cout << "Rit: " << *rit << '\n';
            cups.erase(cups.begin()+*rit);
        }
        marked_for_removal.clear();
        cout << "picked up: ";
        for(int pickup: picked){
            cout << pickup << ' ';
        }
        cout << '\n';
        destination = current_cup-1;
        while((find(cups.begin(),cups.end(),destination) == cups.end())){
            destination-=1;
            if(destination < 1){
                destination = max;
            }
        }
        cout << "Destination: " << destination << '\n';
        destination_idx = find(cups.begin(),cups.end(),destination) - cups.begin();
        cout << "Destination idx: " << destination_idx << '\n';
        cups.insert(cups.begin()+destination_idx+1,picked.begin(),picked.end());
        picked.clear();
        int current_cup_idx = find(cups.begin(),cups.end(),current_cup) - cups.begin();
        while(current_cup_idx != move_idx){
            if(current_cup_idx < move_idx){
                //Shift right
                cups.push_front(cups.back());
                cups.pop_back();
            } else if (current_cup_idx > move_idx){
                //Shift left
                cups.push_back(cups.front());
                cups.pop_front();
            }
            current_cup_idx = find(cups.begin(),cups.end(),current_cup) - cups.begin();
        }
        move_idx = (move_idx+1)%max;
    }
    cout << "cups: ";
    for (int cup : cups) {
      cout << cup << ' ';
    }
    cout << '\n';
    cout << "Order after cup 1: ";
    int cup_1_idx = find(cups.begin(),cups.end(),1) - cups.begin();
    for(int i = cup_1_idx+1; i < cups.size(); i ++){
        cout << cups[i];
    }
    for(int i = 0; i < cup_1_idx; i ++){
        cout << cups[i];
    }
    cout << '\n';
}
