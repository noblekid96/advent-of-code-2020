#include <iostream>
#include <fstream>
#include <set>
using namespace std;

int main(){
    ifstream infile;
    infile.open("input.txt");

    set<int> mp;
    int val;

    while(infile >> val){
        mp.insert(val);
    }

    int a,b,c;
    for (auto it = mp.begin(); it != mp.end(); ++it){
        for (auto jt = mp.begin(); jt != mp.end(); ++jt){
            if (mp.find((2020 - *it) - *jt) != mp.end()) {
                a = *it;
                b = *jt;
                c = (2020 - *it) - *jt;
                auto result = a*b*c;
                cout << result << '\n';
                return 0;
          }
        }
    }
    return 0;
}
