#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
using namespace std;

int count_trees(tuple<int,int> slope_movement){
    int right = get<0>(slope_movement);
    int down = get<1>(slope_movement);
    ifstream infile;
    infile.open("input.txt");

    string pattern;
    string starting_row;
    int trees_encountered = 0;
    for ( int i = 0; i < down; i++ ){
        infile >> starting_row; // Skip this row
    }
    size_t row_size = starting_row.length();

    int x_coord = right;
    int y_coord = down;
    while(infile >> pattern){
        // cout << pattern << '\n';
        if ( y_coord % down == 0 ){
          if (pattern.at(x_coord) == '#') {
            trees_encountered++;
            // cout << "Encountered tree at index: " << x_coord << '\n';
          }
          x_coord = (x_coord + right) % row_size;
        }
        y_coord ++;
    }
    // cout << "Number of trees encountered: " << trees_encountered << '\n';
    return trees_encountered;
}

int main(){
    // Right 1, down 1.
    // Right 3, down 1. (This is the slope you already checked.)
    // Right 5, down 1.
    // Right 7, down 1.
    // Right 1, down 2.
    int64_t result = 1;
    vector<int> numTreesEncountered;
    vector<tuple<int,int>> slope_movements;
    slope_movements.push_back(make_tuple(1,1));
    slope_movements.push_back(make_tuple(3,1));
    slope_movements.push_back(make_tuple(5,1));
    slope_movements.push_back(make_tuple(7,1));
    slope_movements.push_back(make_tuple(1,2));
    for (tuple<int,int> slope_movement : slope_movements ){
        int trees_encountered = count_trees(slope_movement);
        cout << "Number of trees encountered with slope " <<  get<0>(slope_movement) << ","
             << get<1>(slope_movement) << ": " << result << '\n';
        numTreesEncountered.push_back(trees_encountered);
        result *= trees_encountered;
    }
    cout << "List of results: ";
    for (int treesEncountered: numTreesEncountered){
        cout << treesEncountered << ',';
    }
    cout << '\n';
    cout << "Result of product of trees encountered: " << result << '\n';
    return 0;
}
