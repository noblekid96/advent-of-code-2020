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


long process_mask(string mask, string bitval){
    for (int i = 0; i < 36; i ++){
        if (mask[i] != 'X')    {
            bitval[i] = mask[i];
        }
    }
    // Convert bitstring to long
    char* ptr;
    long val = strtol(bitval.c_str(),&ptr,2);
    // cout << "Bitval after mask: "<< bitval << '\n';
    return val;
}

int main(){
    string line;
    string mask;
    string addr;
    string bitval;
    string blank = string(36,'0');
    long value;
    stringstream parser;
    unordered_map<long, long> mem_addresses;
    long sum = 0;

    while (getline(cin,line)){
        if(cin.fail()){
            break;
        }
        if(line[1] == 'a'){
            mask = line.substr(7);
        } else {
          parser.clear();
          string tmp = "";
          parser << line;
          getline(parser, tmp, '[');
          parser >> addr;
          addr = addr.substr(0,addr.size()-1);
          getline(parser, tmp, '=');
          parser >> bitval;
          bitset<36> b(atol(bitval.c_str()));
          // cout << "B to string" << b.to_string() << '\n';
          value = process_mask(mask, b.to_string());
          mem_addresses[atol(addr.c_str())] = value;
        }
    }
    for( auto const& pair: mem_addresses ){
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
        sum += pair.second;
    }
    cout << "Sum is: " << sum << '\n';
}
