#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
// #include <tuple>
// #include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

int main(){
    ifstream infile;
    infile.open("input.txt");

    string line;
    set<char> questions_answered;
    int total_sum;
    while (getline(infile,line)){
        if (line.length() == 0){
            total_sum += questions_answered.size();
            questions_answered.clear();
        } else {
            for (char c: line){
                questions_answered.insert(c);
            }
        }
    }
    total_sum += questions_answered.size();
    cout << "Total sum: " << total_sum << '\n';
}
