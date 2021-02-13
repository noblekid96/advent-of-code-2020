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

typedef unsigned long long long_t;


struct Node{
    long_t label;
    Node* next;

    Node* append(int n){
        Node* new_node = new Node;
        new_node->label = n;
        new_node->next = next;
        next = new_node;
        return next;
    }

    Node* pop3(){
        Node* ret = next;
        next = next->next->next->next;
        return ret;
    }

    void push3(Node* node3){
        node3->next->next->next = next;
        next = node3;
    }
};

unordered_map<long_t, Node*> node_addr;

int main(){
    string input;
    getline(cin,input);
    Node* curr = new Node;
    curr->label = (long_t) input[0] - '0';
    cout << "Input: " << input << '\n';
    node_addr[input[0] - '0'] = curr;
    Node* appender = curr;
    long_t max = 1000000;
    for(long_t i = 1; i < input.length(); i ++){
        long_t number = (long_t) input[i] - '0';
        node_addr[number] = appender = appender->append(number);
    }
    for(long_t i = 10; i <= max ; i ++){
        node_addr[i] = appender = appender->append(i);
    }
    node_addr[max]->next = node_addr[input[0] - '0'];
    for(long_t i = 1 ; i <= max * 10; i ++){
        // cout << "-- Move " << i << "--" << '\n';
        Node* taken = curr->pop3();
        set<long_t> taken_3 = {taken->label,taken->next->label,taken->next->next->label};

        long_t current_label = curr->label-1;
        if(current_label == 0){
            current_label = max;
        }
        while(taken_3.count(current_label)){
            current_label-=1;
            if (current_label == 0) {
              current_label = max;
            }
        }
        node_addr[current_label]->push3(taken);
        curr = curr->next;
    }
    cout << "Product of node 1's 2 clockwise neighbours: " << node_addr[1]->next->label * node_addr[1]->next->next->label << '\n';
}
