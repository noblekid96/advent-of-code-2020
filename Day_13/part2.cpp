#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <sys/types.h>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <vector>
using namespace std;

int main() {
  string line;
  vector<int> buses;
  while (getline(cin, line)) {
    stringstream ss(line);
    while (ss.good()) {
      string substr;
      getline(ss, substr, ',');
      if (substr == "x") {
        buses.push_back(-1);
      } else{
        buses.push_back(atoi(substr.c_str()));
      }
    }
  }

  // End of input parsing
  // Algebra... (bus_id - idx)/(bus_id) = bus_id-n % bus id
  // solve simultaneous equation => congruent += n * (bus_id{n-1}*bus_id{n-2}...*bus_id{0}) for all n in range of buses
  long long current_congruence = 0;
  long long current_lcm = buses[0];
  cout << "Current LCM: " << current_lcm << '\n';
  for (int i = 1; i < buses.size(); i++) {
    int bus_id = buses[i];
    if (bus_id == -1) {
      continue;
    }
    // Assume they are coprime and LCM can be taken directly as product of
    // moduli factor (bus ids)
    int remainder = bus_id - (i % bus_id);
    while ((current_congruence % bus_id) != remainder){
        current_congruence += current_lcm;
    }
    current_lcm = current_lcm * bus_id;
    // cout << "Current idx: " << i << '\n';
    // cout << "Current Remainder: " << remainder << '\n';
    // cout << "Current LCM: " << current_lcm << '\n';
    // cout << "Current Congruent: " << current_congruence << '\n';
  }
  cout << "Target Time: " << current_congruence << '\n';
}
