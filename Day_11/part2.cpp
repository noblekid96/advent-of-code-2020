#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <vector>
using namespace std;

struct {
    int dx;
    int dy;
} directions[] = {{-1,-1,},{-1,0,},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

#define ll long long

void update_seats(vector<string>& old_seats ,vector<string>& new_seats){
  int rows = old_seats.size();
  int cols = old_seats[0].length();
  for (int x = 0; x < rows; x++) {
    for (int y = 0; y < cols; y++) {
      if (old_seats[x].at(y) == 'L') {
        bool empty_around = true;
        for (int d = 0; d < 8; d++) {
          int adj_x = x + directions[d].dx;
          int adj_y = y + directions[d].dy;
          while(adj_x >= 0 && adj_x < rows && adj_y >= 0 && adj_y < cols){
            if (old_seats[adj_x].at(adj_y) == '#') {
              empty_around = false;
            }
            if (old_seats[adj_x].at(adj_y) != '.'){
              break;
            }
            adj_x += directions[d].dx;
            adj_y += directions[d].dy;
          }

          // if (adj_x >= 0 && adj_x < rows && adj_y >= 0 && adj_y < cols) {
          //   if (old_seats[adj_x].at(adj_y) == '#') {
          //     empty_around = false;
          //   }
          // }
        }
        if (empty_around) {
          new_seats[x][y] = '#';
        }
      } else if (old_seats[x].at(y) == '#') {
        bool occupied_around = true;
        int occupied_count = 0;
        for (int d = 0; d < 8; d++) {
          int adj_x = x + directions[d].dx;
          int adj_y = y + directions[d].dy;
          while(adj_x >= 0 && adj_x < rows && adj_y >= 0 && adj_y < cols){
            if (old_seats[adj_x].at(adj_y) == '#') {
              occupied_count += 1;
            }
            if (old_seats[adj_x].at(adj_y) != '.'){
              break;
            }
            adj_x += directions[d].dx;
            adj_y += directions[d].dy;
          }
        }
        if (occupied_count >= 5) {
          new_seats[x][y] = 'L';
        }
      }
    }
  }
}

bool compare_seats(vector<string>& old_seats,vector<string>& new_seats){
  int rows = old_seats.size();
  for (int i = 0; i < rows; i++) {
      if (new_seats[i] != old_seats[i]) {
        return false;
      }
  }
  return true;
}

int main(){
    string line;
    int row = 0;
    int column = 0;
    bool stable = false;
    int occupied = 0;

    getline(cin,line);
    column = line.length();
    vector<string> seats;
    seats.push_back(line);
    row++;

    while(getline(cin,line)){
      seats.push_back(line);
      row++;
    }
    // cout << seats[0] << '\n';
    // cout << seats[row-1];
    // for (int i = 0; i < row; i++){
    //     for(int j = 0; j < column; j++){
    //         cout << seats[i][j];
    //     }
    //     cout << '\n';
    // }
    vector<string> new_seats = seats;
    while (!stable) {
      update_seats(seats, new_seats);
      // cout << "Old seats" << '\n';
      // for (string row : seats) {
      //   cout << row << '\n';
      // }
      // cout << "New seats" << '\n';
      // for (string row : new_seats) {
      //   cout << row << '\n';
      // }
      stable = compare_seats(seats, new_seats);
      if (!stable) {
        for (int i = 0; i < row; i++) {
          seats[i] = new_seats[i];
        }
      }
    }
    cout << "Stable seats" << '\n';
    for (string row: seats){
      cout << row << '\n';
      for (char seat: row){
        if(seat == '#'){
          occupied += 1;
        }
      }
    }
    cout << "Number of occupied seats: " << occupied << '\n';
}
