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
    long highest_id = 0;
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
        double row = min(row_lower_limit,row_upper_limit);
        double column = max(column_lower_limit,column_upper_limit);
        // cout << "Seat coords: " << row << ' ' << column << '\n';
        if ((row * 8 + column) > highest_id){
            highest_id = (row * 8 + column);
            cout << boarding_pass << '\n';
            cout << "New highest: " << highest_id << '\n';
            cout << "Seat coords: " << row << ' ' << column << '\n';
        }
    };
    cout << "Highest seat number: " << highest_id << '\n';
    return 0;
}
