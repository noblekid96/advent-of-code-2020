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

typedef unsigned long long long_t;

string process_mask(string mask, string bitval){
    for (int i = 0; i < 36; i ++){
      // bitval[i] = mask[i];
      switch(mask[i]){
      case '0':
        break;
      case '1':
        bitval[i] = mask[i];
        break;
      case 'X':
        bitval[i] = mask[i];
        break;
      }
    }
    return bitval;
    // // Convert bitstring to long
    // char* ptr;
    // long val = strtol(bitval.c_str(),&ptr,2);
    // // cout << "Bitval after mask: "<< bitval << '\n';
    // return val;
}

set<long_t> permute_addresses(string fixed_string,string floating_addr){
  set<long_t> addresses;
  if(fixed_string.length() == 36){
    long_t val = bitset<36>(fixed_string).to_ullong();
    addresses.insert(val);
    return addresses;
  }
  bool not_modded = true;
  for (int i = 0; i < floating_addr.length(); i++) {
    if (floating_addr[i] == 'X') {
      not_modded = false;
      for (int j = 0; j < 2; j++) {
        string modified_addr = fixed_string + floating_addr.substr(0,i+1);
        int fx_l = fixed_string.length();
        modified_addr[fx_l + i] = (to_string(j)).at(0);
        string floating;
        if (i < floating_addr.length()-1){
          floating = floating_addr.substr(i+1,floating_addr.length());
        }
        set<long_t> permuted_addresses =
            permute_addresses(modified_addr, floating);
        for (long_t perm : permuted_addresses) {
          addresses.insert(perm);
        }
      }
      return addresses;
    }
  }
  if(not_modded && (fixed_string + floating_addr).length() == 36){
    long_t val = bitset<36>(fixed_string + floating_addr).to_ullong();
    addresses.insert(val);
    return addresses;
  }
  return addresses;
}

int main(){
    string line;
    string mask;
    string addr;
    string bitval;
    stringstream parser;
    unordered_map<long_t, long_t> mem_addresses;
    long_t sum = 0;

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
          bitset<36> b(atoll(addr.c_str()));
          string masked_address = process_mask(mask, b.to_string());
          set<long_t> permuted_addresses = permute_addresses("",masked_address);
          for(long_t mem_addr: permuted_addresses){
            mem_addresses[mem_addr] = atoll(bitval.c_str());
          }
        }
    }
    for( auto const& pair: mem_addresses ){
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
        sum += pair.second;
    }
    cout << "Mem addr size: " << mem_addresses.size() << '\n';
    cout << "Sum is: " << sum << '\n';
}
