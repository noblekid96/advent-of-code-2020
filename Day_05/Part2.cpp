#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <algorithm>
#include <iterator>
#include <math.h>
// #include <tuple>
// #include <vector>
using namespace std;

int main(){
    ifstream infile;
    infile.open("input.txt");

    string boarding_pass;
    int lowest_front_id = 127*8;
    int highest_back_id = 7;
    set<int> possible_seats;
    for (int i = 0; i < 128; i ++){
      for (int j = 0; j < 8; j++) {
          possible_seats.insert(i*8 + j);
      }
    }
    int my_id;
    while (infile >> boarding_pass){
        double row_lower_limit = 0;
        double row_upper_limit = 127;
        double row_mid = 64;
        double column_lower_limit = 0;
        double column_upper_limit = 7;
        double column_mid = 4;

        for ( int i = 0; i < boarding_pass.length() ; i ++){
            char part = boarding_pass[i];
            if(i < 7){
                part == 'F' ? row_upper_limit -= row_mid: row_lower_limit += row_mid;
                row_mid = ceil((row_upper_limit - row_lower_limit)/2);
            } else {
                part == 'L' ? column_upper_limit -= column_mid: column_lower_limit += column_mid;
                column_mid = ceil((column_upper_limit - column_lower_limit)/2);
            }
            // cout << "Row limits: " << row_lower_limit << ' ' << row_upper_limit << '\n';
            // cout << "Column limits: " << column_lower_limit << ' ' << column_upper_limit << '\n';
        };
        int row = min(row_lower_limit,row_upper_limit);
        int column = max(column_lower_limit,column_upper_limit);
        // cout << "Seat coords: " << row << ' ' << column << '\n';
        int seat_id = row * 8 + column;
        possible_seats.erase(seat_id);
    };
    for (int seat_id : possible_seats){
        if (possible_seats.find(seat_id + 1) == possible_seats.end() && possible_seats.find(seat_id-1) == possible_seats.end()){
            cout << "My seat number: " << seat_id << '\n';
        }
    }
    return 0;
}
