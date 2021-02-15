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

typedef unsigned long long ull;

ull transform(ull subject,int subject_num){
    subject *= subject_num;
    subject = subject % 20201227;
    return subject;
}

int main(){
    string line;
    char* pEnd;
    getline(cin,line);
    ull card_key = strtoull(line.c_str(), nullptr, 10);
    getline(cin,line);
    ull door_key = strtoull(line.c_str(), nullptr, 10);
    cout << "Card key: " << card_key <<'\n';
    cout << "Door key: " << door_key <<'\n';
    ull card_subject = 1;
    int card_loop_size = 0;
    while(card_subject != card_key){
        card_subject = transform(card_subject,7);
        card_loop_size++;
    }
    cout << "Card loop size: " << card_loop_size << '\n';
    ull door_subject = 1;
    int door_loop_size = 0;
    while(door_subject != door_key){
        door_subject = transform(door_subject,7);
        door_loop_size++;
    }
    cout << "Door loop size: " << door_loop_size << '\n';
    ull encryption_key = 1;
    for(int i = 0 ; i < card_loop_size ; i ++){
        encryption_key = transform(encryption_key,door_key);
    }
    cout << "Encryption key: " << encryption_key << '\n';
}
